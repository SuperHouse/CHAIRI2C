/**
   "Zero Deflection" Assistive Technology Joystick

   Internal dependencies. Install using Arduino library manager:
     "HX711_ADC" by Olav Kallhovd
   To do:
    -

   XIAO pin assignments:
     D0:
     D1:
     D2:
     D3:
     D4:  SDA
     D5:  SCL
     D6:  Tare pin
     D7:  Disable pin
     D8:
     D9:
     D10:

   227g (Pocophone) = 920000 reading

   By:
    Chris Fryer <chris.fryer78@gmail.com>
    Jonathan Oxer <jon@oxer.com.au>

   Copyright 2019-2020 SuperHouse Automation Pty Ltd www.superhouse.tv
*/
#define VERSION "2.2"
/*--------------------------- Configuration ---------------------------------*/
// Configuration should be done in the included file:
#include "config.h"

/*--------------------------- Libraries -------------------------------------*/
#include <HX711_ADC.h>              // Load cell amplifier
#include <Adafruit_DS3502.h>        // Digital potentiometer

/*--------------------------- Global Variables ------------------------------*/
uint32_t g_last_digipot_time     = 0;   // When we last updated the digipot outputs

uint8_t  g_left_button_state     = 0;
uint8_t  g_right_button_state    = 0;

/*--------------------------- Function Signatures ---------------------------*/
/*
  void     readInputPosition();
  int16_t  getScaledLoadCellValueX();
  int16_t  getScaledLoadCellValueY(); */

/*--------------------------- Instantiate Global Objects --------------------*/
Adafruit_DS3502 digipot_x = Adafruit_DS3502();
Adafruit_DS3502 digipot_y = Adafruit_DS3502();

/*--------------------------- Program ---------------------------------------*/
/**
  Setup
*/
void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  Serial.print("ZeroStick starting up, v");
  Serial.println(VERSION);

  pinMode(DISABLE_PIN,            INPUT_PULLUP);
  pinMode(TARE_BUTTON_PIN,        INPUT_PULLUP);
  pinMode(MOUSE_LEFT_BUTTON_PIN,  INPUT_PULLUP);
  pinMode(MOUSE_RIGHT_BUTTON_PIN, INPUT_PULLUP);

  if (!digipot_x.begin(DIGIPOT_X_I2C_ADDR)) {
    Serial.println("Couldn't find X-axis DS3502 chip");
  }
  Serial.println("Found X-axis DS3502 chip");

  if (!digipot_y.begin(DIGIPOT_Y_I2C_ADDR)) {
    Serial.println("Couldn't find Y-axis DS3502 chip");
  }
  Serial.println("Found Y-axis DS3502 chip");

  digipot_x.setWiper(65);               // Start with pots in central position
  digipot_y.setWiper(65);               // Start with pots in central position
}

/**
  Loop
*/
void loop()
{
  //updateDigipotOutputs();
}


/**

*/
void checkMouseButtons()
{
  uint8_t left_button_state = digitalRead(MOUSE_LEFT_BUTTON_PIN);
  if (LOW == left_button_state)
  {
    if (HIGH == g_left_button_state)
    {
      
      Serial.println("down");
      g_left_button_state = LOW;
    }
  }
  if (HIGH == left_button_state)
  {
    if (LOW == g_left_button_state)
    {
      
      Serial.println("up");
      g_left_button_state = HIGH;
    }
  }

  uint8_t right_button_state = digitalRead(MOUSE_RIGHT_BUTTON_PIN);
  if (LOW == right_button_state)
  {
    if (HIGH == g_right_button_state)
    {
      
      Serial.println("down");
      g_right_button_state = LOW;
    }
  }
  if (HIGH == right_button_state)
  {
    if (LOW == g_right_button_state)
    {
      
      Serial.println("up");
      g_right_button_state = HIGH;
    }
  }
}


/**
  Send mouse movements to the wheelchair
*/
void updateDigipotOutputs()
{
#if ENABLE_DIGIPOT_OUTPUT
  if (digitalRead(DISABLE_PIN) == HIGH) // Pull this pin low to disable
  {
    if (millis() > g_last_digipot_time + DIGIPOT_INTERVAL)
    {
      int8_t pot_position_x = 63 + (int)(g_pressure_level_x);
      int8_t pot_position_y = 63 + (int)(g_pressure_level_y);
      digipot_x.setWiper(pot_position_x);
      digipot_y.setWiper(pot_position_y);

      Serial.print("X: ");
      Serial.print(pot_position_x);
      Serial.print("    Y: ");
      Serial.println(pot_position_y);
      g_last_digipot_time = millis();
    }
  }
#endif
}

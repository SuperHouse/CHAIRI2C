/* ----------------- General config -------------------------------- */
/* Output options */
#define   ENABLE_SERIAL_DEBUGGING true

/* Serial */
#define     SERIAL_BAUD_RATE     115200  // Speed for USB serial console

/* ----------------- Hardware-specific config ---------------------- */
/*
   The hardware config for this project depends on a variable set by the
   Arduino environment to detect the target board type. Currently only
   2 target boards are supported: Arduino Leonardo, and Seeeduino XIAO.

   Update the pin definitions in the section for your target board.

   This board detection method is also used in the program to load a
   different HID library and configure it differently depending on the
   board type. If using a Seeeduino XIAO, you must select Tools ->
   USB Stack -> TinyUSB.
*/

/**** Pins for Seeeduino XIAO ****/
/* Inputs */
#define   TARE_BUTTON_PIN             6  // Pull this pin to GND to tare
#define   DISABLE_PIN                 7  // Pull this pin to GND to disable
#define   MOUSE_LEFT_BUTTON_PIN       8  // Pull this pin to GND for left click
#define   MOUSE_RIGHT_BUTTON_PIN      9  // Pull this pin to GND for right click
/**** End of XIAO pins ****/

/* I2C addresses */
#define   DIGIPOT_X_I2C_ADDR       0x28
#define   DIGIPOT_Y_I2C_ADDR       0x29

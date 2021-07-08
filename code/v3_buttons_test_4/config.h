/* ----------------- General config -------------------------------- */
/* Debugging */
#define DEBUG_BUTTONS          true

/* Serial */
#define SERIAL_BAUD_RATE       115200

/* Buttons */
const int buttonamount         = 4;                 // number of buttons connected
int buttons[(buttonamount+1)]  = {14,12,13,4};      // pin button is connected to

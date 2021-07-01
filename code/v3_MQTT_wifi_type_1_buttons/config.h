/* ----------------- General config -------------------------------- */
/* Debugging */
#define DEBUG_BUTTONS          true

/* Serial */
#define SERIAL_BAUD_RATE       115200

/* LED's */
#define LED_PIN                0                    // pin neopixels are connected to -- shouldn't need to be changed
#define LED_COUNT              16                   // number of neopixels
#define LED_TYPE               NEO_GRBW

/* Buttons */
const int buttonamount         = 4;                 // number of buttons connected
int buttons[(buttonamount+1)]  = {14,12,13,4};      // pin button is connected to
const int debounce             = 300;

/* Variables */
int fadespeed                  = 125;               // speed in micros() for color fade mode
int ringspeed                  = 250;               // speed in millis() for ring animation

/* WIFI */
const char* host               = "buttonswitch";    // host name to show on wifi network && mqtt topics
//const char* ssid             = "***";
//const char* password         = "****";

/* MQTT */
const char*   mqtt_broker      = "192.168.0.54";    // IP address or host name of your MQTT broker
const int     mqtt_port        = 1883;

//const char*  mqtt_username     = "****";
//const char*  mqtt_password     = "****";



const uint8_t mqtt_lwt_qos     = 0;
const uint8_t mqtt_lwt_retain  = 1;


/* 
 *  2021-07-08 v0.2.0
 *  wifi and mqtt conenction working as of 12:38 2021-04-22
 *  neopixels working 18:11 2021-04-30
 *  
 *
 *  option - set color    (topic = %hostname%/color; payload = led#, R,G,B,W (0-255))
 *  option fade to color  (topic = %hostname%/fade;  payload = led#, R,G,B,W (0-255))
 *  option ring           (topic = %hostname%/ring;  payload = led#, #ON, R,G,B,W (0-255))
 *  option FWD animation  (topic = %hostname%/fwd;   payload = led#, R,G,B,W,R2,G2,B2,W2,  (0-255))
 *  option BWD animation  (topic = %hostname%/bwd;   payload = led#, R,G,B,W,R2,G2,B2,W2,  (0-255))
 *
 *  button press = button # output on topic %hostname%/button
 *  
 *  online status can be found with %hostname%/LWT
 *  
 *  working button code 2021-07-08
 *  buttons and leds are now 1-based to match LSC 2021-07-08
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>             // For MQTT
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "buttons.h"                  // For button click handling (embedded)

multiButton button = multiButton();
char g_mqtt_message_buffer[64];

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, LED_TYPE + NEO_KHZ800);

/*
 * stuff below here shouldn't need to be changed
 */

  const char* out_topic = "-";
  const char* out_heart = "-";
  const char* in_topic1 = "-";
  const char* in_topic2 = "-";
  const char* in_topic3 = "-";
  const char* in_topic4 = "-";
  const char* in_topic5 = "-";
  char clientoutput[100];
  char clientoutput2[100];
  char clientinput[100];
  char clientinput2[100];
  char clientinput3[100];
  char clientinput4[100];
  char clientinput5[100];
  char connectphrase[100]; // publishes to 'outTopic' when connected

 
// Initialize color variables
int prevR[buttonamount] = {};
int prevG[buttonamount] = {};
int prevB[buttonamount] = {};
int prevW[buttonamount] = {};

int redVal[buttonamount] = {};
int grnVal[buttonamount] = {}; 
int bluVal[buttonamount] = {};
int whiVal[buttonamount] = {};

int rednew[buttonamount] = {};
int grnnew[buttonamount] = {}; 
int blunew[buttonamount] = {};
int whinew[buttonamount] = {};
int rednew1[buttonamount] = {};
int grnnew1[buttonamount] = {}; 
int blunew1[buttonamount] = {};
int whinew1[buttonamount] = {};

int spot[buttonamount] = {0};
int neo_update[buttonamount] = {false};
int fwd = 0;
int fwd_prev = 0;
int bwd = 3;
int bwd_prev = 3;
int ledmode[(buttonamount+1)] = {0};

int r = 0;
int g = 0;
int b = 0;
int w = 0;
int c = 0;
int R = 0;
int G = 0;
int B = 0;
int W = 0;

int SoffitC;
int SoffitS;
int SoffitR;
int SoffitG;
int SoffitB;
int SoffitW;
int SoffitR1;
int SoffitG1;
int SoffitB1;
int SoffitW1;

unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

int connected_update = false;

char * getMqttButtonAction(uint8_t state)
{
  // Determine what action we need to publish
  static char action[7];
  switch (state)
  {
    case BUTTON_HOLD_STATE:
      sprintf_P(action, PSTR("HOLD"));
      break;
    case 1:
      sprintf_P(action, PSTR("SINGLE"));
      break;
    case 2:
      sprintf_P(action, PSTR("DOUBLE"));
      break;
    case 3:
      sprintf_P(action, PSTR("TRIPLE"));
      break;
    case 4:
      sprintf_P(action, PSTR("QUAD"));
      break;
    case 5:
      sprintf_P(action, PSTR("PENTA"));
      break;
    default:
      sprintf_P(action, PSTR("ERROR"));
      break;
  }
  return action;
}

void buttonPressed(uint8_t button, uint8_t state)
{
 
  // Determine the port, switch, and button numbers (1-based)
  uint8_t raw_button =  button;
  uint8_t mqtt_button = raw_button + 1;

  if (DEBUG_BUTTONS)
  {
    Serial.print(F("Press detected: "));
    Serial.print(F(" BUTTON: "));
    Serial.print(mqtt_button);
    Serial.print(F(" STATE: "));
    Serial.print(state);
    Serial.print(F(" ACTION: "));
    Serial.println(getMqttButtonAction(state));
  }

  // Publish event to MQTT
  sprintf_P(g_mqtt_message_buffer, PSTR("{\"BUTTON\":%d, \"ACTION\":\"%s\"}"), mqtt_button, getMqttButtonAction(state));
  client.publish(out_topic, g_mqtt_message_buffer);
}

void setup() {

  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);
//  Serial.println(ESP.getResetReason());
 
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

  settopics();
  WiFi.hostname(host);
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

 for (uint8_t i = 0; i < buttonamount; i++)
  {
   button.setup(i, buttons[i]);
  }

  button.onButtonPressed(buttonPressed);
}

void loop() {
 if (!client.connected()) {
    reconnect();
  }
   client.loop();
   
   if (connected_update == true){ // if we are conencted to wifi and mqtt go green briefly
      success();
    }

    button.process();


  /*
   * 
   * Control leds from incoming mqtt message
   * 
   */

  ringupdate();

    for (int x = 0; x < buttonamount; x ++){ // check each led
        
        if (ledmode[x] == 5){
          if (fwd != fwd_prev){
          FWDring(x,rednew[x],grnnew[x],blunew[x],whinew[x],rednew1[x],grnnew1[x],blunew1[x],whinew1[x]);
         }
        }
        if (ledmode[x] == 4){
          if (bwd != bwd_prev){
          BWDring(x,rednew[x],grnnew[x],blunew[x],whinew[x],rednew1[x],grnnew1[x],blunew1[x],whinew1[x]);
         }
        }
      if (ledmode[x] == 3){ // fade led
        if (neo_update[x] == true){
          timering(x,spot[x],rednew[x],grnnew[x],blunew[x],whinew[x]);
        }
       }
      if (ledmode[x] == 2){ // fade led
        if (neo_update[x] == true){
          crossfadeRGB(x,rednew[x],grnnew[x],blunew[x],whinew[x]);
        }
       }
      if (ledmode[x] == 1){ // just change the color
        if (neo_update[x] == true){
          colorWipe(x,rednew[x],grnnew[x],blunew[x],whinew[x]);
        }
      }
    }

    fwd_prev = fwd;
    bwd_prev = bwd;

}

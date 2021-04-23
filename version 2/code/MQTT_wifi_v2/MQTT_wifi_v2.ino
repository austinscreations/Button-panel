
/* 
 *  2021-04-22 v0.1.1
 *  wifi and mqtt conenction working as of 12:38pm 2021-04-22
 *  neopixels working 13:17 2021-04-23
 *  heartbeat working 14:02 2021-04-23
 *  
 *  option - set color    (topic = color; payload = led#, R,G,B,W (0-255))
 *  option fade to color  (topic = fade;  payload = led#, R,G,B,W (0-255))
 *
 *  button press = button # output on topic %hostname%/button
 *  
 *  heartbeat = "1" every ~15 seconds %hostname%/button
 *  
 *  ***(very rare) still has slight issue of double sending button press when releasing button***
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>

WiFiClient espClient;
PubSubClient client(espClient);


#define LED_PIN     0 // pin neopixels are connected to
#define LED_COUNT  4 // number of neopixels

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

int fadespeed = 125; // speed in micros() for color fade mode
const int debounce = 250;

const int buttonamount = 4; // number of buttons connected
int buttons[(buttonamount+1)] = {14,12,13,4}; // pin button is conencted to

const char* host = "buttonswitch"; // host name to show on wifi network

const char* ssid = "***";
const char* password = "****";
const char* mqtt_server = "192.168.0.**";

const char* mqtt_user = "****";
const char* mqtt_password = "****";

/*
 * stuff below here shouldn't need to be changed
 */

  const char* out_topic = "-";
  const char* out_heart = "-";
  const char* in_topic1 = "-";
  const char* in_topic2 = "-";
  char clientoutput[100];
  char clientoutput2[100];
  char clientinput[100];
  char clientinput2[100];
  char connectphrase[100]; // publishes to 'outTopic' when conencted

 
int buttonstate[(buttonamount+1)] = {0}; // digital read of button state created for each button
int prevbuttonstate[(buttonamount+1)] = {0}; // previous state of button

unsigned long time1 = 0;

const int mod_num = 4; // number of RGB modules being used.

// Initialize color variables
int prevR[mod_num] = {};
int prevG[mod_num] = {};
int prevB[mod_num] = {};
int prevW[mod_num] = {};

int redVal[mod_num] = {};
int grnVal[mod_num] = {}; 
int bluVal[mod_num] = {};
int whiVal[mod_num] = {};

int rednew[mod_num] = {};
int grnnew[mod_num] = {}; 
int blunew[mod_num] = {};
int whinew[mod_num] = {};

int neo_update[mod_num] = {false};
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
int SoffitR;
int SoffitG;
int SoffitB;
int SoffitW;

int y;
unsigned long previousMillis2 = 0;
unsigned long previousheartbeat = 0;

int connected_update = false;



void setup() {

  Serial.begin(115200);
  delay(1000);
//  Serial.println(ESP.getResetReason());
 
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP

  settopics();
  WiFi.hostname(host);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

for (int p = 0; p < buttonamount; p ++){pinMode(buttons[p], INPUT_PULLUP);} // set all buttons to input pullup

}

void loop() {
 if (!client.connected()) {
    reconnect();
  }
   client.loop();
   heartbeat();
   
   if (connected_update == true){ // if we are conencted to wifi and mqtt go greeen briefly
      success();
    }


// check if a button was pressed, and send button number through mqtt
  for (int p = 0; p < buttonamount; p ++){
    buttonstate[p] = digitalRead(buttons[p]); // read current state of all buttons
    
    if (buttonstate[p] == LOW && prevbuttonstate[p] == HIGH && millis() - time1 > debounce) { // confirm button was release from last press and if repressed enough time has passed for debounce
       client.publish(out_topic,String(p).c_str(), false);
      time1 = millis();
    }
  prevbuttonstate[p] = buttonstate[p]; // save last state of buttons
  }


  /*
   * 
   * Control leds from incoming mqtt message
   * 
   */


    for (int x = 0; x < mod_num; x ++){ // check each led
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


  
  

  
}

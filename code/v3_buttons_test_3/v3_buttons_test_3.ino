
/* 
 *  2021-07-01 v0.2
 *    
 *    works on single button 2021-07-03
 *    
 *    _eventtimer - precursor to multi buttons works 2021-07-07
 *    single button in void setup works 2021-07-07
 *    
 *    press detection working using modified lsc button - ready for multi button formatting 2021-07-07
 *    
 *    TO DO
 *      - support multiple buttons
 *         - switch over to allowing setup of telling how many buttons, their GPIO number amd active state
 *         - update then cycles through those interations
 *         - reports back... hopefully
 */

#include "config.h"
#include "buttons.h"               // For button click handling (embedded)

//LSC_Button button[4];

//buttonGPIO buttonGPIO(1);

//char g_mqtt_message_buffer[64];

/*
 * stuff below here shouldn't need to be changed
 */

//int buttonstate[(buttonamount+1)] = {0}; // digital read of button state created for each button
//int prevbuttonstate[(buttonamount+1)] = {0}; // previous state of button

  mdPushButton button = mdPushButton();

//void ButtonPressed(int clicks) {
//  switch (clicks) {
//    case -1: Serial.println("Long button press");   break;
//    case  1: Serial.println("Button pressed once"); break;
//  default  : Serial.print("Button pressed "); Serial.print(clicks); Serial.println(" times"); break;
//  }
//}

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
// Serial.println("hi");
 
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
//  sprintf_P(g_mqtt_message_buffer, PSTR("{\"BUTTON\":%d, \"ACTION\":\"%s\"}"), mqtt_button, getMqttButtonAction(state));
//  client.publish(out_topic, g_mqtt_message_buffer);
}


void setup() {

  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);
    Serial.println("\nsetup() starting...");

//  Serial.println(ESP.getResetReason());


button.setup(buttons[0]);
//button.setup(1, buttons[0]);


//for (int p = 0; p < buttonamount; p ++)
//  {
//    pinMode(buttons[p], INPUT_PULLUP);// set all buttons to input pullup
//    buttonGPIO.settings(p, LOW); // setup the active state for a button (button # , active state)
//  }

//  buttonGPIO.settings(0, LOW); // setup the active state for a button (button # , active state)

}

void loop() {
  
button.process();

//switch (int clicks = button.status()) {
//    case -3: /* ignore this case */; break;
//    case -2: Serial.println("HOLD"); break;
//    case -1: Serial.println("Long button press"); break;
//    case  0: /* ignore this case */; break;
//    case  1: Serial.println("Button pressed once"); break;
//  default  : Serial.print("Button pressed "); Serial.print(clicks); Serial.println(" times"); break;
//  }
//  delay(40 + random(21)); // rest of loop takes 40 to 60 ms to execute 





  

// check if a button was pressed, and send button number through mqtt
//for (int p = 0; p < buttonamount; p ++)
//  {
//    buttonstate[p] = digitalRead(buttons[p]); // read current state of all buttons
//    button[p].process(p, buttonstate[p]); 
//  }

//for (int p = 0; p < buttonamount; p ++)
//{
//  buttonGPIO.process(0, buttons[0]); 
//}

//delay(2500);

}

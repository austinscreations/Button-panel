
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
 *    single button working for mqtt readout (via serial) - 2021-07-07
 *    multiple buttons working for mqtt readout (via serial) - 2021-07-08
 *    
 *    TO DO
 *      - reports PENTA after HOLD
 */

#include "config.h"
#include "buttons.h"               // For button click handling (embedded)

//char g_mqtt_message_buffer[64];

mdPushButton button = mdPushButton();

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
//  sprintf_P(g_mqtt_message_buffer, PSTR("{\"BUTTON\":%d, \"ACTION\":\"%s\"}"), mqtt_button, getMqttButtonAction(state));
//  client.publish(out_topic, g_mqtt_message_buffer);
}

void setup() {

  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);
    Serial.println("\nsetup() starting...");

//  Serial.println(ESP.getResetReason());

button.setup(0, buttons[0]);
button.setup(1, buttons[1]);

button.onButtonPressed(buttonPressed);

}

void loop() {
  
button.process();


}

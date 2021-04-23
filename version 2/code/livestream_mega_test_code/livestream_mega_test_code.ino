/*
 * 
 * working as of 2021-04-21 v1.0.0
 * 
 */


const int buttonamount = 4; // number of buttons connected
int buttons[(buttonamount+1)] = {4,5,6,7}; // pin button is conencted to
int buttonstate[(buttonamount+1)] = {0}; // digital read of button state created for each button


void setup() {

pinMode(LED_BUILTIN, OUTPUT);

for (int p = 0; p < buttonamount; p ++){pinMode(buttons[p], INPUT_PULLUP);} // set all buttons to input pullup

}

void loop() {
  
 for (int p = 0; p < (buttonamount); p ++){buttonstate[p] = digitalRead(buttons[p]);} // read current state of all buttons
 
  if (ledON()){digitalWrite(LED_BUILTIN, HIGH);} // button is pressed, turn on led
    else{digitalWrite(LED_BUILTIN, LOW);} // no button is being pressed turn led off

}

boolean ledON(){
  for (int y = 0; y < (buttonamount); y++){
    if (buttonstate[y] == 0){return true;}    // has a button been pressed?
  } 
  return false;
}

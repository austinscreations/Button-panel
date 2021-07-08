/*
 * buttons.h
 * 
 * A push button Arduino library capable of returning the number of
 * consecutive button presses made in quick succession or if the 
 * button was held down for a long time. 
 * 
 * Based on LSC_Button by ben.jones12@gmail.com, forked from mdButton library
 * Based on mdPushButton by Michel Deslierres <sigmdel.ca/michel>
 * 
 */

 #ifndef BUTTONS_H
#define BUTTONS_H


#include "Arduino.h"  // needed for platformIO

// May need to define this macro in Arduino IDE if a value != 0 is desired
#ifndef DEBUG_PUSH_BUTTON
#define DEBUG_PUSH_BUTTON 0  // 0 - no debugging, 1 - printSetup() available, 2 adds state machine debugging
#endif

#define DEBOUNCE_PRESS_TIME      15  // delay to debounce the make part of the signal
#define DEBOUNCE_RELEASE_TIME    30  // delay to debounce the break part of the signal
#define MULTI_CLICK_TIME        250  // if 0, does not check for multiple button clicks
#define HOLD_TIME               500  // minimum time of button press for mdButton.status() to return a -1 (long button press)
                                             // all times in milliseconds

// Special state values
#define BUTTON_NO_STATE          0
#define BUTTON_HOLD_STATE       15

// Max number of clicks we support (won't report more even if button clicked more often)
#define BUTTON_MAX_CLICKS        5

#define BUTTON_COUNT             4

typedef void (*buttonPressedCallback)(uint8_t, uint8_t);

enum buttonState_t { AWAIT_PRESS, DEBOUNCE_PRESS, AWAIT_RELEASE, DEBOUNCE_RELEASE, AWAIT_MULTI_PRESS };

union buttonData_t
{
  uint8_t _data;
  struct 
  {
    buttonState_t state  : 4;
    uint8_t clicks : 4;
  } data;
};


class mdPushButton {
  public:
    mdPushButton();  //constructor
    
    void setup(uint8_t id, uint8_t pin, uint8_t active = LOW, bool useInternalPullResistor = true); // setup input pin
//    void setup(uint8_t buttonnum, uint8_t pin, uint8_t active = LOW, bool useInternalPullResistor = true); // setup input pin
    
    // Current library version
    int16_t version;

    // status, number of clicks since last update
    // -1 = button held, 0 = button not pressed, 1, 2, ... number of times button pressed
//    int status();

//    void process();
    void process();

    // Set callback function to be called when the button has been pressed   
//    void OnButtonClicked(callback_int); // only one push button, or using separate click handlers for each button

    void onButtonPressed(buttonPressedCallback);

   
  private:
    uint8_t _pin[BUTTON_COUNT];;    
    uint8_t _active[BUTTON_COUNT];;

    buttonPressedCallback _onButtonPressed;

    uint32_t _lastUpdateTime;
    
//    uint8_t _BUTTON_COUNT;   // number of buttons connected
    buttonData_t _buttonState[BUTTON_COUNT];

    uint16_t _eventTime[BUTTON_COUNT];
  
//    callback_int _OnClick1;

    uint8_t * _update();


   
};

#endif

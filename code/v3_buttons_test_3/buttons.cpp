/*
 * buttons.cpp
 * 
 * A push button Arduino library capable of returning the number of
 * consecutive button presses made in quick succession or if the 
 * button was held down for a long time. 
 * 
 * Based on LSC_Button by ben.jones12@gmail.com, forked from mdButton library
 * Based on mdPushButton by Michel Deslierres <sigmdel.ca/michel>
 * 
 */

#include "Arduino.h"
#include "buttons.h"


#define VERSION 0x0002

// If active = LOW (the default) then the input must be pulled high most of the time
//   This can be done with the internal pullup (set pullup = true which is also the default value) 
//   or an external pull up resistor say 4.7K + connected to the  GPIO pin and Vcc
//
// If active = HIGH then the input must be pulled low most of the time
//   This can be done with the internal pulldown (set pullup = true which is also the default value) 
//   or an external pull down resistor say 4.7K + connected to the  GPIO pin and Vcc

mdPushButton::mdPushButton(){}

void mdPushButton::setup(uint8_t pin, uint8_t active, bool useInternalPullResistor) {

  _pin = pin;
  _active = active;

  int mode = INPUT;
  if (useInternalPullResistor) {
    if (active == LOW)
      mode = INPUT_PULLUP;
    else {
      // mode = INPUT_PULLDOWN where defined
      #if defined(INPUT_PULLDOWN) 
        mode = INPUT_PULLDOWN;
      #elif defined(ESP8266)
        if (pin == 16) mode = INPUT_PULLDOWN_16;
      #endif  
    }
  }

   pinMode(_pin, mode);
  _buttonState.data.state = AWAIT_PRESS;
}

//void mdPushButton::OnButtonClicked( callback_int cb ){_OnClick1 = cb;}

void mdPushButton::onButtonPressed(buttonPressedCallback callback)
{ 
  _onButtonPressed = callback; 
}

void mdPushButton::process() 
{
  // Process each input to see what, if any, events have occured
  uint8_t state = _update();

  // Check if we have a callback to handle the press events
//  if (_onButtonPressed) 
//  {
//    for (uint8_t i = 0; i < BUTTON_COUNT; i++)
//    {
      // Only interested in buttons with events to report
      if (state != BUTTON_NO_STATE) {
        Serial.println(state);                                          // <<<<<<<<<<<<<<<<<<<<<<<<<<< showing correct data but no callback
        _onButtonPressed(0, state);
      }
//    }
//  }
}

uint8_t mdPushButton::_update()
{
   
  // Work out how long since our last update so we can increment the event times for each button
  uint16_t delta = millis() - _lastUpdateTime;
  _lastUpdateTime = millis();
  
    // Increment the event time for this button
    _eventTime = _eventTime + delta;
    
    // AWAIT_PRESS
    if (_buttonState.data.state == AWAIT_PRESS) 
    {
      _buttonState.data.clicks = 0;
      if (digitalRead(_pin) == _active)
      {
        _buttonState.data.state = DEBOUNCE_PRESS;
        _eventTime = 0;
      }
    }
    // DEBOUNCE_PRESS
    else if (_buttonState.data.state == DEBOUNCE_PRESS) 
    {
      if (_eventTime > DEBOUNCE_PRESS_TIME) 
      {
        _buttonState.data.state = AWAIT_RELEASE;
        _eventTime = 0;
      }
    }
    // AWAIT_RELEASE
    else if (_buttonState.data.state == AWAIT_RELEASE) 
    {
      if (!(digitalRead(_pin) == _active)) 
      {
        _buttonState.data.state = DEBOUNCE_RELEASE;
        _eventTime = 0;
      }
      else
      {
        if (_eventTime > HOLD_TIME)
        {
          _buttonState.data.clicks = BUTTON_HOLD_STATE ;
          _eventTime = 0;
//          Serial.println("i was held");
//          state = BUTTON_HOLD_STATE;
         return BUTTON_HOLD_STATE;
        }
      }
    }
    // DEBOUNCE_RELEASE
    else if (_buttonState.data.state == DEBOUNCE_RELEASE) 
    {
      if (_eventTime > DEBOUNCE_RELEASE_TIME) 
      {
        if (_buttonState.data.clicks == BUTTON_HOLD_STATE ) 
        {
          _buttonState.data.state = AWAIT_PRESS;
          return 0;
        }
          _buttonState.data.clicks = min(BUTTON_MAX_CLICKS, _buttonState.data.clicks + 1);
//          _buttonState.data.clicks += 1;
          _buttonState.data.state = AWAIT_MULTI_PRESS;
//          Serial.println("i had multipress");
          _eventTime = 0; 
        }
      }
    
    // AWAIT_MULTI_PRESS
    else if (_buttonState.data.state == AWAIT_MULTI_PRESS) 
    { 
      if (digitalRead(_pin) == _active)
      {
        _buttonState.data.state = DEBOUNCE_PRESS;
        _eventTime = 0;
      } 
      else if (_eventTime > MULTI_CLICK_TIME) 
      {
        _buttonState.data.state = AWAIT_PRESS;
        return _buttonState.data.clicks;
//          state = _buttonState.data.clicks;
      }
    }
  

  return 0;
}

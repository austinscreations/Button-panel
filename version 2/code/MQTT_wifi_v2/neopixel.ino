// animations for neopixel control

int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1. 
*  (R, G, and B are each calculated separately.)
*/

int calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a     value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a 
*  0-255 range, then loops 1020 times, checking to see if  
*  the value needs to be updated each time, then writing
*  the color values to the correct pins.
*/

void crossfadeRGB(int c,uint8_t r,uint8_t g,uint8_t b,uint8_t w) {
    
  int stepR = calculateStep(prevR[c], r);
  int stepG = calculateStep(prevG[c], g); 
  int stepB = calculateStep(prevB[c], b);
  int stepW = calculateStep(prevW[c], w);


 for (int i = 0; i <= 1020; i++) {
  if (micros() - previousMillis2 >= fadespeed) {
    previousMillis2 = micros();
    redVal[c] = calculateVal(stepR, redVal[c], i);
    grnVal[c] = calculateVal(stepG, grnVal[c], i);
    bluVal[c] = calculateVal(stepB, bluVal[c], i);
    whiVal[c] = calculateVal(stepW, whiVal[c], i);
  }
 }

for (int j = (0+c); j <= (3+c); j++) {
 R = redVal[c]; // changes from a 255 value to a 16 bit value as the PWM driver outputs a 16bit pulse
 G = grnVal[c];
 B = bluVal[c];
 W = whiVal[c];
 strip.setPixelColor(c,R,G,B,W);         //  Set pixel's color (in RAM)
 strip.show();
 }
  
  prevR[c] = redVal[c]; 
  prevG[c] = grnVal[c]; 
  prevB[c] = bluVal[c];
  prevW[c] = whiVal[c];

  if (r == redVal[c] && g == grnVal[c] && b == bluVal[c] && w == whiVal[c]){
    neo_update[c] = false;
  }
}


void colorWipe(int c,uint8_t r,uint8_t g,uint8_t b,uint8_t w){
  for(int a=0; a<4; a++) {
    strip.setPixelColor(c,r,g,b,w);         //  Set pixel's color (in RAM)
    strip.show();
   }
  prevR[c] = r; 
  prevG[c] = g; 
  prevB[c] = b;
  prevW[c] = w;
  neo_update[c] = false;
}

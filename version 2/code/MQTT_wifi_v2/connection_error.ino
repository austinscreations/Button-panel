// color animation once conencted, and heartbeat for mqtt

void heartbeat(){ // send heartbeat via mqtt
  if (millis() - previousheartbeat >= 15000) {
    previousheartbeat = millis();
    client.publish(out_heart,"1", false);
 }
}

void success(){ // all green - with delay
 for (int c=0; c<mod_num; c++){
  for(int a=0; a<4; a++) {
    strip.setPixelColor(c,0,255,0,0);         //  Set pixel's color (in RAM)
    strip.show();
   }
 }
 delay(1000);
  for (int c=0; c<mod_num; c++){
  for(int a=0; a<4; a++) {
    strip.setPixelColor(c,0,0,0,0);         //  Set pixel's color (in RAM)
    strip.show();
   }
 }
 connected_update = false;
}

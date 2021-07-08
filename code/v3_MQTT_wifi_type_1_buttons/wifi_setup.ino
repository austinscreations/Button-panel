// wifi setup information


void settopics(){ // sets mqtt topics based on hostname
  // *** outputs *** //
  strcpy(clientoutput, host);
  strcat(clientoutput,"/button");

  strcpy(clientoutput2, host);
  strcat(clientoutput2,"/LWT");

  // *** inputs ***  //
  strcpy(clientinput, host);
  strcat(clientinput,"/rgbw");

  strcpy(clientinput2, host);
  strcat(clientinput2,"/fade");
  
  strcpy(clientinput3, host);
  strcat(clientinput3,"/ring");
  
  strcpy(clientinput4, host);
  strcat(clientinput4,"/bwd");
  
  strcpy(clientinput5, host);
  strcat(clientinput5,"/fwd");
  
  out_topic = clientoutput;
  out_heart = clientoutput2;
  in_topic1 = clientinput;
  in_topic2 = clientinput2;
  in_topic3 = clientinput3;
  in_topic4 = clientinput4;
  in_topic5 = clientinput5;

  Serial.println(out_topic);
  Serial.println(out_heart);
  Serial.println(in_topic1);
  Serial.println(in_topic2);
  Serial.println(in_topic3);
  Serial.println(in_topic4);
  Serial.println(in_topic5);
}


void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
 payload[length] = '\0';
   Serial.print("payload: [");
   Serial.print((char *)payload);
   Serial.println("]");


if (strcmp(topic,in_topic1)==0){ // call to set regular rgb color

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
SoffitC = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW = value.substring(iStart, iEnd).toInt();

    Serial.print("LED #: ");
    Serial.println(SoffitC);

    Serial.print("RED: ");
    Serial.println(SoffitR);

    Serial.print("GREEN: ");
    Serial.println(SoffitG);

    Serial.print("BLUE: ");
    Serial.println(SoffitB); 

    Serial.print("WHITE: ");
    Serial.println(SoffitW); 

    if (SoffitC != 0){
    ledmode[(SoffitC-1)] = 1; // set led to normal color
    neo_update[(SoffitC-1)] = true; // time to update the neopixel
     rednew[(SoffitC-1)] = {SoffitR};
     grnnew[(SoffitC-1)] = {SoffitG}; 
     blunew[(SoffitC-1)] = {SoffitB};
     whinew[(SoffitC-1)] = {SoffitW};
  }
}

if (strcmp(topic,in_topic2)==0){ // call to set fade rgb color

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
SoffitC = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW = value.substring(iStart, iEnd).toInt();

    Serial.print("LED #: ");
    Serial.println(SoffitC);

    Serial.print("RED: ");
    Serial.println(SoffitR);

    Serial.print("GREEN: ");
    Serial.println(SoffitG);

    Serial.print("BLUE: ");
    Serial.println(SoffitB); 

    Serial.print("WHITE: ");
    Serial.println(SoffitW); 

    if (SoffitC != 0){
    ledmode[(SoffitC-1)] = 2; // set led to fade color
    neo_update[(SoffitC-1)] = true; // time to update the neopixel
     rednew[(SoffitC-1)] = {SoffitR};
     grnnew[(SoffitC-1)] = {SoffitG}; 
     blunew[(SoffitC-1)] = {SoffitB};
     whinew[(SoffitC-1)] = {SoffitW};
  }
}

if (strcmp(topic,in_topic3)==0){ // call to set ring

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
SoffitC = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitS = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW = value.substring(iStart, iEnd).toInt();

    Serial.print("LED #: ");
    Serial.println(SoffitC);

    Serial.print("Spot #: ");
    Serial.println(SoffitS);

    Serial.print("RED: ");
    Serial.println(SoffitR);

    Serial.print("GREEN: ");
    Serial.println(SoffitG);

    Serial.print("BLUE: ");
    Serial.println(SoffitB); 

    Serial.print("WHITE: ");
    Serial.println(SoffitW); 

    if (SoffitC != 0){
    ledmode[(SoffitC-1)] = 3; // set led to ring color
    neo_update[(SoffitC-1)] = true; // time to update the neopixel
     spot[(SoffitC-1)] = {SoffitS};
     rednew[(SoffitC-1)] = {SoffitR};
     grnnew[(SoffitC-1)] = {SoffitG}; 
     blunew[(SoffitC-1)] = {SoffitB};
     whinew[(SoffitC-1)] = {SoffitW};
  }
}

if (strcmp(topic,in_topic4)==0){ // call to set bwd ring animation

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
SoffitC = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW1 = value.substring(iStart, iEnd).toInt();

    Serial.print("LED #: ");
    Serial.println(SoffitC);

    Serial.print("RED: ");
    Serial.println(SoffitR);

    Serial.print("GREEN: ");
    Serial.println(SoffitG);

    Serial.print("BLUE: ");
    Serial.println(SoffitB); 

    Serial.print("WHITE: ");
    Serial.println(SoffitW); 

    Serial.print("RED2: ");
    Serial.println(SoffitR1);

    Serial.print("GREEN2: ");
    Serial.println(SoffitG1);

    Serial.print("BLUE2: ");
    Serial.println(SoffitB1); 

    Serial.print("WHITE2: ");
    Serial.println(SoffitW1);

    if (SoffitC != 0){
    ledmode[(SoffitC-1)] = 4; // set led to fade color
     rednew[(SoffitC-1)] = {SoffitR};
     grnnew[(SoffitC-1)] = {SoffitG}; 
     blunew[(SoffitC-1)] = {SoffitB};
     whinew[(SoffitC-1)] = {SoffitW};
     rednew1[(SoffitC-1)] = {SoffitR1};
     grnnew1[(SoffitC-1)] = {SoffitG1}; 
     blunew1[(SoffitC-1)] = {SoffitB1};
     whinew1[(SoffitC-1)] = {SoffitW1};
  }
}

  if (strcmp(topic,in_topic5)==0){ // call to set fwd ring animation

String value = String((char*)payload);

int iStart, iEnd;
iStart = 0;
iEnd = value.indexOf(',', iStart);
SoffitC = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitR1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitG1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitB1 = value.substring(iStart, iEnd).toInt();
iStart = iEnd + 1;
iEnd = value.indexOf(',', iStart);
SoffitW1 = value.substring(iStart, iEnd).toInt();

    Serial.print("LED #: ");
    Serial.println(SoffitC);

    Serial.print("RED: ");
    Serial.println(SoffitR);

    Serial.print("GREEN: ");
    Serial.println(SoffitG);

    Serial.print("BLUE: ");
    Serial.println(SoffitB); 

    Serial.print("WHITE: ");
    Serial.println(SoffitW); 

    Serial.print("RED2: ");
    Serial.println(SoffitR1);

    Serial.print("GREEN2: ");
    Serial.println(SoffitG1);

    Serial.print("BLUE2: ");
    Serial.println(SoffitB1); 

    Serial.print("WHITE2: ");
    Serial.println(SoffitW1);

    if (SoffitC != 0){
    ledmode[(SoffitC-1)] = 5; // set led to fade color
     rednew[(SoffitC-1)] = {SoffitR};
     grnnew[(SoffitC-1)] = {SoffitG}; 
     blunew[(SoffitC-1)] = {SoffitB};
     whinew[(SoffitC-1)] = {SoffitW};
     rednew1[(SoffitC-1)] = {SoffitR1};
     grnnew1[(SoffitC-1)] = {SoffitG1}; 
     blunew1[(SoffitC-1)] = {SoffitB1};
     whinew1[(SoffitC-1)] = {SoffitW1};
  }
 }
  
  
   
}

void reconnect() {
  
  // Loop until we're reconnected
  while (!client.connected()) {
   for (int c=0; c<buttonamount; c++){
      strip.setPixelColor(0+(4*c),0,0,0,255); 
      strip.show();
      }

    Serial.print("Attempting MQTT connection...");
    if (client.connect(host,mqtt_username,mqtt_password,out_heart, mqtt_lwt_qos, mqtt_lwt_retain, "0")) {
      Serial.println("mqtt connected");
      connected_update = true;
      // Once connected, publish an announcement...
      strcpy(connectphrase, "connected = ");
      strcat(connectphrase, host);
      const char* phrase = connectphrase;
      client.publish("outTopic",phrase);
      byte lwt_payload[] = { '1' };
      client.publish(out_heart, lwt_payload, 1, mqtt_lwt_retain);
      // ... and resubscribe
      client.subscribe(in_topic1);
      client.subscribe(in_topic2);
      client.subscribe(in_topic3);
      client.subscribe(in_topic4);
      client.subscribe(in_topic5);

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
//       Wait 5 seconds before retrying
      delay(5000);
     }
  }
}

void setup_wifi() {
  delay(10);
//   We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    for (int c=0; c<buttonamount; c++){
    strip.setPixelColor(0+(4*c),255,0,0,0); 
    strip.show();
    }
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

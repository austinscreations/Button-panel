// wifi setup information

void settopics(){ // sets mqtt topics based on hostname
  strcpy(clientoutput, host);
  strcat(clientoutput,"/button");

  strcpy(clientoutput2, host);
  strcat(clientoutput2,"/heartbeat");

  strcpy(clientinput, host);
  strcat(clientinput,"/rgbw");

  strcpy(clientinput2, host);
  strcat(clientinput2,"/fade");
  
  out_topic = clientoutput;
  out_heart = clientoutput2;
  in_topic1 = clientinput;
  in_topic2 = clientinput2;

  Serial.println(out_topic);
  Serial.println(out_heart);
  Serial.println(in_topic1);
  Serial.println(in_topic2);
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

    ledmode[SoffitC] = 1; // set led to normal color
    neo_update[SoffitC] = true; // time to update the neopixel
     rednew[SoffitC] = {SoffitR};
     grnnew[SoffitC] = {SoffitG}; 
     blunew[SoffitC] = {SoffitB};
     whinew[SoffitC] = {SoffitW};
  }

if (strcmp(topic,in_topic2)==0){ // call to set regular rgb color

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

    ledmode[SoffitC] = 2; // set led to fade color
    neo_update[SoffitC] = true; // time to update the neopixel
     rednew[SoffitC] = {SoffitR};
     grnnew[SoffitC] = {SoffitG}; 
     blunew[SoffitC] = {SoffitB};
     whinew[SoffitC] = {SoffitW};
  }
   
}

void reconnect() {
  
  // Loop until we're reconnected
  while (!client.connected()) {
   for (int c=0; c<mod_num; c++){
      strip.setPixelColor(0+(4*c),0,0,0,255); 
      strip.show();
      }

    Serial.print("Attempting MQTT connection...");
    if (client.connect(host,mqtt_user,mqtt_password)) {
      Serial.println("mqtt connected");
      connected_update = true;
      // Once connected, publish an announcement...
      strcpy(connectphrase, "connected = ");
      strcat(connectphrase, host);
      const char* phrase = connectphrase;
      client.publish("outTopic",phrase);
      // ... and resubscribe
      client.subscribe(in_topic1);
      client.subscribe(in_topic2);

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
    for (int c=0; c<mod_num; c++){
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

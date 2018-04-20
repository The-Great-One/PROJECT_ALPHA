#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"

// prototypes
boolean connectWifi();

//on/off callbacks 
bool s1On();
bool s1Off();
bool s2On();
bool s2Off();
bool s3On();
bool s3Off();
bool s4On();
bool s4Off();

// Change this before you flash
const char* ssid = "****";
const char* password = "****";
const int relayS1Pin = 14;
const int relayS2Pin = 12;
const int relayS3Pin = 13;
const int relayS4Pin = 15;

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *s1 = NULL;
Switch *s2 = NULL;
Switch *s3 = NULL;
Switch *s4 = NULL;

bool iss1On = false;
bool iss2On = false;
bool iss3On = false;
bool iss4On = false;


void setup()
{
  Serial.begin(9600);
   
  // Initialise wifi connection
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    upnpBroadcastResponder.beginUdpMulticast();
    
  
  // Inside void setup() 
  pinMode(relayS1Pin, OUTPUT);
  pinMode(relayS2Pin, OUTPUT);
  pinMode(relayS3Pin, OUTPUT);
  pinMode(relayS4Pin, OUTPUT);
    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    s1 = new Switch("office", 80, s1On, s1Off);
    s2 = new Switch("kitchen", 81, s2On, s2Off);
    s3 = new Switch("fan", 82, s3On, s3Off);
    s4 = new Switch("tv", 83, s4On, s4Off);

    Serial.println("Adding switches upnp broadcast responder");
  upnpBroadcastResponder.addDevice(*s1);
  upnpBroadcastResponder.addDevice(*s2);
  upnpBroadcastResponder.addDevice(*s3);
  upnpBroadcastResponder.addDevice(*s4);

  }
}
 
void loop()
{
	 if(wifiConnected){
      upnpBroadcastResponder.serverLoop();
      
      s1->serverLoop();
      s2->serverLoop();
      s3->serverLoop();
      s4->serverLoop();

      
	 }
}
//void s1On() {
//  digitalWrite(s1, HIGH); // turn on relay with voltage HIGH 
//}
//
//void s1Off() {
//  digitalWrite(s1, LOW); // turn off relay with voltage LOW 
//}
//
//void s2On() {
//  digitalWrite(s2, HIGH); // turn on relay with voltage HIGH 
//}
//
//void s2Off() {
//  digitalWrite(s2, LOW); // turn on relay with voltage LOW
//}
//
//void s3On() {
//  digitalWrite(s3, HIGH); // turn on relay with voltage HIGH 
//}
//
//void s3Off() {
//  digitalWrite(s3, LOW); // turn on relay with voltage HIGH 
//}
//
//void s4On() {
//  digitalWrite(s3, HIGH); // turn on relay with voltage HIGH 
//}
//
//void s4Off() {
//  digitalWrite(s4, LOW); // turn on relay with voltage HIGH 
//}
bool s1On() {
    Serial.println("Switch 1 turn on ...");
    
    iss1On = true;    
    return iss1On;
}

bool s1Off() {
    Serial.println("Switch 1 turn off ...");

    iss1On = false;
    return iss1On;
}

bool s2On() {
    Serial.println("Switch 2 turn on ...");

    iss2On = true;
    return iss2On;
}

bool s2Off() {
  Serial.println("Switch 2 turn off ...");

  iss2On = false;
  return iss2On;
}

bool s3On() {
    Serial.println("Switch 3 turn on ...");

    iss3On = true;
    return iss3On;
}

bool s3Off() {
  Serial.println("Switch 3 turn off ...");

  iss3On = false;
  return iss3On;
}

bool s4On() {
    Serial.println("Switch 4 turn on ...");

    iss4On = true;
    return iss4On;
}

bool s4Off() {
  Serial.println("Switch 4 turn off ...");

  iss4On = false;
  return iss4On;
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10){
      state = false;
      break;
    }
    i++;
  }
  
  if (state){
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }
  
  return state;
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#define USE_SERIAL Serial

const char* ssid     = "SmartMushroomBox";            //Set ssid
const char* password = "12345678";                    //Set Password
const char* Server   = "192.168.0.102";           //set Server Domain or Server ip

ESP8266WiFiMulti WiFiMulti;

int motion = 4;

void setup() 
{
  USE_SERIAL.begin(115200);
      for(uint8_t t = 6; t > 0; t--) 
      {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
      }
    WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
    WiFi.begin(ssid, password);         //Set starting for Wifi
    Serial.println(WiFi.localIP());

}

void loop() 
{
  int value=digitalRead(motion);
  if(value==HIGH)
  {
    Serial.println("Alarm!!");
  }
  else
  {
    Serial.println("NO_Alarm!!");
  }
  delay(1000);
}

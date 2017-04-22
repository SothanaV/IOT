#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
////////////////////////////////////////////////////////////////////////////////
//////////Define Pin///////////////////////////////////////////////////////////
#define USE_SERIAL Serial
/////////////////-----------------------------------//////////////////////////
int Pump = 4;             //setpin of AC_Pump at D2
int Valve = 5;               //setpin of pump to D1
//int Led_Red = 14;            //setpin of Led Red at D5
//int Led_Green = 12;            //setpin of Led Red at D6
//int Led_Blue = 13;            //setpin of Led Red at D7
///////////////////////////////////////////////////////////////////////////////
void SendData(int n);     //Define Senddata Voide

////////////Setup//////////////////////////////////////////////////////////////

const char* ssid     = "true_home2G_792";            //Set ssid
const char* password = "ilovestudy";                    //Set Password
const char* Server   = "192.168.1.49";           //set Server Domain or Server ip
ESP8266WiFiMulti WiFiMulti;


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

    ////////////////////////////////SetuoPinMode//////////////////////////////////////////
    pinMode(Pump,OUTPUT);
    pinMode(Valve,OUTPUT);
    
                                            
}

////////////////////Loop////////////////////////////////////////////////////////////////////

void loop() 
{
    int n = 0 ;
    SendData(n);

}

///////////////////////SednData//////////////////////////////////////////////////////////////////
void SendData(int n) 
{
  
  // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        String str = "http://" +String(Server)+":5000" +"/data/" + String(n);
        Serial.println(str);
        http.begin(str);
        int httpCode = http.GET();
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
              {
                String payload = http.getString();
      //-------------------Control----------------------------//
                USE_SERIAL.print("payload");
                USE_SERIAL.println(payload);
                String x = payload.substring(4,7);
                Serial.println(payload.substring(0,3));
                Serial.println(payload.substring(4,7));
                  if(payload.substring(0,3)=="101")
                    {
                     //OnCooler;
                     digitalWrite(Pump,HIGH);
                     Serial.println("OnPump");
                    }
                   if(payload.substring(4,7)=="201")
                    {
                      //OnPump;
                      digitalWrite(Valve,HIGH);
                      Serial.println("OnValve");                    
                    }
                   if(payload.substring(0,3)=="100")
                    {
                      //OffCooler;
                      digitalWrite(Pump,LOW);
                      Serial.println("OffPump");
                    }
                   if(payload.substring(4,7)=="200")
                    {
                      //OffPump;
                      digitalWrite(Valve,LOW);
                      Serial.println("OffValve");
                    }
              }
        }
        http.end();
    }
    delay(1000);
}





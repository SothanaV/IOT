#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid     = "iot2";                         //Set ssid
const char* password = "12345678";                                //Set Password
const char* Server   = "192.168.137.1";                           //set Server Domain or Server ip
const char* port     = "5000";                                    //set server port
ESP8266WiFiMulti WiFiMulti;

#include <Adafruit_NeoPixel.h>
#define PIN 2
#define NUM_LEDS 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{
 Serial.begin(115200);
 WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
 WiFi.begin(ssid, password);         //Set starting for Wifi
 for(int t=5;t>0;t--)
  {
    Serial.print("[SETUP]:");
    Serial.println(t);
    WiFi.begin(ssid, password);
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  dht.begin();

  strip.begin();
  strip.show();
  
}

void loop() 
{
  if((WiFiMulti.run() == WL_CONNECTED))
  {
    HTTPClient http;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(t) || isnan(h)) 
    {
    Serial.println("Failed to read from DHT");
    } 
    else 
    {
      
    Serial.print("Humidity:    ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");
    
    String str = "http://" +String(Server)+":"+String(port)+"/data/"+t+"/"+h+"/";
    Serial.println(str);
    http.begin(str);
    int httpCode = http.GET();
    Serial.print("[HTTP] GET... code:");
    Serial.println(httpCode);
      if(httpCode > 0) 
      {
        if(httpCode == HTTP_CODE_OK) 
        {
          if(httpCode == 200)
          {
            String payload = http.getString();
            Serial.println(payload);
            int red = payload.substring(0,4).toInt();
            int green = payload.substring(5,9).toInt();
            int blue = payload.substring(10,14).toInt();
            neoPixel(red,green,blue);
//            Serial.println(red);              
          }
        }
      }
    
    }
    
  }

}

void neoPixel(int red,int green,int blue)
{
  strip.setPixelColor(0, red, green, blue);
  strip.show();
}


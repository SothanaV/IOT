#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);
const char* ssid     = "iot2";                         //Set ssid
const char* password = "12345678";                    //Set Password
const char* Server   = "192.168.137.1";           //set Server Domain or Server ip
const char* port     = "5000";                       //set server port
ESP8266WiFiMulti WiFiMulti;
void setup() 
{
   Serial.begin(115200);
 WiFiMulti.addAP(ssid, password);    //Set SSID and Password (SSID, Password)
  WiFi.begin(ssid, password);         //Set starting for Wifi
  Serial.println(WiFi.localIP());
  lcd.begin();
  for(int t=5;t>0;t--)
  {
    Serial.print("[SETUP]:");
    Serial.println(t);
    delay(1000);
  }

}

void loop() 
{
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        String str = "http://" +String(Server)+":"+String(port)+"/text";
        Serial.println(str);
        http.begin(str);
        int httpCode = http.GET();
        Serial.print("[HTTP] GET... code:");
        Serial.println(httpCode);
          if(httpCode > 0) 
          {
            if(httpCode == HTTP_CODE_OK) 
              {
                String payload = http.getString();
                Serial.println(payload);
                lcd.setCursor(0, 0);
                lcd.print(payload);
                delay(1000);
                lcd.clear();
              }
          }
    }

}

int pin[] = {16,5,4,0,2,14,12,13,15};

// MARK : Wifi
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
const char *ssid = "ois";
const char *password = "ilovestudy";

// MARK : OTA
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// MARK : Neopixel LED
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, pin[5], NEO_GRB + NEO_KHZ800);
void led(int r,int g,int b){
  if(r>255) r=0;
  if(g>255) g=0;
  if(b>255) b=0;
  pixels.setPixelColor(0, pixels.Color(r,g,b));
  pixels.show();
}

// MARK : DHT
#include "DHT.h"
#define DHTPIN pin[6]
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MARK : My Library
#include "motor.h"
#include "init.h"

// MARK : System Setup
void setup() {
  motor.init();
	Init(); 
}

// MARK : System Loop
void loop() {
  ArduinoOTA.handle();
	server.handleClient();
}

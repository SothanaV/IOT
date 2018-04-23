#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//define NeoPixel Pin and Number of LEDs
#define PIN 16
#define NUM_LEDS 1
//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
void setup() 
{
  // start the strip and blank it out
  strip.begin();
  strip.show();
}
void loop() 
{
 for(int i=0;i<255;i++)
 {
   strip.setPixelColor(0, i, 0, 0);
  strip.show();
 }
 for(int i=0;i<255;i++)
 {
   strip.setPixelColor(0, 0, i, 0);
  strip.show();
 }
 for(int i=0;i<255;i++)
 {
   strip.setPixelColor(0, 0, 0, i);
  strip.show();
 }
}

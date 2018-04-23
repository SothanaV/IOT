#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
//define NeoPixel Pin and Number of LEDs
#define PIN 2
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
  // set pixel to red, delay(1000)
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
  delay(1000);
  // set pixel to off, delay(1000)
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();
  delay(1000);
}

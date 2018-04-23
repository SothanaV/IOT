#include <Arduino.h>
#include "motor.h"
void setup() 
{
  Serial.begin(9600);

}

void loop() 
{
  motor m;
  m.left(1,200);
  delay(500);

}

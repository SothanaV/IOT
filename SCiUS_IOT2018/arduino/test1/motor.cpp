#include "motor.h"

motor::motor(){

}

void motor::left(int pin,int s)
{
	analogWrite(pin,s);
	Serial.print("left ");
	Serial.println(s);
}

void motor::right(int pin,int s)
{
	analogWrite(pin,s);
	Serial.print("right ");
	Serial.println(s);
}

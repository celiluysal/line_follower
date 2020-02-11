#include "Pins.h"
#include "Arduino.h"

class Motor
{
private:
	short int maxSpeed, minSpeed;
	short int leftSpeed, rightSpeed;
public:
	Motor(short int, short int);
	void SetSpeed(short int, short int);
	void PrintSpeed();
};


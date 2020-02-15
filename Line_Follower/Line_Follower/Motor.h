#include "Pins.h"
#include "Values.h"
#include "Arduino.h"

class Motor
{
private:
	short int leftSpeed, rightSpeed;
public:
	Motor();
	void SetSpeed(short int, short int);
	void PrintSpeed();
};


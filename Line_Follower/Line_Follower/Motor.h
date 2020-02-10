#include "Pins.h"
#include "Arduino.h"

class Motor
{
private:
	short int maxSpeed, minSpeed;
public:
	Motor(short int, short int);
	void SetSpeed(short int, short int);
	int getMax();

};


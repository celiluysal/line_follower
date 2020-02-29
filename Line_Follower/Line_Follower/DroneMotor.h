#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class DroneMotor
{
private:
	short int speed;
public:
	DroneMotor();
	void SetSpeed(short int);
};


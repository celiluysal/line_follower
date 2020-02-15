#include "Arduino.h"
#include "Pid.h"
#include "Motor.h"
#include "DroneMotor.h"
#include "Values.h"
#include "Encoder.h"

class Manage
{
private:
	Line *line;
	Pid *pid;
	Motor *motor;
	DroneMotor* drone;
	Encoder* encoder;

	short int leftMotorDuty;
	short int rightMotorDuty;

	short int droneDuty;

public:
	Manage();
	void GenenalEvent();
};


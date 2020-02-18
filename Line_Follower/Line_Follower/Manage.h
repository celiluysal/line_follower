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

	bool left1Done;

	short int duty;
	short int leftMotorDuty;
	short int rightMotorDuty;

	short int droneDuty;

	short int lineCount;
	void LineCount();

	void TurnLeft();
	void TurnRight();

public:
	Manage();
	void GenenalEvent();
	void Control();
};


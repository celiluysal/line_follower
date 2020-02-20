#include "Arduino.h"
#include "Pid.h"
#include "Motor.h"
#include "DroneMotor.h"
#include "Values.h"
#include "Encoder.h"
#include "Mz80.h"
#include "Tactic.h"

class Manage
{
private:
	Line *line;
	Pid *pid;
	Motor *motor;
	DroneMotor* drone;
	Encoder* encoder;
	Mz80* mz80;
	Tactic* tactic;

	bool left1Done;
	bool _count;

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


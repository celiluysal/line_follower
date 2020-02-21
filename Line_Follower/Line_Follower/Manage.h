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

	bool objectPass;
	bool _count;
	bool _corner;
	short int _chooseWay;
	short int _tmpDistance;

	short int duty;
	short int leftMotorDuty;
	short int rightMotorDuty;

	short int droneDuty;

	short int lineCount;
	void LineCount();

	void changeLineLeft();
	void changeLineRight();

	void chooseWayLeft();
	void chooseWayRight();


	void cornerLeft();
	void cornerRight();

public:
	Manage();
	void GenenalEvent();
	void Control();
};


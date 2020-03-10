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

	short int objectPass;
	bool _count;
	bool _corner_left;
	bool _corner_right;

	short int _chooseWay;
	short int _tmpDistance;
	short int station;

	short int duty;
	short int leftMotorDuty;
	short int rightMotorDuty;
	short int droneDuty;

	float pastAverageDistance;
	float averageDistance;
	short int lineCount;
	short int parkCount;

	void LineCount();
	void ParkCount();

	void changeLineLeft(short int);
	void changeLineRight(short int);

	void chooseWayLeft(short int);
	void chooseWayRight(short int);

	void cornerLeft(short int);
	void cornerRight(short int);

	void GenenalEvent(short int);
	void GenenalEvent(short int,float);

public:
	Manage();
	void Control();
};


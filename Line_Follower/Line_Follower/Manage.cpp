#include "Manage.h"


Manage::Manage() {
	line = new Line();
	pid = new Pid(line);
	motor = new Motor();
	drone = new DroneMotor();
	encoder = new Encoder();
	mz80 = new Mz80();
	tactic = new Tactic();

	/////////////////////////////////////////////////////////////////////////////////
	station = 1;

	averageDistance = 0;
	pastAverageDistance = 0;

	lineCount = 0;
	parkCount = 0;

	_corner_left = 0;
	_corner_right = 0;
	_count = 0;
	_chooseWay = 0;

	encoder->Set();
}

void Manage::Control() {
	
	/*encoder->Print();
	Serial.println();*/

	//GenenalEvent(base_speed_s2);

	GenenalEvent(base_speed_s2,30);
	//MoveStraight(base_speed_s2, 60);
	while (true)
	{
		motor->SetSpeed(0, 0);
	}
	
}



void Manage::GenenalEvent(short int SPEED) {
	line->Read();
	duty = pid->Calculate();

	if (mz80->Read() && tactic->Read()) {
		leftMotorDuty = SPEED + duty;
		rightMotorDuty = SPEED - duty;

		motor->SetSpeed(leftMotorDuty, rightMotorDuty);
	}
	else
	{
		motor->SetSpeed(0, 0);
	}


	//encoder->Print();
	/*line->Print();

	Serial.print(" position: ");
	Serial.print(line->position);

	Serial.print(" error: ");
	Serial.print(line->error);
	
	
	/*Serial.print(" left: ");
	Serial.print(leftMotorDuty);

	Serial.print(" right: ");
	Serial.print(rightMotorDuty);*/

	/*Serial.print(" droneduty: ");
	Serial.print(abs(line->error) / 30);

	Serial.print(" count: ");
	Serial.print(lineCount);*/


	//Serial.println();
}

void Manage::GenenalEvent(short int SPEED, float DISTANCE)
{
	encoder->Read();
	pastAverageDistance = encoder->averageDistance;
	while (1) //düz gitme miktarı
	{
		GenenalEvent(SPEED);
		encoder->Read();
		if (encoder->averageDistance - pastAverageDistance > DISTANCE)
			break;
	}
}

void Manage::MoveStraight(short int SPEED, float DISTANCE)
{
	digitalWrite(LedPin, 1);
	short int diff = 0;
	short int _rightDistance,_leftDistance;

	encoder->Set();
	encoder->Read();

	_leftDistance = encoder->leftDistance;
	_rightDistance = encoder->rightDistance;
	pastAverageDistance = encoder->averageDistance;
	while (1) //düz gitme miktarı
	{
		encoder->Read();
		diff = ((encoder->leftDistance - _leftDistance) - (encoder->rightDistance - _rightDistance));

		motor->SetSpeed(SPEED - diff, SPEED + diff);

		encoder->Read();
		if (encoder->averageDistance - pastAverageDistance > DISTANCE)
			break;
	}
}

void Manage::changeLineLeft(short int SPEED) {
	while (1)
	{
		motor->SetSpeed((SPEED + (change_left_error * Kp)), (SPEED - (change_left_error * Kp)));
		line->Read();

		if (line->sensorValues[0] < 500)
			break;
	}
}

void Manage::changeLineRight(short int SPEED) {
	short int tmp = 0;

	while (1)
	{
		motor->SetSpeed((SPEED + (change_right_error * Kp)), (SPEED - (change_right_error * Kp)));
		line->Read();
		
		if (line->sensorValues[0] > 500 && tmp == 0)
			tmp = 1;
		else if (line->sensorValues[0] < 500 && tmp == 1)
			tmp = 2;
		else if (line->sensorValues[0] > 500 && tmp == 2)
			tmp = 3;
		if (line->sensorValues[7] < 500 && tmp == 3)
			break;
	}
}

void Manage::chooseWayLeft(short int SPEED) {
	bool tmp = 0;
	while (1)
	{
		line->Read();

		if (line->sensorValues[1] < 500)
			tmp = 1;

		if (tmp == 1)
		{
			motor->SetSpeed((SPEED + (choose_left_error * Kp)), (SPEED - (choose_left_error * Kp)));


			if (line->sensorValues[7] > 600 && _chooseWay == 0) {
				_chooseWay = 1;
			}
			if (line->sensorValues[7] < 600 && _chooseWay == 1) {
				_chooseWay = 2;
			}
			else if (line->sensorValues[7] > 700 && _chooseWay == 2) {
				_chooseWay = 3;
			}
			else if (line->sensorValues[7] < 600 && _chooseWay == 3) {
				_chooseWay = 0;
				break; 
			}
		}
		else
		{
			GenenalEvent(SPEED);
		}
				
	}
}

void Manage::chooseWayRight(short int SPEED) {

}

void Manage::cornerLeft(short int SPEED) {
	if (line->sum < 4000) {
		if (line->sensorValues[0] < 500 && line->sensorValues[1] < 500 && line->sensorValues[2] < 500 && line->sensorValues[3] < 500) {
			_corner_left = 1;
		}
	}
	else if (line->sum > 7000 && _corner_left == 1)
	{
		while (1)
		{
			//Serial.println(" left");
			/*leftMotorDuty = SPEED + corner_speed + duty;
			rightMotorDuty = SPEED - corner_speed - duty;

			droneDuty = (leftMotorDuty + rightMotorDuty) / 2;

			motor->SetSpeed(leftMotorDuty, rightMotorDuty);*/
			//drone->SetSpeed(droneDuty);

			GenenalEvent(SPEED);
			_corner_left = 0;
			line->Read();
			if (line->sensorValues[0] < 500)
				break;
		}
	}
}

void Manage::cornerRight(short int SPEED) {
	if (line->sum < 4000) {
		if (line->sensorValues[7] < 500 && line->sensorValues[6] < 500 && line->sensorValues[5] < 500 && line->sensorValues[4] < 500) {
			_corner_right = 1;
		}
	}
	else if (line->sum > 7000 && _corner_right == 1)
	{
		while (1)
		{
			//Serial.println(" right");
			//leftMotorDuty = SPEED + corner_speed + duty;
			//rightMotorDuty = SPEED - corner_speed - duty;

			//droneDuty = (leftMotorDuty + rightMotorDuty) / 2;

			//motor->SetSpeed(leftMotorDuty, rightMotorDuty);
			//drone->SetSpeed(droneDuty);

			GenenalEvent(SPEED);

			_corner_right = 0;
			line->Read();
			if (line->sensorValues[7] < 500)
				break;
		}
	}
}

void Manage::LineCount() {
	bool tmp = 0;
	if (line->sum < 500) {
		_count = 1;
	}
	if (line->sum > 2000 && _count == 1 && tmp == 0) {
		lineCount++;
		_count = 0;
		tmp = 1;
	}
	else {
		tmp = 0;
	}
}

void Manage::ParkCount() {
	bool tmp = 0;
	if (line->sum < 500) {
		_count = 1;
	}
	if (line->sum > 7000 && _count == 1 && tmp == 0) {
		parkCount = 1;
		_count = 0;
		tmp = 1;
	}
	else {
		tmp = 0;
	}
}

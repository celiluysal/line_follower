#include "Manage.h"


Manage::Manage() {
	Serial.println("manage kur");
	line = new Line();
	pid = new Pid(line);
	motor = new Motor();
	drone = new DroneMotor();
	encoder = new Encoder();
	mz80 = new Mz80();
	tactic = new Tactic();

	
	lineCount = 0;
	_corner = 0;
	_count = 0;
	_chooseWay = 0;
	objectPass = 0;
	_tmpDistance = 0;

}

void Manage::Control() {

	encoder->Read();
	line->Read();
	LineCount();

	//duty = pid->Calculate();
	//GenenalEvent();

	//Serial.print(" count:");
	//Serial.print(lineCount);
	

	cornerRight();

	line->Read();
	duty = pid->Calculate();
	GenenalEvent();
}

	
	
	






void Manage::GenenalEvent() {

	if (mz80->Read() && tactic->Read()) {
		leftMotorDuty = base_speed + duty;
		rightMotorDuty = base_speed - duty;

		droneDuty = (leftMotorDuty + rightMotorDuty) / 4;

		motor->SetSpeed(leftMotorDuty, rightMotorDuty);
		//drone->SetSpeed(droneDuty);
	}
	else
	{
		motor->SetSpeed(0, 0);
		//drone->SetSpeed(0);
	}

	/*line->Print();

	Serial.print(" position: ");
	Serial.print(line->position);

	Serial.print(" error: ");
	Serial.print(line->error);

	//encoder->Print();
	
	/*Serial.print(" left: ");
	Serial.print(leftMotorDuty);

	Serial.print(" right: ");
	Serial.print(rightMotorDuty);*/

	/*Serial.print(" droneduty: ");
	Serial.print(abs(line->error) / 30);

	Serial.print(" count: ");
	Serial.print(lineCount);*/


	Serial.println();
}

void Manage::changeLineLeft() {
	while (1)
	{
		motor->SetSpeed((base_speed + (change_left_error * Kp)), (base_speed - (change_left_error * Kp)));
		line->Read();
		//if (line->error > -2000 && line->error < -1300)//error kullan
		if (line->sensorValues[0] < 500)
			break;
	}
}

void Manage::changeLineRight() {
	short int tmp = 0;
	digitalWrite(LedPin, 1);

	while (1)
	{
		motor->SetSpeed((base_speed + (change_right_error * Kp)), (base_speed - (change_right_error * Kp)));
		line->Read();
		//if (line->error > 1300 && line->error < 2000)//error kullan
		
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

void Manage::chooseWayLeft() {
	digitalWrite(LedPin, 1);
	//float tmp = encoder->rightDistance;
	//float diff = 0;
	while (1)
	{
		/*int a = (base_speed + (turn_right_error * Kp));
		int b = (base_speed - (turn_right_error * Kp));
		Serial.print(" a:");
		Serial.print(a);
		Serial.print(" b:");
		Serial.println(b);*/
		//encoder->Read();
		//diff = encoder->rightDistance - tmp;
		//Serial.print(" diff");
		//Serial.print(diff);
		//Serial.println(" choose-left");

		line->Read();



		motor->SetSpeed((base_speed + (choose_left_error * Kp)), (base_speed - (choose_left_error * Kp)));
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
			digitalWrite(LedPin, 0);
			_chooseWay = 0;
			break;
		}
			
	}
}

void Manage::chooseWayRight() {

}

void Manage::cornerLeft() {
	
}

void Manage::cornerRight() {
	if (line->sum < 4000) {
		if (line->sensorValues[7] < 500 && line->sensorValues[6] < 500 && line->sensorValues[5] < 500 && line->sensorValues[5] < 500) {
			_corner = 1;
		}
	}
	else if (line->sum > 7000 && _corner == 1)
	{
		while (1)
		{
			leftMotorDuty = base_speed + corner_speed + duty;
			rightMotorDuty = base_speed - corner_speed - duty;

			droneDuty = (leftMotorDuty + rightMotorDuty) / 2;

			motor->SetSpeed(leftMotorDuty, rightMotorDuty);
			//drone->SetSpeed(droneDuty);

			_corner = 0;
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

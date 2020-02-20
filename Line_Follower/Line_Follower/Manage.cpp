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

	_count = 0;
	lineCount = 0;

	left1Done = false;
}

void Manage::Control() {

	encoder->Read();
	LineCount();
	line->Read();

	/*Serial.print(" count:");
	Serial.println(lineCount);*/

	if (lineCount == 1)
	{
		//Serial.print(" dongu");
		lineCount = 0;
		TurnLeft();
		line->Read();
		duty = pid->Calculate();
		GenenalEvent();
	}
	else
	{
		line->Read();
		duty = pid->Calculate();
		GenenalEvent();
	}

	

}




void Manage::GenenalEvent() {

	if (mz80->Read() && tactic->Read()) {
		leftMotorDuty = base_speed + duty;
		rightMotorDuty = base_speed - duty;

		motor->SetSpeed(leftMotorDuty, rightMotorDuty);
	}
	else
	{
		motor->SetSpeed(0, 0);
	}

	/*line->Print();

	Serial.print(" position: ");
	Serial.print(line->position);

	Serial.print(" error: ");
	Serial.print(line->error);
	
	Serial.print(" left: ");
	Serial.print(leftMotorDuty);

	Serial.print(" right: ");
	Serial.print(rightMotorDuty);*/

	/*Serial.print(" droneduty: ");
	Serial.print(abs(line->error) / 30);

	Serial.print(" count: ");
	Serial.print(lineCount);*/


	//Serial.println();
}

void Manage::TurnLeft() {
	while (1)
	{
		
		/*int a = (base_speed + (turn_left_error * Kp));
		int b = (base_speed - (turn_left_error * Kp));
		Serial.print(" a:");
		Serial.print(a);
		Serial.print(" b:");
		Serial.println(b);*/

		//Serial.println(" left");

		motor->SetSpeed((base_speed + (turn_left_error * Kp)), (base_speed - (turn_left_error * Kp)));
		line->Read();
		if (line->error > -2000 && line->error < -1300)//error kullan
			break;
	}
}

void Manage::TurnRight() {

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

	


	/*if (line->sum < 500 && tmp == 0) {
		
		lineCount++;
		tmp = 1;
	}
	else {
		tmp = 0;
	}*/
}

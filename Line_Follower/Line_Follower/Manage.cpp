#include "Manage.h"


Manage::Manage() {
	Serial.println("manage kur");
	line = new Line();
	pid = new Pid(line);
	motor = new Motor();
	//drone = new DroneMotor();
	//encoder = new Encoder();
}

void Manage::GenenalEvent() {
	line->Read();
	/*Serial.print(" error: ");
	Serial.print(line->error);*/

	short int duty = pid->Calculate();

	leftMotorDuty = base_speed + duty;
	rightMotorDuty = base_speed - duty;

	motor->SetSpeed(leftMotorDuty, rightMotorDuty);

	/*Serial.print(" left: ");
	Serial.print(leftMotorDuty);

	Serial.print(" right: ");
	Serial.print(rightMotorDuty);

	line->Print*/




	/*
	motor->SetSpeed(60, 60);
	delay(50);

	encoder->Print();
	Serial.println();*/






	/*drone->SetSpeed(20);
	delay(1000);
	drone->SetSpeed(30);
	delay(1000);
	drone->SetSpeed(0);
	delay(1000);*/

	Serial.println();
}

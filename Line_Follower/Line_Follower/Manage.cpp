#include "Manage.h"


Manage::Manage() {
	Serial.println("manage kur");
	line = new Line();
	pid = new Pid(line);
	motor = new Motor();
	//drone = new DroneMotor();
	//encoder = new Encoder();

	lineCount = 0;
	left1Done = false;
}

void Manage::Control() {
	line->Read();
	line->Sum();//sil

	LineCount();

	if (lineCount == 1 && !(left1Done))
	{
		TurnLeft();
		line->Read();
		left1Done = 1;
	}
	else
	{
		duty = pid->Calculate();
		GenenalEvent();
	}
	


}



void Manage::GenenalEvent() {

	Serial.print(" count: ");
	Serial.print(lineCount);

	/*Serial.print(" position: ");
	Serial.print(line->position);
	
	Serial.print(" error: ");
	Serial.print(line->error);

	Serial.print(" sum: ");
	Serial.print(line->sum);*/

	//Serial.print(" droneduty: ");
	//Serial.print(abs(line->error)/30);

	

	leftMotorDuty = base_speed + duty;
	rightMotorDuty = base_speed - duty;

	//motor->SetSpeed(leftMotorDuty, rightMotorDuty);



	/*Serial.print(" left: ");
	Serial.print(leftMotorDuty);

	Serial.print(" right: ");
	Serial.print(rightMotorDuty);

	line->Print();
	*/


	Serial.println();
}

void Manage::TurnLeft() {
	while (1)
	{
		Serial.println(" turn_left ");
		
		line->Read();
		if (line->sensorValues[2] < 500)
			break;
	}
}

void Manage::TurnRight() {

}

void Manage::LineCount() {
	short int tmp = 0;
	if (line->sum < 500 && tmp == 0) {
		lineCount++;
		tmp = 1;
	}
	else {
		tmp = 0;
	}
}

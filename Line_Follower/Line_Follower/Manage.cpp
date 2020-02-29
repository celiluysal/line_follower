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

	lineCount = 0;
	_corner_left = 0;
	_corner_right = 0;
	_count = 0;
	_chooseWay = 0;

	objectPass = 0;
	_tmpDistance = 0;

}

void Manage::Control() {

	//bursa

	/*encoder->Read();


	switch (station)
	{
	case 0: {
		
		break;
	}
	case 1: {//engel ile sollama
		if (!mz80->Read())
		{
			encoder->Read();
			pastAverageDistance = encoder->averageDistance;
			changeLineLeft(base_speed_s1); //s1

			while (1) //düz gitme miktarı
			{
				line->Read();
				duty = pid->Calculate();
				GenenalEvent(base_speed_s1); //s1
				encoder->Read();
				if (encoder->averageDistance - pastAverageDistance > 35)
					break;
			}
			changeLineRight(base_speed_s1); 
			GenenalEvent(base_speed_s2); //s2
			station = 2;
		}
		else
		{
			GenenalEvent(base_speed_s1); //s1
		}
		break;
	}
	case 2: {//sol yol seçim (kısa yol)
		line->Read();
		LineCount();
		if (lineCount == 2)
		{
			lineCount = 0;
			station = 4;
		}
		else
		{
			GenenalEvent(base_speed_s1); //s1
		}
		
		break;
	}
	case 3: {
		

		break;
	}
	case 4: {
		encoder->Read();
		pastAverageDistance = encoder->averageDistance;
		while (1) //düz gitme miktarı
		{
			digitalWrite(LedPin, 1);
			GenenalEvent(base_speed_s1); //s1
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 15)
				break;
		}
		digitalWrite(LedPin, 0);
		station = 5;
		break;
	}
	case 5: {
		line->Read();
		chooseWayLeft(base_speed_s1); //s1
		GenenalEvent(base_speed_s1); //s1
		station = 6;
		break;
	}
	case 6: {
		encoder->Read();
		pastAverageDistance = encoder->averageDistance;

		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed_s1); //s1
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 30)
				break;
		}

		encoder->Read();
		pastAverageDistance = encoder->averageDistance;

		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed);
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 420)
				break;
		}

		encoder->Read();
		pastAverageDistance = encoder->averageDistance;

		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed_s2);
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 200) //210
				break;
		}

		station = 7;
		break;
	}
	case 7: {//kapı
		GenenalEvent(base_speed);
		if (!mz80->Read())//kapı
			objectPass = 1;
		else if (mz80->Read() && objectPass == 1) {
			station = 8;
			objectPass = 2;
		}
			
		break;
	}
	case 8: {//hareketli engel
			encoder->Read();
			pastAverageDistance = encoder->averageDistance;

			while (1) //düz gitme miktarı
			{
				GenenalEvent(base_speed_s1);
				encoder->Read();
				if (encoder->averageDistance - pastAverageDistance > 20)
					break;
			}
			station = 9;
		break;
	}
	case 9: {
		line->Read();
			if (!mz80->Read() && objectPass == 2)//engel var
				objectPass = 4;
			else if (line->sum > 7000 && objectPass == 4) {
				//digitalWrite(LedPin, 1);
				objectPass = 5;
				changeLineLeft(base_speed_s1);
				station = 10;
			}
			else
			{
				GenenalEvent(base_speed);
			}
		break;
	}
	case 10: {
		//tek say hız düşür
		line->Read();
		LineCount();
		if (lineCount == 1)
		{
			//digitalWrite(LedPin, 1);
			lineCount = 0;
			GenenalEvent(base_speed);
			station = 11;
		}
		else
		{
			GenenalEvent(base_speed); //s1
		}
		break;
	}
	case 11: {
		//hız düşür
		encoder->Read();
		pastAverageDistance = encoder->averageDistance;

		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed);
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 150)
				break;
		}
		GenenalEvent(base_speed);
		station = 12;
		break;
	}
	case 12: {	
		//sol yol seçs
		line->Read();
		LineCount();
		if (lineCount == 2)
		{
			lineCount = 0;
			chooseWayLeft(base_speed_s1); //s1
			GenenalEvent(base_speed_s1); //s1

			encoder->Read();
			pastAverageDistance = encoder->averageDistance;

			while (1) //düz gitme miktarı
			{
				GenenalEvent(base_speed_s1); //s1
				encoder->Read();
				if (encoder->averageDistance - pastAverageDistance > 15)
					break;
			}
			encoder->Read();
			pastAverageDistance = encoder->averageDistance;
			while (1) //düz gitme miktarı
			{
				GenenalEvent(base_speed_s2); //s1
				encoder->Read();
				if (encoder->averageDistance - pastAverageDistance > 15)
					break;
			}

			station = 13;
		}
		else {	
			GenenalEvent(base_speed);
		}	
		break;
	}
	case 13: {
		encoder->Read();
		pastAverageDistance = encoder->averageDistance;
		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed_f1); 
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 480)//530-500
				break;

		}
		encoder->Read();
		pastAverageDistance = encoder->averageDistance;
		while (1) //düz gitme miktarı
		{
			GenenalEvent(base_speed);
			encoder->Read();
			if (encoder->averageDistance - pastAverageDistance > 60)//530-500
				break;

		}
		station = 15;

		break;
	}
	case 14: {

		break;
	}
	case 15: {
		line->Read();
		ParkCount();
		if (parkCount == 1)
		{
			motor->SetSpeed(0, 0);
			delay(1000);

			encoder->Read();
			pastAverageDistance = encoder->averageDistance;

			while (1) //düz gitme miktarı
			{
				motor->SetSpeed(30, 30);
				encoder->Read();
				if (encoder->averageDistance - pastAverageDistance > 25)
					break;
			}
			station = 20;
		}
		else
			GenenalEvent(base_speed_s3);
		break;
	}
	case 16: {
		
		break;
	}
	case 18: {
		
		break;
	}
	case 19: {
		
		break;
	}
	case 20: {
		motor->SetSpeed(0, 0);
		break;
	}
	default: {
		motor->SetSpeed(0, 0);
		//drone->SetSpeed(0);
		break;
	}
	}*/
}



void Manage::GenenalEvent(short int SPEED) {
	line->Read();
	duty = pid->Calculate();

	if (mz80->Read() && tactic->Read()) {
		leftMotorDuty = SPEED + duty;
		rightMotorDuty = SPEED - duty;

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


	//Serial.println();
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

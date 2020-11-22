#include "DroneMotor.h"

DroneMotor::DroneMotor() {
	pinMode(DronePin, OUTPUT);
}

void DroneMotor::SetSpeed(short int speed) {
	if (speed > drone_max_speed)
		this->speed = drone_max_speed;
	else if (speed < drone_min_speed)
		this->speed = drone_min_speed;
	else
		this->speed = speed;

	analogWrite(DronePin,this->speed);
}
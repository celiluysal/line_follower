#include "Motor.h"

Motor::Motor(short int maxSpeed, short int minSpeed) {
	this->maxSpeed = maxSpeed;
	this->minSpeed = minSpeed;
}

void Motor::SetSpeed(short int leftSpeed, short int rightSpeed) {
    if (leftSpeed > maxSpeed)
        leftSpeed = maxSpeed;
    else if (leftSpeed < minSpeed)
        leftSpeed = minSpeed;

    if (rightSpeed > maxSpeed)
        rightSpeed = maxSpeed;
    else if (rightSpeed < minSpeed)
        rightSpeed = minSpeed;


    if (leftSpeed < 0) {
        digitalWrite(AIN2, LOW);
        digitalWrite(AIN1, HIGH);
    }
    else {
        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);
    }

    if (rightSpeed < 0) {
        digitalWrite(BIN2, LOW);
        digitalWrite(BIN1, HIGH);
    }
    else {
        digitalWrite(BIN2, HIGH);
        digitalWrite(BIN1, LOW);
    }

    analogWrite(PWMA, leftSpeed);
    analogWrite(PWMB, rightSpeed);

}

int Motor::getMax() {
    return maxSpeed;
}
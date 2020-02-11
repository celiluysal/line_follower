#include "Motor.h"

Motor::Motor(short int minSpeed, short int maxSpeed) {
    this->maxSpeed = (maxSpeed < 255) ? maxSpeed : 255;
    this->minSpeed = (minSpeed > -255) ? minSpeed : -255;
}

void Motor::SetSpeed(short int leftSpeed, short int rightSpeed) {
    if (leftSpeed > maxSpeed)
        this->leftSpeed = maxSpeed;
    else if (leftSpeed < minSpeed)
        this->leftSpeed = minSpeed;
    else
        this->leftSpeed = leftSpeed;

    if (rightSpeed > maxSpeed)
        this->rightSpeed = maxSpeed;
    else if (rightSpeed < minSpeed)
        this->rightSpeed = minSpeed;
    else
        this->rightSpeed = rightSpeed;


    if (this->leftSpeed < 0) {
        digitalWrite(AIN2, LOW);
        digitalWrite(AIN1, HIGH);
    }
    else {
        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);
    }

    if (this->rightSpeed < 0) {
        digitalWrite(BIN2, LOW);
        digitalWrite(BIN1, HIGH);
    }
    else {
        digitalWrite(BIN2, HIGH);
        digitalWrite(BIN1, LOW);
    }

    analogWrite(PWMA, this->leftSpeed);
    analogWrite(PWMB, this->rightSpeed);

}

void Motor::PrintSpeed() {
    Serial.print("leftSpeed:");
    Serial.print(this->leftSpeed);
    Serial.print('\t');
    Serial.print("rightSpeed:");
    Serial.print(this->rightSpeed);
}

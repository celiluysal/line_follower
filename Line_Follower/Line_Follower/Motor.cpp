#include "Motor.h"

Motor::Motor() {
    pinMode(PWMA,OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
}

void Motor::SetSpeed(short int leftSpeed, short int rightSpeed) {
    if (leftSpeed > max_speed)
        this->leftSpeed = max_speed;
    else if (leftSpeed < min_speed)
        this->leftSpeed = min_speed;
    else
        this->leftSpeed = leftSpeed;

    if (rightSpeed > max_speed)
        this->rightSpeed = max_speed;
    else if (rightSpeed < min_speed)
        this->rightSpeed = min_speed;
    else
        this->rightSpeed = rightSpeed;


    if (this->leftSpeed >= 0) {
        digitalWrite(AIN2, LOW);
        digitalWrite(AIN1, HIGH); 
    }
    else {
        digitalWrite(AIN2, HIGH);
        digitalWrite(AIN1, LOW);
        this->leftSpeed = -this->leftSpeed;
    }

    if (this->rightSpeed >= 0) {
        digitalWrite(BIN2, LOW);
        digitalWrite(BIN1, HIGH);       
    }
    else {
        digitalWrite(BIN2, HIGH);
        digitalWrite(BIN1, LOW);
        this->rightSpeed = -this->rightSpeed;
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

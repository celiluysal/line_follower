#include "Encoder.h"

Encoder::Encoder() {
	pinMode(LeftEncoderPin, INPUT);
	pinMode(RightEncoderPin, INPUT);

    leftDistance = 0;
    rightDistance = 0;
    averageDistance = 0;

    _left = 0;
    _right = 0;
}

void Encoder::Set()
{
    firstLeft = !(digitalRead(LeftEncoderPin));
    firstRight = !(digitalRead(RightEncoderPin));
}

void Encoder::Read() {
    if (digitalRead(LeftEncoderPin) == firstLeft && _left == 0) {
        leftDistance += wheel_factor;
        _left = 1;
    }
    if (digitalRead(LeftEncoderPin) == !(firstLeft) && _left == 1) {
        leftDistance += wheel_factor;
        _left = 0;
    }

    if (digitalRead(RightEncoderPin) == firstRight && _right == 0) {
        rightDistance += wheel_factor;
        _right = 1;
    }
    if (digitalRead(RightEncoderPin) == !(firstRight) && _right == 1) {
        rightDistance += wheel_factor;
        _right = 0;
    }
    averageDistance = (leftDistance + rightDistance) / 2;
}

void Encoder::Print() {
    Read();
    Serial.print("  len: ");
    Serial.print(leftDistance);
    Serial.print("  ren: ");
    Serial.print(rightDistance);
}
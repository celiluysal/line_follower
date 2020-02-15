#include "Encoder.h"

Encoder::Encoder() {
	pinMode(LeftEncoderPin, INPUT);
	pinMode(RightEncoderPin, INPUT);

    leftCount = 0;
    rightCount = 0;
    _left = 0;
    _right = 0;
}

void Encoder::Read() {
    if (digitalRead(LeftEncoderPin) == 0 && _left == 0) {
        leftCount++;
        _left = 1;
    }
    if (digitalRead(LeftEncoderPin) == 1) {
        _left = 0;
    }

    if (digitalRead(RightEncoderPin) == 0 && _right == 0) {
        rightCount++;
        _right = 1;
    }
    if (digitalRead(RightEncoderPin) == 1) {
        _right = 0;
    }
}

void Encoder::Print() {
    Read();
    Serial.print("  len: ");
    Serial.print(leftCount);
    Serial.print("  ren: ");
    Serial.print(rightCount);
}
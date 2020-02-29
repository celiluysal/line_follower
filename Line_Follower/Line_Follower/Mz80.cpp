#include "Mz80.h"

Mz80::Mz80() {
	pinMode(Mz80Pin, INPUT);
}

bool Mz80::Read() {
	distance = digitalRead(Mz80Pin);
	return distance;
}

void Mz80::Print() {
	Read();
	Serial.print(" mz80: ");
	Serial.print(distance);
}


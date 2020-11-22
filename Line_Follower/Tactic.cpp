#include "Tactic.h"

Tactic::Tactic() {
	pinMode(TacticPin, INPUT);
}

bool Tactic::Read() {
	tactic = digitalRead(TacticPin);
	return tactic;
}

void Tactic::Print() {
	Read();
	Serial.print(" tactic: ");
	Serial.print(tactic);
}
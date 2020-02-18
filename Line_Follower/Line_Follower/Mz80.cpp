#include "Mz80.h"

Mz80::Mz80() {
	pinMode(Mz80Pin, INPUT);
}

bool Mz80::Read() {
	distance = digitalRead(Mz80Pin);
}

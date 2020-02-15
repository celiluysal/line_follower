#include "Pid.h"

Pid::Pid(Line *line) {
	Serial.println("pid kur");
	this->line = line;
	lastError = 0;

	Serial.print("pid line.position: ");
	Serial.println(this->line->position);
}

short int Pid::Calculate() {
	int P = line->error * Kp;
	long I = (I + line->error) * Ki;
	int D = (line->error - lastError) * Kd;
	short int PD = P + D;
	lastError = line->error;
	return PD;
}

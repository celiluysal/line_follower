#include "Pid.h"

Pid::Pid(Line *line) {
	Serial.println("pid kur");
	this->line = line;
	lastError = 0;

	Serial.print("pid line.position: ");
	Serial.println(this->line->position);
}

short int Pid::Calculate() {
	Serial.println();
	Serial.print("pid line.position: ");
	Serial.println(this->line->position);
	Serial.println();
	int P = line->error * Kp;
	long I = (I + line->error) * Ki;
	int D = (line->error - lastError) * Kd;
	short int PID = P + I + D;
	lastError = line->error;
	return PID;
}

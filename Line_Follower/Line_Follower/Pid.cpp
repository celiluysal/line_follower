#include "Pid.h"

Pid::Pid(Line *line) {
	this->line = line;
	lastError = 0;
}

short int Pid::Calculate() {
	int P = line->error * Kp;
	long I = (I + line->error) * Ki;
	int D = (line->error - lastError) * Kd;
	short int PD = P + D;
	lastError = line->error;
	return PD;
}

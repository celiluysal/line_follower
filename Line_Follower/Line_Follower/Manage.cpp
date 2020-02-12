#include "Manage.h"


Manage::Manage() {
	Serial.println("manage kur");
	line = new Line();

	Serial.print("manage line.position: ");
	Serial.println(line->position);

	pid = new Pid(line);
}

void Manage::GenenalEvent() {
	line->Read();
	short int leftDuty = pid->Calculate();
	Serial.println("generalevent pid.calculate");
	Serial.print("left duty: ");
	Serial.println(leftDuty);
}

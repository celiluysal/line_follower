#include "Arduino.h"
#include "Pid.h"

class Manage
{
private:
	Line *line;
	Pid *pid;
public:
	Manage();
	void GenenalEvent();
};


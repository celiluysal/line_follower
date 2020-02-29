#include "Arduino.h"
#include "Line.h"
#include "Values.h"


class Pid
{
private:
	short int lastError;
	Line *line;
public:
	Pid(Line *line);
	short int Calculate();
};


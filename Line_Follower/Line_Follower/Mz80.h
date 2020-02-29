#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class Mz80
{
private:
	bool distance;
public:
	Mz80();
	bool Read();
	void Print();
};


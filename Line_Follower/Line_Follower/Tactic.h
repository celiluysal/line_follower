#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class Tactic
{
private:
	bool tactic;
public:
	Tactic();
	bool Read();
	void Print();
};


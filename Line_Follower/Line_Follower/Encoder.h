#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class Encoder
{
private:
	bool _left;
	bool _right;	
public:
	long leftCount;
	long rightCount;
	Encoder();
	void Read();
	void Print();
};


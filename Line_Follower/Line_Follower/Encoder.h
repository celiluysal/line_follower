#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class Encoder
{
private:
	bool _left;
	bool _right;

	bool firstLeft;
	bool firstRight;
public:
	float leftDistance;
	float rightDistance;

	float averageDistance;

	Encoder();
	void Set();
	void Read();
	void Print();
};


#include "Arduino.h"
#include "Pins.h"
#include "Values.h"

class Encoder
{
private:
	bool _left;
	bool _right;	
public:
	float leftDistance;
	float rightDistance;

	float averageDistance;

	Encoder();
	void Read();
	void Print();
};


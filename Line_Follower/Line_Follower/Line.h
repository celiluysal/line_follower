#include <QTRSensors.h>
#include "Arduino.h"
#include "Pins.h"

class Line
{
private:
	QTRSensors qtr;
	bool backGround;
public:
	short int sensorValues[QtrSensorCount];
	short int position;
	short int error;

	Line();
	void CalibrateSensor();	
	void Read();
	void DetectBackground();
	void Print();
	QTRSensors GetQtr();

};


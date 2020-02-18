#include "Line.h"


const uint8_t QTRPins[QtrSensorCount] = QtrPins;

Line::Line(void) {
 /*   Serial.print('\t');
    Serial.print("kur qtr");
    Serial.print('\t');*/
	qtr.setTypeAnalog();
	qtr.setSensorPins(QTRPins, QtrSensorCount);

    CalibrateSensor();
}

void Line::CalibrateSensor() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

    // analogRead() takes about 0.1 ms on an AVR.
    // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
    // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
    // Call calibrate() 400 times to make calibration take about 10 seconds.
    for (uint16_t i = 0; i < 100; i++)
    {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW); // turn off Arduino's LED to indicate we are through with calibration

    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (uint8_t i = 0; i < QtrSensorCount; i++)
    {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    // print the calibration maximum values measured when emitters were on
    for (uint8_t i = 0; i < QtrSensorCount; i++)
    {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(2000);
    position = qtr.readLineWhite((uint16_t*)sensorValues);
}

void Line::Read() {
    DetectBackground();

    if (backGround) {
        Serial.print(" black ");
        position = qtr.readLineWhite((uint16_t*)sensorValues);
    }
    else {
        Serial.print(" white ");
        position = qtr.readLineBlack((uint16_t*)sensorValues);
    }
        


    
    error = position-3500;    

}

void Line::Print() {
    Serial.print("  ");
    for (uint8_t i = 0; i < QtrSensorCount; i++)
    {
        Serial.print(sensorValues[i]);
        Serial.print("  ");
    }
}

void Line::Sum() {
    sum = 0;
    for (uint8_t i = 0; i < QtrSensorCount; i++)
    {
        sum += sensorValues[i];
    }
}

void Line::DetectBackground() {
    Sum();
    if ((sum > 800) && (sum < 2100))
        backGround = 0;
    else
        backGround = 1;
}

QTRSensors Line::GetQtr() {
    return qtr;
}




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
    delay(1000);
}

void Line::Read() {
    position = qtr.readLineBlack((uint16_t*)sensorValues);
    error = position;

    Serial.println();
    for (uint8_t i = 0; i < QtrSensorCount; i++)
    {
        Serial.print(sensorValues[i]);
        Serial.print('\t');
    }
    Serial.println();
    /*
    DetectBackgroud fonksiyounua göre
    qtr.readLineBlack veya qtr.readLineWhite seç
    position, error ve sensorValues değerlerini ata
    */
}

void Line::DetectBackground() {
    /*
    sensorValues[] veya positon değerlerini yorumla ve zemin rengini bul
    */

    /*if (sensorValues[7] < 300 && sensorValues[0] < 300) //siyah
        backGround = 1; 

    if (sensorValues[7] < 300 && sensorValues[0] < 300) //beyaz
        backGround = 1;*/
}

QTRSensors Line::GetQtr() {
    return qtr;
}




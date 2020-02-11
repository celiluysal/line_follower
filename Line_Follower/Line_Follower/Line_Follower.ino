/*
 Name:		Line_Follower.ino
 Created:	2/10/2020 2:56:30 AM
 Author:	celil
*/

#include "Pins.h"
#include "Motor.h"
#include "Line.h"

//motor(minSpeed,maxSpeed)
Motor motor(-100, 255);

Line line;




void setup() {
    Serial.begin(9600);
    
}


void loop() {
    for (int i = -260; i < 360; i++)
    {
        motor.SetSpeed(i, i);
        motor.PrintSpeed();
        Serial.println();
        delay(100);
    }
   
    
  
}
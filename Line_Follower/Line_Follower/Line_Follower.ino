/*
 Name:		Line_Follower.ino
 Created:	2/10/2020 2:56:30 AM
 Author:	celil
*/

#include "Pins.h"
#include "Motor.h"
//#include "Line.h"
//#include "Pid.h"
#include "Manage.h"


//motor(minSpeed,maxSpeed)
//Motor motor(-100, 255);

//Line line;
//Pid pid;
Manage *manage;





void setup() {
    Serial.begin(9600);

    manage = new Manage();


    
}


void loop() {

    manage->GenenalEvent();
    delay(500);
   /* for (int i = -260; i < 360; i++)
    {
        motor.SetSpeed(i, i);
        motor.PrintSpeed();
        Serial.println();
        delay(100);
    }*/
   
    
  
}
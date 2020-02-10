/*
 Name:		Vs_arduino.ino
 Created:	2/10/2020 1:40:09 AM
 Author:	celil
*/

#include "deneme.h"

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);

    deneme d;
    d.fonk();
}

// the loop function runs over and over again until power down or reset
void loop() {
    //Serial.println("sea");
    /*digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);*/

  
}

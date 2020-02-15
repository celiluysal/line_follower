/*
 Name:		Line_Follower.ino
 Created:	2/10/2020 2:56:30 AM
 Author:	celil
*/

#include "Manage.h"

Manage *manage;

void setup() {
    Serial.begin(9600);
    manage = new Manage();
}


void loop() {
    manage->GenenalEvent();
}
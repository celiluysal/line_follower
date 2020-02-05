#define sol_encoder 2

int sol_encoder_say = 0;
int sol_encoder_yuzey = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(sol_encoder);
  Serial.println(sensorValue);
  delay(1);   
}

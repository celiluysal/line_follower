#define PWMA 3

void setup() {
  pinMode(PWMA,OUTPUT);

}

void loop() {
  analogWrite(PWMA,10);
  delay(1000);
  analogWrite(PWMA,20);
  delay(1000);
  analogWrite(PWMA,30);
  delay(1000);
  analogWrite(PWMA,40);
  delay(1000);
  analogWrite(PWMA,30);
  delay(1000);
  analogWrite(PWMA,20);
  delay(1000);
  analogWrite(PWMA,10);
  delay(1000);
  analogWrite(PWMA,0);
  delay(1000);

  
}

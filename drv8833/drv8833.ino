#define PWMA 5
#define AIN2 6
#define AIN1 7

#define PWMB 11
#define BIN2 10
#define BIN1 9



void setup() {
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  
  pinMode(PWMB,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);

}

void loop() {
  /*motor(0,0);
  delay(1000);
  motor(20,20);
  delay(1000);*/
  
  motor(40,40);
 /* delay(1000);
  motor(60,60);
  delay(1000);
  motor(40,40);
  delay(1000);
  motor(20,20);
  delay(1000);*/
}

void motor(int A, int B){
  analogWrite(PWMA,A);
  digitalWrite(AIN2,1);
  digitalWrite(AIN1,0);

  analogWrite(PWMB,B);
  digitalWrite(BIN2,1);
  digitalWrite(BIN1,0);
}

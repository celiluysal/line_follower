#define PWMA 5
#define AIN2 6
#define AIN1 7

#define PWMB 11
#define BIN2 10
#define BIN1 9

#define tactic 8

#define sol_encoder 2

int sol_encoder_say = 0;
int sol_encoder_yuzey = 0;



void setup() {
Serial.begin(9600);
  
  pinMode(PWMA,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  
  pinMode(PWMB,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);

  pinMode(tactic, INPUT);

}

void loop() {

  int tactic_state = digitalRead(tactic);
  //int sensorValue = digitalRead(sol_encoder);
  //Serial.println(sensorValue);

  if(tactic_state)
  motor(255,40);
  else
  motor(0,0);

  if(digitalRead(sol_encoder) == 0 && sol_encoder_yuzey == 0){
    sol_encoder_say++;
    sol_encoder_yuzey=1;
  }
  if(digitalRead(sol_encoder)==1){
    sol_encoder_yuzey=0;
  }
  delay(1);
  Serial.println(sol_encoder_say);

}

void motor(int A, int B){
  analogWrite(PWMA,A);
  digitalWrite(AIN2,1);
  digitalWrite(AIN1,0);

  analogWrite(PWMB,B);
  digitalWrite(BIN2,1);
  digitalWrite(BIN1,0);
}

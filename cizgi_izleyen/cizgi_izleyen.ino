#define PWMA 5
#define AIN2 6
#define AIN1 7

#define PWMB 11
#define BIN2 10
#define BIN1 9

#define Tactic 8
#define Distance 12

#define LeftEncoder 2
#define RightEncoder 4

#define Led 13

#define TX 1
#define RX 0

#define max_speed 255
#define min_speed -255
#define base_speed 100





float Kp = 0.04;// 0.1//0.03
float Kd = 0.1;//0.5 kalibrasyonda 0.3 iyi değer kalibre yoksa 0.5 iyi
float Ki = 0.0001;//0.0001

unsigned int HIZ = 35; // hız ilk değeri. etaplarda değiştirilecek

int left_motor_duty = 0;
int right_motor_duty = 0;

unsigned int son_pozisyon = 0;
unsigned int pozisyon = 3500;
unsigned int merkez = 3500;

int sonhata = 0;

#include <QTRSensors.h>
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];


void motor(int left_speed, int right_speed){
  if(left_speed > max_speed)
    left_speed = max_speed;
  else if(left_speed < min_speed)
    left_speed = min_speed;

  if(right_speed > max_speed)
    right_speed = max_speed;
  else if(right_speed < min_speed)
    right_speed = min_speed;
    
  
  if(left_speed < 0){
    digitalWrite(AIN2,0);
    digitalWrite(AIN1,1);
  }
  else{
    digitalWrite(AIN2,1);
    digitalWrite(AIN1,0);
  }
  
  if(right_speed < 0){
    digitalWrite(BIN2,0);
    digitalWrite(BIN1,1);
  }
  else{
    digitalWrite(BIN2,1);
    digitalWrite(BIN1,0);
  }

  analogWrite(PWMA,left_speed);
  analogWrite(PWMB,right_speed);
}

void pid(){
  int hata = pozisyon - merkez;
  int  P = hata * Kp;
  long I = (I + hata) * Ki;
  int  D = (hata - sonhata) * Kd;
  int PID = P + I + D;
  sonhata = hata;
  
  if (PID < -255) {
      PID = -255;
  }
  
  if (PID > 255) {
      PID = 255;
  }

  left_motor_duty = (HIZ + PID);
  right_motor_duty = (HIZ - PID);

  if (left_motor_duty > 255){
    right_motor_duty = right_motor_duty-(left_motor_duty - 255) ;
    left_motor_duty = 255 ;}
  if (right_motor_duty > 255){
    left_motor_duty = left_motor_duty-(right_motor_duty - 255) ;
    right_motor_duty = 255 ;}  
    
  if (left_motor_duty < 0)
    left_motor_duty = 0;
  if (right_motor_duty < 0)
    right_motor_duty = 0;
}

void calibration(){
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2, A1, A0}, SensorCount);

  delay(500);
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
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(qtr.calibrationOn.maximum[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
}



void setup() {
  calibration();
  
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
  pozisyon = qtr.readLineBlack(sensorValues);
 
  son_pozisyon = pozisyon;

  pid();

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.print(pozisyon);
  Serial.print('\t');

  Serial.print("left: ");
  Serial.print(left_motor_duty);

  Serial.print("  right: ");
  Serial.println(right_motor_duty);
  
  if(tactic_state)
  motor(left_motor_duty, right_motor_duty);
  else
  motor(0,0);
  

}

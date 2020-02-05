#define mz80 12

void setup() {
  pinMode(13,OUTPUT);
  pinMode(mz80, INPUT);

}

void loop() {
  bool uzaklik = digitalRead(mz80);
  if(!uzaklik){
    digitalWrite(13,1);
  }
  else{
    digitalWrite(13,0);
  }

}

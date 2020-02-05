#define tactic 8

void setup() {d:
  Serial.begin(9600);
  pinMode(tactic, INPUT);
}

void loop() {
  int tactic_state = digitalRead(tactic);
  Serial.println(tactic_state);
  delay(1);    
}

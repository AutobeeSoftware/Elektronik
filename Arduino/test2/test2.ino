int HI1 = 3;
int LI1 = 5;
int HI2 = 6;
int LI2 = 9;
int HI3 = 10;
int LI3 = 11;

int off_time = 1;
int on_time = 2;

void setup() {
  pinMode(HI1, OUTPUT);
  pinMode(HI2, OUTPUT);
  pinMode(HI3, OUTPUT);
  pinMode(LI1, OUTPUT);
  pinMode(LI2, OUTPUT);
  pinMode(LI3, OUTPUT);

  digitalWrite(HI1, LOW);
  digitalWrite(HI2, LOW);
  digitalWrite(HI3, LOW);
  digitalWrite(LI1, LOW);
  digitalWrite(LI2, LOW);
  digitalWrite(LI3, LOW);
}

void loop() {
  digitalWrite(HI1, HIGH);
  digitalWrite(LI2, HIGH);
  delay(on_time);
  digitalWrite(HI1, LOW);
  digitalWrite(LI2, LOW);
  delay(off_time);

  digitalWrite(HI1, HIGH);
  digitalWrite(LI3, HIGH);
  delay(on_time);
  digitalWrite(LI3, LOW);
  digitalWrite(HI1, LOW);
  delay(off_time);
  
  digitalWrite(HI2, HIGH);
  digitalWrite(LI1, HIGH);
  delay(on_time);
  digitalWrite(LI1, LOW);
  digitalWrite(HI2, LOW);
  delay(off_time);

  digitalWrite(HI2, HIGH);
  digitalWrite(LI3, HIGH);
  delay(on_time);
  digitalWrite(LI3, LOW);
  digitalWrite(HI2, LOW);
  delay(off_time);

  digitalWrite(HI3, HIGH);
  digitalWrite(LI1, HIGH);
  delay(on_time);
  digitalWrite(LI1, LOW);
  digitalWrite(HI3, LOW);
  delay(off_time);

  digitalWrite(HI3, HIGH);
  digitalWrite(LI2, HIGH);
  delay(on_time);
  digitalWrite(LI2, LOW);
  digitalWrite(HI3, LOW);
  delay(off_time);
  
}

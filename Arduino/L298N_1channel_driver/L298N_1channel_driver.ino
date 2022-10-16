int ENA11 = 3;
int M11R = 2;
int M11L = 4;
int M12R = 5;
int M12L = 7;
int ENA12 = 6;

int ENA21 = 10;
int M21R = A1;
int M21L = A0;
int M22R = 12;
int M22L = 13;
int ENA22 = 11;

unsigned long timer[6];
byte last_channel[5];
int input[5];

int input1;
int input2;

int spd1 = 100;
int spd2 = 100;
int a = 0;
int b = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(ENA11, OUTPUT);
  pinMode(ENA12, OUTPUT);
  pinMode(M11R, OUTPUT);
  pinMode(M11L, OUTPUT);
  pinMode(M12R, OUTPUT);
  pinMode(M12L, OUTPUT);

  pinMode(ENA21, OUTPUT);
  pinMode(ENA22, OUTPUT);
  pinMode(M21R, OUTPUT);
  pinMode(M21L, OUTPUT);
  pinMode(M22R, OUTPUT);
  pinMode(M22L, OUTPUT);

  digitalWrite(M11R, LOW);
  digitalWrite(M11L, LOW);
  analogWrite(ENA11, 0);

  digitalWrite(M12R, LOW);
  digitalWrite(M12L, LOW);
  analogWrite(ENA12, 0);

  digitalWrite(M21R, LOW);
  digitalWrite(M21L, LOW);
  analogWrite(ENA21, 0);

  digitalWrite(M22R, LOW);
  digitalWrite(M22L, LOW);
  analogWrite(ENA22, 0);

  PCICR |= (1 << PCIE0);
  PCICR |= (1 << PCIE1);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK1 |= (1 << PCINT10);
  PCMSK1 |= (1 << PCINT11);
  PCMSK1 |= (1 << PCINT12);
}

void loop() {
  if (input[4] < 1500){
    input1 = input[0];
    input2 = input[1];
  }
  else{
    input1 = input[2];
    input2 = input[3];
  }
  
  a = abs(1500 - input1);
  if (a > 490) a = 490;
  spd1 = map(a,0,490,0,250);

  b = abs(1500 - input2);
  if (b > 490) b = 490;
  spd2 = map(b,0,490,0,250);

  if (input1 > 1450 && input1 < 1550){
    digitalWrite(M12R, LOW);
    digitalWrite(M12L, LOW);
    analogWrite(ENA12, 0);
    digitalWrite(M11R, LOW);
    digitalWrite(M11L, LOW);
    analogWrite(ENA11, 0);
  }
  else if (input1 > 1550){
    digitalWrite(M12R, HIGH);
    digitalWrite(M12L, LOW);
    analogWrite(ENA12, spd1);
    digitalWrite(M11R, HIGH);
    digitalWrite(M11L, LOW);
    analogWrite(ENA11, spd1);
  }
  else if (input1 < 1450){
    digitalWrite(M12R, LOW);
    digitalWrite(M12L, HIGH);
    analogWrite(ENA12, spd1);
    digitalWrite(M11R, LOW);
    digitalWrite(M11L, HIGH);
    analogWrite(ENA11, spd1);
  }

  if (input2 > 1450 && input2 < 1550){
    digitalWrite(M22R, LOW);
    digitalWrite(M22L, LOW);
    analogWrite(ENA22, 0);
    digitalWrite(M21R, LOW);
    digitalWrite(M21L, LOW);
    analogWrite(ENA21, 0);
  }
  else if (input2 > 1550){
    digitalWrite(M22R, HIGH);
    digitalWrite(M22L, LOW);
    analogWrite(ENA22, spd2);
    digitalWrite(M21R, HIGH);
    digitalWrite(M21L, LOW);
    analogWrite(ENA21, spd2);
  }
  else if (input2 < 1450){
    digitalWrite(M22R, LOW);
    digitalWrite(M22L, HIGH);
    analogWrite(ENA22, spd2);
    digitalWrite(M21R, LOW);
    digitalWrite(M21L, HIGH);
    analogWrite(ENA21, spd2);
  }
}

ISR(PCINT0_vect) {
  timer[0] = micros();
  if (last_channel[0] == 0 && PINB & B00000001) // means digitalread 
  {
    last_channel[0] = 1;
    timer[1] = timer[0];
  }
  else if (last_channel[0] == 1 && !(PINB & B00000001)) // make sure new channel position will be low
  {
    last_channel[0] = 0;
    input[0] = timer[0] - timer[1];
  }
  if (last_channel[1] == 0 && PINB & B00000010) // means digitalread 
  {
    last_channel[1] = 1;
    timer[2] = timer[0];
  }
  else if (last_channel[1] == 1 && !(PINB & B00000010)) // make sure new channel position will be low
  {
    last_channel[1] = 0;
    input[1] = timer[0] - timer[2];
  }
}

ISR(PCINT1_vect){
  timer[0] = micros();
  if (last_channel[2] == 0 && PINC & B00000100) // means digitalread 
  {
    last_channel[2] = 1;
    timer[3] = timer[0];
  }
  else if (last_channel[2] == 1 && !(PINC & B00000100)) // make sure new channel position will be low
  {
    last_channel[2] = 0;
    input[2] = timer[0] - timer[3];
  }
  
  if (last_channel[3] == 0 && PINC & B00001000) // means digitalread 
  {
    last_channel[3] = 1;
    timer[4] = timer[0];
  }
  else if (last_channel[3] == 1 && !(PINC & B00001000)) // make sure new channel position will be low
  {
    last_channel[3] = 0;
    input[3] = timer[0] - timer[4];
  }
  
  if (last_channel[4] == 0 && PINC & B00010000) // means digitalread 
  {
    last_channel[4] = 1;
    timer[5] = timer[0];
  }
  else if (last_channel[4] == 1 && !(PINC & B00010000)) // make sure new channel position will be low
  {
    last_channel[4] = 0;
    input[4] = timer[0] - timer[5];
  }
}

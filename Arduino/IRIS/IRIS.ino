#define RPWM1 5
#define LPWM1 6
#define R_EN1 7
#define L_EN1 4
#define R_IS1 2
#define L_IS1 3

#define RPWM2 10
#define LPWM2 11
#define R_EN2 12
#define L_EN2 13
#define R_IS2 18
#define L_IS2 19

unsigned long timer[4];
byte last_channel[4];
int input[4];

int spd1 = 100;
int spd2 = 100;
int a = 0;

void setup() {
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(R_EN1, OUTPUT);
  pinMode(L_EN1, OUTPUT);
  pinMode(R_IS1, OUTPUT);
  pinMode(L_IS1, OUTPUT);

  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(R_EN2, OUTPUT);
  pinMode(L_EN2, OUTPUT);
  pinMode(R_IS2, OUTPUT);
  pinMode(L_IS2, OUTPUT);

  digitalWrite(R_EN1, HIGH);
  digitalWrite(L_EN1, HIGH);
  digitalWrite(R_IS1, LOW);
  digitalWrite(L_IS1, LOW);

  digitalWrite(R_EN2, HIGH);
  digitalWrite(L_EN2, HIGH);
  digitalWrite(R_IS2, LOW);
  digitalWrite(L_IS2, LOW);
  
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);

  Serial.begin(9600);
}

void loop() {

  Serial.println(spd1);
  //Serial.println(spd2);

  a = abs(1500 - input[0]);
  if (a > 490) a = 490;
  spd1 = map(a,0,490,0,250);

  a = abs(1500 - input[1]);
  if (a > 490) a = 490;
  spd2 = map(a,0,490,0,250);
  
  if (input[0] > 1450 && input[0] < 1550){
    digitalWrite(RPWM1, LOW);
    digitalWrite(LPWM1, LOW);
  }
  else if (input[0] > 1550){
    analogWrite(RPWM1, spd1);
    digitalWrite(LPWM1, LOW);
  }
  else if (input[0] < 1450){
    analogWrite(LPWM1, spd1);
    digitalWrite(RPWM1, LOW);
  }


  if (input[1] > 1450 && input[1] < 1550){
    digitalWrite(RPWM2, LOW);
    digitalWrite(LPWM2, LOW);
  }
  else if (input[1] > 1550){
    analogWrite(RPWM2, spd2);
    digitalWrite(LPWM2, LOW);
  }
  else if (input[1] < 1450){
    analogWrite(LPWM2, spd2);
    digitalWrite(RPWM2, LOW);
  }
}

ISR(PCINT0_vect) {
  timer[0] = micros();
  if(last_channel[0] == 0 && PINB & B00000001) {
    last_channel[0] = 1;
    timer[1] = timer[0];
  }
  else if(last_channel[0] == 1 && !(PINB & B00000001)) {
    last_channel[0] = 0;
    input[0] = timer[0] - timer[1];
  }

  if(last_channel[1] == 0 && PINB & B00000010) {
    last_channel[1] = 1;
    timer[2] = timer[0];
  }
  else if(last_channel[1] == 1 && !(PINB & B00000010)) {
    last_channel[1] = 0;
    input[1] = timer[0] - timer[2];
  }
}

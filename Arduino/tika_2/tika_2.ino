#define RPWM1 2
#define LPWM1 3
#define R_EN1 19
#define L_EN1 18
#define R_IS1 17
#define L_IS1 16

unsigned long timer[4];
byte last_channel[4];
int input[4];

int spd1 = 200;
int spd2 = 100;
int a = 0;

void setup() {
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(R_EN1, OUTPUT);
  pinMode(L_EN1, OUTPUT);
  pinMode(R_IS1, OUTPUT);
  pinMode(L_IS1, OUTPUT);

  digitalWrite(R_EN1, HIGH);
  digitalWrite(L_EN1, HIGH);
  digitalWrite(R_IS1, LOW);
  digitalWrite(L_IS1, LOW);

  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
}

void loop() {
  analogWrite(RPWM1, spd1);
  digitalWrite(LPWM1, LOW);
}

#define ENA1 6
#define DIR1 5
#define PUL1 4

#define ENA2 3
#define DIR2 2
#define PUL2 1

unsigned long timer2[4];
byte last_channel[4];
int input[4];
int dly = 500;
int target = 75;
long timer[2];
int lastdir = 0;
int acc = 500;
int a;

void setup() {
  pinMode(ENA1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(PUL1, OUTPUT);

  pinMode(ENA2, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(PUL2, OUTPUT);

  digitalWrite(ENA1, LOW);
  digitalWrite(DIR1, HIGH);

  digitalWrite(ENA2, LOW);
  digitalWrite(DIR2, HIGH);
  
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);

}

void loop() {


  a = abs(1500 - input[0]);
  if (a > 490) a = 490;
  
  target = map(abs(1500 - input[0]),0,490,1000,100);
  if(input[0] > 1450 && input[0] < 1550){
    digitalWrite(ENA1, HIGH);

    digitalWrite(ENA2, HIGH);
  }
  
  if(input[0] < 1450){
    if(lastdir == 0) dly = 1000;
    digitalWrite(DIR1 , HIGH);
    digitalWrite(ENA1, LOW);

    digitalWrite(DIR2 , HIGH);
    digitalWrite(ENA2, LOW);
    lastdir = 1;
  }
  if(input[0] > 1550){
    if(lastdir == 1) dly = 1000;
    digitalWrite(DIR1 , LOW);
    digitalWrite(ENA1, LOW);

    digitalWrite(DIR2 , LOW);
    digitalWrite(ENA2, LOW);
    lastdir = 0;
  }
  if (target < dly){
    timer[0] = micros();
    if ((timer[0] - timer[1]) > 1000){
      timer[1] = timer[0];
      dly--;
    }
    
    if (dly < target){
      dly = target;
    }
  }

  if (target > dly){
    timer[0] = micros();
    if ((timer[0] - timer[1]) > 500){
      timer[1] = timer[0];
      dly++;
    }
    
    if (dly > target){
      dly = target;
    }
  }

  digitalWrite(PUL1, HIGH);
  digitalWrite(PUL2, HIGH);
  delayMicroseconds(dly);
  digitalWrite(PUL1, LOW);
  digitalWrite(PUL2, LOW);
  delayMicroseconds(dly);
}

ISR(PCINT0_vect) {
  timer2[0] = micros();
  if(last_channel[0] == 0 && PINB & B00000001) {
    last_channel[0] = 1;
    timer2[1] = timer2[0];
  }
  else if(last_channel[0] == 1 && !(PINB & B00000001)) {
    last_channel[0] = 0;
    input[0] = timer2[0] - timer2[1];
  }
}

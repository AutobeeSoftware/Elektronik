#define ENA1 7
#define DIR1 6
#define PUL1 5

#define ENA2 4
#define DIR2 3
#define PUL2 2

unsigned long timer2[4];
byte last_channel[4];
int input[4];
int dly = 500;
int target = 75;
long timer[2];
int lastdir = 0;
int rpm = 120;

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

  Serial.begin(9600);
}

void loop() {

  //max değerlerin aynı olması sağlanacak

  target = map(abs(1500 - input[0]),0,490,1000,500);
  if(input[0] > 1450 && input[0] < 1550){
    digitalWrite(ENA1, HIGH);

    digitalWrite(ENA2, HIGH);
    rpm = 120;
  }
  else{
    digitalWrite(ENA1, LOW);
    digitalWrite(ENA2, LOW);
  }
  
  if(input[0] < 1450){
    if(lastdir == 0){
      digitalWrite(ENA1, HIGH);
      digitalWrite(ENA2, HIGH);
      rpm = 120;
      delay(50);
    }
    digitalWrite(DIR1, HIGH);
    digitalWrite(DIR2, HIGH);
    lastdir = 1;
  }
  if(input[0] > 1550){
    if(lastdir == 1){
      digitalWrite(ENA1, HIGH);
      digitalWrite(ENA2, HIGH);
      rpm = 120;
      delay(50);
    }
    digitalWrite(DIR1 , LOW);
    digitalWrite(DIR2 , LOW);
    lastdir = 0;
  }
  
  if (target < dly){
    timer[0] = micros();
    timer[1] = timer[0];
    rpm++;
    if ((dly - target) > 20) rpm += 5;
    
    if (dly < target){
      dly = target;
    }
  }

  if (target > dly){
    timer[0] = micros();
    timer[1] = timer[0];
    rpm--;
    if ((target - dly) > 20) rpm -= 5;
    
    if (dly > target){
      dly = target;
    }
  }
  dly = (60000000/400)/rpm;
  
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

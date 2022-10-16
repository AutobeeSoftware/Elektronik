#include <Servo.h>

Servo myservo;
int pos = 180;

unsigned long timer[4];
byte last_channel[4];
int input[4];
int period = 0;
int mspeed = 0;
int mode = 0;

int ALI = 6;
int AHI = 9;
int BLI = 10;
int BHI = 11;


void setup() {
  pinMode(ALI, OUTPUT);
  pinMode(AHI, OUTPUT);
  pinMode(BLI, OUTPUT);
  pinMode(BHI, OUTPUT);
  
  PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  PCMSK0 |= (1 << PCINT1);
  PCMSK0 |= (1 << PCINT2);
  PCMSK0 |= (1 << PCINT3);
  
  Serial.begin(9600);
  //myservo.attach(9);
}

void loop() {

  //myservo.write(pos);
  if((period < 20050) && (10950 < period)) {
    mspeed = abs(input[0] - 1500);
    if (mspeed > 500) mspeed = 500;
    mspeed = mspeed/2;
    
    if(input[0] < 1450){
      mode = 1;
    }
    else if(input[0] > 1550){
      mode = 2;
    }
    else{
      mode = 0;
    }
    //Serial.print(mspeed);
  }
  else{
    mspeed = 0;
  }

  if(mode == 0){
    digitalWrite(AHI, LOW);
    digitalWrite(BLI, LOW);
    analogWrite(BHI, LOW);
    digitalWrite(ALI, LOW);
  }
  if(mode == 1){
    digitalWrite(ALI, LOW);
    digitalWrite(BHI, LOW);
    analogWrite(AHI, mspeed);
    digitalWrite(BLI, HIGH);
  }
  if(mode == 2){
    digitalWrite(AHI, LOW);
    digitalWrite(BLI, LOW);
    analogWrite(BHI, mspeed);
    digitalWrite(ALI, HIGH);
  }
  Serial.print(mode);
  Serial.print(input[0]);
  Serial.println(mspeed);
}

ISR(PCINT0_vect) {
  timer[0] = micros();
  if(last_channel[0] == 0 && PINB & B00000001) {
    last_channel[0] = 1;
    period = timer[0] - timer[1];
    timer[1] = timer[0];
  }
  else if(last_channel[0] == 1 && !(PINB & B00000001)) {
    last_channel[0] = 0;
    input[0] = timer[0] - timer[1];
  }
}

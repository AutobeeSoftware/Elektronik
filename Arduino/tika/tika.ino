int EN=3; // Enable Pin Connected to Digital 3
int EN2=4;
int Speed=10; // Motor Speed & Direction Pin Connected to Digital 11
int Speed2=11;

unsigned long timer[4];
byte last_channel[4];
int input[4];

int spd1 = 100;
int spd2 = 100;
int a = 0;

void setup() {
pinMode(EN, OUTPUT); // Enable Pin Made Output
Serial.begin(9600); // Serial Iterface Started at 9600 bps baudrate.
digitalWrite(EN,LOW); // Enable Pin set low for avoding false startups.
delay(1500); // Delay for 1.5 Second.
setPwmFrequency(10, 8); // Set Pin 9's Pwm Frequency tp 3906 hz (3.9 Khz)
setPwmFrequency(11,8);

PCICR |= (1 << PCIE0);
PCMSK0 |= (1 << PCINT0);
PCMSK0 |= (1 << PCINT1);
}


////////// PWM Frequency Modify Function////////////////
void setPwmFrequency(int pin, int divisor) {
byte mode;
if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
switch(divisor) {
case 1: mode = 0x01; break;
case 8: mode = 0x02; break;
case 64: mode = 0x03; break;
case 256: mode = 0x04; break;
case 1024: mode = 0x05; break;
default: return;
}
if(pin == 5 || pin == 6) {
TCCR0B = TCCR0B & 0b11111000 | mode;
} else {
TCCR1B = TCCR1B & 0b11111000 | mode;
}
}
}


void loop() {

a = abs(1000 - input[0]);
if (a > 990) a = 990;
if (a < 10) a = 10;
spd1 = map(a,10,990,0,250);

a = abs(1000 - input[1]);
if (a > 990) a = 990;
if (a < 10) a = 10;
spd2 = map(a,10,990,0,250);
  
Serial.println("FULL FORWARD"); // This Serial Prints sent to Computer Screen to Arduino's Serial Monitor.

if (spd1 > 120 && spd1 < 136){
  digitalWrite(EN,LOW);
  digitalWrite(EN2,LOW);
}
else{
  digitalWrite(EN,HIGH);
  digitalWrite(EN2,HIGH);
}

analogWrite(Speed, spd1); // Full FWD Speed (252/255)
analogWrite(Speed2, spd2);
/*
delay(2000); // 2 Second Delay
  
Serial.println("STOPPED");
digitalWrite(EN,HIGH);
analogWrite(Speed, 128); // Half Duty Cycle and Enable Low Stops Motor (128/255)
delay(1000);

Serial.println("FULL BACKWARD");
digitalWrite(EN,HIGH);
analogWrite(Speed, spd1); // Full BWD Speed (2/255)
delay(2000); // 2 Second Delay

Serial.println("STOPPED");
digitalWrite(EN,HIGH);
analogWrite(Speed, 128); // Half Duty Cycle and Enable Low Stops Motor (128/255)
delay(1000);
*/
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

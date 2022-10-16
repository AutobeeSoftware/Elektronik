int dly = 250;
int max_spd = 220;
int min_spd = 0;

int pwm1 = 9;
int pwm2 = 10;

void setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);

  TCCR1B = TCCR1B & B11111000 | B00000001; // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz on 9,10
  TCCR0B = TCCR0B & B11111000 | B00000010; // for PWM frequency of 7812.50 Hz on 5,6

  digitalWrite(11, HIGH);
  digitalWrite(pwm2, LOW);
  digitalWrite(pwm1, LOW);

  Serial.begin(9600);
}

void loop() {

  

  int spd = analogRead(A0);

  spd = map(spd,0,1023,0,160);
  Serial.println(spd);

  analogWrite(pwm2, spd);

 /*
  for(int i = min_spd; i < max_spd; i++){
    analogWrite(pwm1, i);
    delay(dly);
    Serial.println(i);
  }
  
  delay(20000);

  for(int i = max_spd; i > min_spd; i--){
    analogWrite(pwm1, i);
    delay(dly);
    Serial.println(i);
  }

  

  digitalWrite(pwm1, LOW);
  delay(dly);

  digitalWrite(9,LOW);
  delay(200);
  
  digitalWrite(9, LOW);
  delay(1);
  analogWrite(10, 150);
  delay(3000);

  digitalWrite(10,LOW);
  delay(200);
  */
}

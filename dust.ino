#include <TM1637.h>

int CLK = 4;
int DIO = 5 ;

int measure = A0;
int led = 3;

int sampleTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVolt = 0;
float dustDensity = 0;

char value[4];

TM1637 tm(CLK,DIO);

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  tm.init();
  tm.set(2);

}

void displayNumber(int num)
{   
tm.display(3, num % 10);   
tm.display(2, num / 10 % 10);   
tm.display(1, num / 100 % 10);   
tm.display(0, num / 1000 % 10);
}

void loop() {
  digitalWrite(led, LOW);
  delayMicroseconds(sampleTime);

  voMeasured = analogRead(measure);

  delayMicroseconds(deltaTime);
  digitalWrite(led, HIGH);
  delayMicroseconds(sleepTime);

  calcVolt = voMeasured * (5.0 / 1024.0);

  // Serial.println(calcVolt);
  
  dustDensity = 170 * calcVolt - 0.1;

  Serial.println(dustDensity);
  
  displayNumber(dustDensity);  

  delay(550);
  
}

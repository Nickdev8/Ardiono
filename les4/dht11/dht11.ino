#include <DHT.h>
#define DHTTYPE DHT11
uint8_t DHTPin = D7;
DHT dht(DHTPin, DHTTYPE);

float Temperature, Humidity, HeatIndex;

void setup() {
  Serial.begin(115200);  

  pinMode(D3, OUTPUT); 
  pinMode(D5, OUTPUT); 
  pinMode(D6, OUTPUT); 
  pinMode(A0, OUTPUT); 
}

void loop() {

  ReadDHT11();
  
  doRandomLamps();
  delay(1000);
  doRandomLamps();
  delay(1000);
  doRandomLamps();
  delay(1000);
}

void doRandomLamps()
{
  int A = random(999);
  int B = random(999);
  int C = random(999);
  int D = random(999);

  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);

  if (C > A and A < B)
  {
    digitalWrite(D5, HIGH);
  }
  if (B > C and B > A and C < A)
  {
    digitalWrite(D6, HIGH);
  }

  if (D > A and D > B and D > C)
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
  }


  float value = analogRead(A0);
  Serial.println(value);

  digitalWrite(D3, LOW);
  if (value > 60 && value < 300)
  {
    digitalWrite(D3, HIGH);
  }

}
void setup() {
  Serial.begin(115200);  

  pinMode(D3, OUTPUT); 
  pinMode(D5, OUTPUT); 
  pinMode(D6, OUTPUT); 
}

void loop() {
  //int val = analogRead(D1);  // Read digital value from D0
  //Serial.println(val);        // Print the value directly
  //delay(100);                 // Add a small delay for readability

  int A = random(999);
  int B = random(999);
  int C = random(999);
  int D = random(999);

  digitalWrite(D3, LOW);
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);

  if (A > B or A > C)
  {
    digitalWrite(D3, HIGH);
    Serial.println("D3 = High");
  }
  if (C > A and A < B)
  {
    digitalWrite(D5, HIGH);
    Serial.println("D5 = High");
  }
  if (B > C and B > A and C < A)
  {
    digitalWrite(D6, HIGH);
    Serial.println("D6 = High");
  }

  if (D > A and D > B and D > C)
  {
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);
    Serial.println("All = High");
  }



  Serial.println(A);
  Serial.println(B);
  Serial.println(C);
  Serial.println(D);

  Serial.println("\n");
  delay(100);
  //Serial.println(val);
}

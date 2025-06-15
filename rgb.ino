// C++ code
//
int potvalue = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  potvalue = analogRead(A0);
  analogWrite(10, map(potvalue, 0, 1023, 0, 255));
  analogWrite(11,150);
  analogWrite(9, 70);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(11, map(potvalue, 0, 1023, 0, 255));
  analogWrite(10,0 );
  analogWrite(9, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(9, map(potvalue, 0, 1023, 0, 255));
  analogWrite(10, 0);
  analogWrite(11, 0);
  delay(1000); // Wait for 1000 millisecond(s)
}

// C++ code
//
#include <Servo.h>

int angle = 0;

int i = 0;

Servo servo_9;

void setup()
{
  pinMode(5, OUTPUT);
  servo_9.attach(9, 500, 2500);
  pinMode(4, OUTPUT);

  angle = 0;
}

void loop()
{
  while (angle < 180) {
    angle += 1;
    digitalWrite(5, HIGH);
    servo_9.write(angle);
  }
  delay(2000); // Wait for 2000 millisecond(s)
  if (angle == 180) {
    digitalWrite(5, LOW);
  }

  while (angle > 0) {
    angle += -1;
    digitalWrite(4, HIGH);
    servo_9.write(angle);
  }
  delay(2000); // Wait for 2000 millisecond(s)
  digitalWrite(4, LOW);
}
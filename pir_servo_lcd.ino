// C++ code
//
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

int rotation = 0;

int pirstate = 0;

int val = 0;

int angle = 0;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

Servo servo_4;

void setup()
{
  lcd_1.init();
  lcd_1.backlight();
  pinMode(8, INPUT);
  servo_4.attach(4, 500, 2500);
  Serial.begin(9600);

  rotation = 0;
  pirstate = 0;
  angle = 0;
}

void loop()
{
  val = digitalRead(8);
  lcd_1.clear();
  if (val == 1) {
    angle = 90;
    servo_4.write(angle);
    Serial.println("motion detected");
    lcd_1.setCursor(0, 0);
    lcd_1.print("Hello! Do you want");
    lcd_1.setCursor(0, 1);
    lcd_1.print("to throw it in?");
    delay(200); // Wait for 5000 millisecond(s)
    lcd_1.scrollDisplayLeft();
    delay(2000);
     } else {
    lcd_1.clear();
    angle = 0;
    servo_4.write(angle);
    Serial.println("motion stopped");
    lcd_1.setCursor(2, 1);
    lcd_1.print("Bye!");
    delay(1000); // Wait for 1000 millisecond(s)
  }
}
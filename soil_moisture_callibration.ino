#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/* Change these values based on your calibration values */
#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'

// Sensor pins
#define sensorPower 7
#define sensorPin A0


void setup() {
	pinMode(sensorPower, OUTPUT);
	lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
  lcd.backlight();
	// Initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}
void loop() {
	int moisture = readSensor(); //get the reading from the function below and print it
	Serial.print("Analog Output: ");
	Serial.println(moisture);
  lcd.setCursor(3,0);
  lcd.print(moisture);
  delay(1000);
  
	// Determine status of our soil
	if (moisture < soilWet) {
		Serial.println("Status: Soil is too wet");
    lcd.setCursor(1,0);
    lcd.print("Soil is too wet");
    
	} else if (moisture >= soilWet && moisture < soilDry) {
		  Serial.println("Status: Soil moisture is perfect");
      lcd.setCursor(1,0);
      lcd.print("Soil moisture is perfect");
      
	} else {
		Serial.println("Status: Soil is too dry - time to water!");
    lcd.setCursor(1,0);
    lcd.print("Soil is too dry");
    lcd.setCursor(1,1);
    lcd.print("time to water!");
    
  }
		
	delay(1000);	// Take a reading every second for testing
					// Normally you should take reading perhaps once or twice a day
	Serial.println();
  lcd.clear();
}

//  This function returns the analog soil moisture measurement
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// Allow power to settle
	int val = analogRead(sensorPin);	// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// Return analog moisture value
}
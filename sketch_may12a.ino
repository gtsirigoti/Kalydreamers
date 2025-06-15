// --- PINS ---
const int measurePin = 34;   // ADC-capable pin on ESP32
const int ledPower = 12;     // Controls the LED

// --- Timing ---
const unsigned int samplingTime = 280;
const unsigned int deltaTime = 40;
const unsigned int sleepTime = 9680;

// --- Filter Settings ---
const int numReadings = 10;            // Number of samples for moving average
int readings[numReadings];             // Circular buffer
int readIndex = 0;
int total = 0;
int average = 0;

// --- Measurement Variables ---
float calcVoltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPower, OUTPUT);
  digitalWrite(ledPower, HIGH);        // Turn off LED initially

  // Initialize readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  digitalWrite(ledPower, LOW);                 // LED ON
  delayMicroseconds(samplingTime);

  int voMeasured = analogRead(measurePin);     // Raw sensor reading

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);                // LED OFF
  delayMicroseconds(sleepTime);

  // --- Moving Average Filter ---
  total = total - readings[readIndex];         // Subtract oldest value
  readings[readIndex] = voMeasured;            // Replace with new value
  total = total + readings[readIndex];         // Add new value
  readIndex = (readIndex + 1) % numReadings;   // Advance index
  average = total / numReadings;               // Compute average

  // --- Convert to voltage (3.3V reference on ESP32) ---
  calcVoltage = average * (3.3 / 4095.0);

  // --- Dust Density (adjust for 3.3V logic if needed) ---
  dustDensity = 0.17 * calcVoltage - 0.1;
  if (dustDensity < 0) dustDensity = 0.00;

  // --- Output ---
  Serial.println("Filtered Raw Value (0-4095):");
  Serial.println(average);
  Serial.println("Voltage:");
  Serial.println(calcVoltage, 3);
  Serial.println("Dust Density (mg/m^3):");
  Serial.println(dustDensity, 3);

  delay(1000);  // Wait 1 second before next reading
}

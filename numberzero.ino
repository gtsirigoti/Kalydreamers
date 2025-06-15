// Pin definitions
const int segmentPins[] = {2, 3, 4, 5, 6, 7, 8}; // a, b, c, d, e, f, g

// Segment states for the number 0 (a, b, c, d, e, f, g)
const int numberOne[7] = {0, 0, 1, 1, 1, 1,1}; // g is OFF
const int numberTwo[7] = {0, 1, 1, 1, 1, 0,1}; // g is OFF

void setup() {
  // Set all segment pins as OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Display the number 0
 // displayNumber(numberTwo);
}

void loop() {
displayNumber(numberOne);// Do nothing, number stays displayed
delay(1000);
displayNumber(numberTwo);
delay(1000);
}

void displayNumber(const int number[]) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], number[i]);
  }
}
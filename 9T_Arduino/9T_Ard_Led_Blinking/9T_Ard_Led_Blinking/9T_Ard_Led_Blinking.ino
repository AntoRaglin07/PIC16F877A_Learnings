
const int ledPin1 = 12; // Pin connected to LED 1
const int ledPin2 = 13; // Pin connected to LED 2




void setup() {
  // Initialize the digital pins as outputs
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // Turn LED 1 on, and LED 2 off
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  delay(1000); 

  // Turn LED 1 off, and LED 2 on
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, HIGH);
  delay(1000);
}

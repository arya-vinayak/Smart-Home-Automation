#define ledPin 13
#define sensorPin A0
#define sensorPinD 10
#define Buzzer 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(ledPin, LOW);
}

int readSensor() {
  unsigned int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
    // digitalWrite(Buzzer, HIGH);
  if (outputValue >= 2) {
    analogWrite(ledPin, outputValue); // generate PWM signal
    delay(500);
    digitalWrite(Buzzer,HIGH);
    delay(3000);
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(Buzzer, LOW); 
  }
  return outputValue;             // Return analog moisture value
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Analog output: ");
  Serial.println(readSensor());
  delay(500);
}

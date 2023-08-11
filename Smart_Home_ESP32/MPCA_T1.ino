#define BLYNK_TEMPLATE_ID "TMPL6UD__iS8G"
#define BLYNK_TEMPLATE_NAME "MY ESP"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

#include "BlynkEdgent.h"
#include <DHT.h> 
BlynkTimer timer; 
// BlynkTimer timer2; 

#include <ESP32Servo.h>
#define DHTPIN 19         //pin where the dht11 is connected
#define GAS_SENSOR 4
 
DHT dht(DHTPIN, DHT11);
Servo servo;

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(2,pinValue);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(21,pinValue);
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(5,pinValue);
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  digitalWrite(18,pinValue);
}

BLYNK_WRITE(V6) {
  servo.write(param.asInt());
}

int data = 0;
float t = 0, h = 0;

void sendTemp() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.println("Readings:");
  Serial.println(h);
  Serial.println(t);
  Blynk.virtualWrite(V4, h);
  Blynk.virtualWrite(V5, t);
  if(t >= 32) {
    Blynk.logEvent("too_hot");
  }
}

void sendSmoke() {
  data = analogRead(GAS_SENSOR);
  Blynk.virtualWrite(V6, data); // Blynk INPUT Connect V6 Pin
  Serial.println(data);
  Serial.print("Gas Sensor: ");  
  Serial.print(data);   /*Read value printed*/
  Serial.print("\t");
  Serial.print("\t\n");
  if (data > 700 )
  {
    Blynk.logEvent("smoke_detected");
  }
}

void setup()
{
  pinMode(2, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  servo.attach(15);
  Serial.begin(115200);
  dht.begin();
  delay(100);
  BlynkEdgent.begin();
  
  // delay(100);
  timer.setInterval(3000L,sendTemp);
  // timer.setInterval(1000L,sendSmoke);                                              Q
}

void loop() {
  // sendSensor();
  timer.run();
  BlynkEdgent.run();
  // delay(100);
}

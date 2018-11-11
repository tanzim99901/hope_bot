#include <SoftwareSerial.h>

SoftwareSerial bluetooth(62, 63); // RX (arduino) | TX (arduino)

void setup()
{
  pinMode(9, OUTPUT);  // Pull the KEY pin HIGH to enter AT Command mode
  digitalWrite(9, HIGH);
  Serial.begin(9600);
  Serial.println("AT Command Mode");
  bluetooth.begin(38400);  // HC-05 default speed in AT command mode
}

void loop()
{
  if (bluetooth.available()) Serial.write(bluetooth.read()); // Read from HC-05 and send to Arduino Serial Monitor
  
  if (Serial.available()) bluetooth.write(Serial.read()); // Read from Arduino Serial Monitor and send to HC-05
}

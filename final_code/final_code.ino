#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <usb.h>

#include "hidjoystickrptparser.h"

#define in1 47
#define in2 49
#define in3 51
#define in4 53
#define ena 11
#define enb 12

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);
int X1, Y1, X2, Y2, hat, button, right_joy, left_joy;

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay(200);

  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop()
{
  Usb.Task();
  get_joystick();
  move_robot();
}

void move_robot()
{
  left_motor(left_joy);
  right_motor(right_joy);
}

void get_joystick()
{
  parse_values();
  correct_right();
  correct_left();
  Serial.print(left_joy);
  Serial.print("\t");
  Serial.print(right_joy);
  Serial.print("\t");
  Serial.print(hat);
  Serial.print("\t");
  Serial.println(button);
}

void correct_right()
{
  if (Y1 >= 126 && Y1 <= 128) Y1 = 0;
  else if (Y1 > 128) Y1 = map(Y1, 128, 255, -1, -255);
  else if (Y1 < 126) Y1 = map(Y1, 0, 127, 255, 1);
  right_joy = Y1;
}

void correct_left()
{
  if (X2 >= 126 && X2 <= 128) X2 = 0;
  else if (X2 > 128) X2 = map(X2, 128, 255, -1, -255);
  else if (X2 < 126) X2 = map(X2, 0, 127, 255, 1);
  left_joy = X2;
}

void parse_values()
{
  X1 = JoyEvents.X_par;
  Y1 = JoyEvents.Y_par;
  X2 = JoyEvents.Z_par;
  Y2 = JoyEvents.Rz_par;
  hat = JoyEvents.hat_par;
  button = JoyEvents.but_par;
}

void left_motor(int left_speed)
{
  if (left_speed == 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  else if (left_speed > 0)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  else if (left_speed < 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(ena, abs(left_speed));
}

void right_motor(int right_speed)
{
  if (right_speed == 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  else if (right_speed > 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  else if (right_speed < 0)
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  analogWrite(enb, abs(right_speed));
}


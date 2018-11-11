#include "hidjoystickrptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
  joyEvents(evt),
  oldHat(0xDE),
  oldButtons(0) {
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    oldPad[i] = 0xD;
}

void JoystickReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  bool match = true;

  // Checking if there are changes in report since the method was last called
  for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
    if (buf[i] != oldPad[i]) {
      match = false;
      break;
    }

  // Calling Game Pad event handler
  if (!match && joyEvents) {
    //joyEvents->OnGamePadChanged((const GamePadEventData*)buf);
    joyEvents->X_val((const GamePadEventData*)buf);
    joyEvents->Y_val((const GamePadEventData*)buf);
    joyEvents->Z_val((const GamePadEventData*)buf);
    joyEvents->Rz_val((const GamePadEventData*)buf);
    for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
  }

  uint8_t hat = (buf[5] & 0xF);

  // Calling Hat Switch event handler
  if (hat != oldHat && joyEvents) {
    //joyEvents->OnHatSwitch(hat);
    joyEvents->hat_val(hat);
    oldHat = hat;
  }

  uint16_t buttons = (0x0000 | buf[6]);
  buttons <<= 4;
  buttons |= (buf[5] >> 4);
  uint16_t changes = (buttons ^ oldButtons);

  // Calling Button Event Handler for every button changed
  if (changes) {
    for (uint8_t i = 0; i < 0x0C; i++) {
      uint16_t mask = (0x0001 << i);

      if (((mask & changes) > 0) && joyEvents)
        joyEvents->but_val(i+1);
    }
    oldButtons = buttons;
  }
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
  Serial.print("X1: ");
  Serial.print(evt->X, DEC);
  //kasakj = evt->X;
  Serial.print("\tY1: ");
  Serial.print(evt->Y, DEC);
  Serial.print("\tX2: ");
  Serial.print(evt->Z2, DEC);
  Serial.print("\tY2: ");
  Serial.print(evt->Rz, DEC);
  Serial.println("");
  //Serial.println(evt->X);
}

/*void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
        Serial.print("X1: ");
        PrintHex<uint8_t > (evt->X, 0x80);
        Serial.print("\tY1: ");
        PrintHex<uint8_t > (evt->Y, 0x80);
        Serial.print("\tX2: ");
        PrintHex<uint8_t > (evt->Z1, 0x80);
        Serial.print("\tY2: ");
        PrintHex<uint8_t > (evt->Z2, 0x80);
        Serial.print("\tRz: ");
        PrintHex<uint8_t > (evt->Rz, 0x80);
        Serial.println("");
  }*/

void JoystickEvents::OnHatSwitch(uint8_t hat) {
  Serial.print("Hat Switch: ");
  Serial.print(hat, DEC);
  Serial.println("");
  delay(500);
}

void JoystickEvents::OnButtonUp(uint8_t but_id) {
  Serial.print("Released: ");
  Serial.println(but_id, DEC);
  delay(500);
}

void JoystickEvents::OnButtonDn(uint8_t but_id) {
  Serial.print("Pressed: ");
  Serial.println(but_id, DEC);
  delay(500);

}

int JoystickEvents::X_val(const GamePadEventData *evt)
{
  //Serial.print(evt->X, DEC);
  return X_par = evt->X;
}

int JoystickEvents::Y_val(const GamePadEventData *evt)
{
  //Serial.print("\t");
  //Serial.print(evt->Y, DEC);
  return Y_par = evt->Y;
}
int JoystickEvents::Z_val(const GamePadEventData *evt)
{
  //Serial.print("\t");
  //Serial.print(evt->Z2, DEC);
  return Z_par = evt->Z2;
}
int JoystickEvents::Rz_val(const GamePadEventData *evt)
{
  //Serial.print("\t");
  //Serial.print(evt->Rz, DEC);
  return Rz_par = evt->Rz;
}
int JoystickEvents::hat_val(uint8_t hat)
{
  //Serial.print(hat, DEC);
  //Serial.println("");
  return hat_par = hat;
}
int JoystickEvents::but_val(uint8_t but_id)
{
  //Serial.print("Pressed: ");
  //Serial.println(but_id, DEC);
  return but_par = but_id;
}

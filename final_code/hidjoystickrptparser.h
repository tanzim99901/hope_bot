#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <hid.h>

struct GamePadEventData {
        uint8_t X, Y, Z1, Z2, Rz;
};

class JoystickEvents {
public:
        virtual void OnGamePadChanged(const GamePadEventData *evt);
        virtual void OnHatSwitch(uint8_t hat);
        virtual void OnButtonUp(uint8_t but_id);
        virtual void OnButtonDn(uint8_t but_id);
        virtual int X_val(const GamePadEventData *evt);
        virtual int Y_val(const GamePadEventData *evt);
        virtual int Z_val(const GamePadEventData *evt);
        virtual int Rz_val(const GamePadEventData *evt);
        virtual int hat_val(uint8_t hat);
        virtual int but_val(uint8_t but_id);
        int X_par, Y_par, Z_par, Rz_par, hat_par, but_par;
};

#define RPT_GEMEPAD_LEN		5

class JoystickReportParser : public HIDReportParser {
        JoystickEvents *joyEvents;

        uint8_t oldPad[RPT_GEMEPAD_LEN];
        uint8_t oldHat;
        uint16_t oldButtons;

public:
        JoystickReportParser(JoystickEvents *evt);

        virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__

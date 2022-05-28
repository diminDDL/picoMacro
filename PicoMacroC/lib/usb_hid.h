#ifndef USB_HID_H_
#define USB_HID_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

// HID button struct
enum{
    SHORTCUT = 0,   // uses a shortcutBase array and sends very specific keys in a very specific manner as described in the array
    TEXT,           // just matches a char array with a key and sends that (when using different languages this will be funky but there is no way to fix it in the USB standard, so I an sorry)
    MEDIA,          // media keys aka volume UP DOWN, PAUSE and so on only one key per physical key because if you want to mix it with other stuff you are deranged
    GAMEPAD         // same as shortcut, just uses gamepad keys
};
struct shortcutBase // structure: {HID_key, pressTime(mS), releaseTime(mS), timeMultiplier}
{
    u_int8_t HIDkey;        // the HID keycode
    u_int8_t pressTime;     // the time the key should be pressed down (ms)
    u_int8_t releaseTime;   // the time the key should be released (ms)
    u_int8_t multiplier;    // the multiplier for the time (1 = normal, 2 = double, 3 = triple, 4 = quadruple, etc)
};
struct key
{
    u_int8_t keyNum;        // the key number on the macropad
    u_int8_t keyXval;       // the x value of the key on the macropad
    u_int8_t keyYval;       // the y value of the key on the macropad
    u_int8_t HIDtype;       // the type of HID keycode to send
    u_int8_t delayMs;       // the delay between the key press and release (ms) except when using the SHORTCUT type
};



// different tasks
void hidInit(void);
void hidRun(bool wakeup);

// different callbacks
void tud_mount_cb(void);
void tud_umount_cb(void);
void tud_suspend_cb(bool remote_wakeup_en);
void tud_resume_cb(void);

// HID service functions
static void send_hid_report(uint8_t report_id, uint32_t btn);
void hid_task(bool wakeup);
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len);
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

#endif /* USB_HID_H_ */
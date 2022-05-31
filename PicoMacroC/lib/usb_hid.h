#ifndef USB_HID_H_
#define USB_HID_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

// HID button struct
struct shortcutBase // structure: {HID_key, pressTime(mS), releaseTime(mS), timeMultiplier}
{
    u_int8_t HIDkey;        // the HID keycode
    u_int8_t pressTime;     // the time the key should be pressed down (ms)
    u_int8_t releaseTime;   // the time the key should be released (ms)
    u_int8_t multiplier;    // the multiplier for the time (1 = normal, 2 = double, 3 = triple, 4 = quadruple, etc)
};

class Key{
    public:
    Key(uint type, u_int8_t keyXvalue, u_int8_t keyYvalue) : HIDtype {type}, keyXval {keyXvalue}, keyYval {keyYvalue}
    {
    }
    uint getType(){
        return HIDtype;
    }
    u_int8_t getKeyNum(){
        return keyXval;
    }
    void setRGB(uint32_t color){
        RGBcode = color;
    }
    void clearShortcut(){
        shortcuts.clear();
    }
    void addKey(shortcutBase s){
        shortcuts.push_back(s);
    }
    uint getShortcutSize(){
        return shortcuts.size();
    }
    shortcutBase getShortcut(uint i){
        return shortcuts[i];
    }
    void sendShortcut(bool btn){
        static uint8_t report[6] = {0}; // think of how to implement this so that multiple buttons can be pressed at once and it doesn't stall the program
        // start timestamp
        // if the button is pressed proceed
        // use the delta from the current timestamp and the start one to detect how much time has elapsed
        // iterate over the vector of keys and check the time of start
        // if something starts add it to the report
        // if the report is full, release the oldest key TODO tell the user about that
        // TODO
        // if it tells to release a key according to the vector, do so.
        // send the report
        // stop here when button pressed, else:
        // after completion send NULL report
    }
    private:
    std::vector<shortcutBase> shortcuts;
    uint HIDtype {};            // the type of HID device
    uint32_t RGBcode;           // LED color
    u_int8_t keyNum {};         // the key number on the macropad
    u_int8_t keyXval {};        // the x value of the key on the macropad
    u_int8_t keyYval {};        // the y value of the key on the macropad
    u_int8_t delayMs;           // the delay between the key press and release (ms) except when using the SHORTCUT type
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
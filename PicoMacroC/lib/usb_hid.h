#ifndef USB_HID_H_
#define USB_HID_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

#include "lib/kbScan.h"

extern bool lastReportFinished;

// HID button struct
struct shortcutBase // structure: {HID_key, pressTime(mS), releaseTime(mS), timeMultiplier}
{
    uint8_t HIDkey;        // the HID keycode
    uint32_t pressTime;     // the time the key should be pressed down (ms)
    uint32_t releaseTime;   // the time the key should be released (ms)
};


class Key{
    public:
    struct repeating_timer timer;
    void* payloadPtr;
    uint16_t *reportPtr;
    Key(uint type, uint8_t keyXvalue, uint8_t keyYvalue) : HIDtype {type}, keyXval {keyXvalue}, keyYval {keyYvalue}
    {
    }
    uint getType(){
        return HIDtype;
    }
    uint8_t getKeyNum(){
        return keyXval * keyYval;
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
    // call this function in a loop with the status of the button as an argument, it should automatically handle the button press and release
    void sendShortcut(bool btn){
        static uint8_t report[6] = {0};     // think of how to implement this so that multiple buttons can be pressed at once and it doesn't stall the program
        static uint64_t startTime = 0;      // TODO change to uint64_t
        static uint8_t releasedCount = 0;
        static bool has_keyboard_key = false;
        static bool finished = false;
        static bool startedReport = false;
        static uint32_t lastReleaseTime = 0;
        // start the report
        if(btn && !startedReport){
            startedReport = true;
        }
        if(HIDtype == REPORT_ID_KEYBOARD && !finished && startedReport && lastReportFinished){
            if(startTime == 0)
                startTime = time_us_64();
            // find the last release time, we can leave once we release the last key
            if(lastReleaseTime == 0){
                for(uint i = 0; i < shortcuts.size(); i++){
                    if(shortcuts[i].releaseTime > lastReleaseTime)
                        lastReleaseTime = shortcuts[i].releaseTime;
                }
            }
            uint32_t elapsedTime = (time_us_64() - startTime) / 1000;    // TODO change to uint64_t
            for(uint i = 0; i < shortcuts.size(); i++){
                //printf("(info.) elapsedTime: %d, pressTime: %d, key %d\n", elapsedTime, shortcuts[i].pressTime, shortcuts[i].HIDkey);
                if(elapsedTime >= shortcuts[i].pressTime && elapsedTime <= shortcuts[i].releaseTime){
                    // check if shortcuts[i].HIDkey is already in the report
                    bool found = false;
                    for(uint j = 0; j < sizeof(report[0]); j++){
                        if(report[j] == shortcuts[i].HIDkey){
                            found = true;
                            break;
                        }
                    }
                    // find the first zero in the array and add the key there
                    if(!found){
                        for(uint j = 0; j < sizeof(report[0]); j++){    // TODO debug this (not added to report????)
                            if(report[j] == 0){
                                report[j] = shortcuts[i].HIDkey;
                                break;
                            }
                        }
                    }

                }else if(elapsedTime >= shortcuts[i].releaseTime){ // if the key has elapsed, find it in the report array and remove it, defragment the array, send empty report
                    for(uint j = 0; j < sizeof(report); j++){
                        bool reset = true;
                        if(report[j] == shortcuts[i].HIDkey){
                            for(uint k = 0; k < shortcuts.size(); k++){
                                if(report[j] == shortcuts[k].HIDkey && elapsedTime >= shortcuts[k].pressTime && shortcuts[k].releaseTime >= elapsedTime && shortcuts[k].releaseTime >= shortcuts[i].releaseTime){
                                    reset = false;
                                }
                            }
                            if(reset) report[j] = 0;
                        }
                    }
                    //move all the non zero elements of the array to the right
                    int count = 0;
                    for (int i = 0; i < sizeof(report); i++)
                        if (report[i] != 0)
                            report[count++] = report[i];
                    while (count < sizeof(report))
                        report[count++] = 0;

                    // if we reach the last release time that means we are done
                    if(elapsedTime > lastReleaseTime){
                        startTime = 0;
                        finished = true;
                    }
                }
                
            }
            tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, report);
            has_keyboard_key = true;
            lastReportFinished = false;
            //printf("(Press) reporting: %d, %d, %d, %d, %d, %d\n", report[0], report[1], report[2], report[3], report[4], report[5]);
        }else{
            lastReleaseTime = 0;
            startedReport = false;
            if (has_keyboard_key && lastReportFinished) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
            if (!btn) has_keyboard_key = false;
            if (!btn) finished = false;
            startTime = 0;
        }
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
    uint8_t keyNum {};         // the key number on the macropad
    uint8_t keyXval {};        // the x value of the key on the macropad
    uint8_t keyYval {};        // the y value of the key on the macropad
    uint8_t delayMs;           // the delay between the key press and release (ms) except when using the SHORTCUT type

};


// different tasks
void hidInit(void);
void hidRun(void);

// different callbacks
void tud_mount_cb(void);
void tud_umount_cb(void);
void tud_suspend_cb(bool remote_wakeup_en);
void tud_resume_cb(void);

// HID service functions
//static void send_hid_report(uint8_t report_id, uint32_t btn);
//void hid_task(bool wakeup);
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint8_t len);
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

void startKeyPulling(Key key, uint16_t *report, uint callIntervalMs);
void stopKeyPulling(Key key);
bool reportTimerCallback(struct repeating_timer *t);

#endif /* USB_HID_H_ */
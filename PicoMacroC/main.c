#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "lib/config.h"
#include "lib/wsLED.h"
#include "lib/usb_hid.h"
#include "lib/kbScan.h"

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void sendkey1(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_R;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey2(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_F;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey3(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_SHIFT_LEFT;
        keycode[1] = HID_KEY_T;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey4(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_CONTROL_LEFT;
        keycode[1] = HID_KEY_H;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey5(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_CONTROL_LEFT;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey6(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_SHIFT_LEFT;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey7(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_CONTROL_LEFT;
        keycode[1] = HID_KEY_SHIFT_LEFT;
        keycode[2] = HID_KEY_A;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    void sendkey8(bool btn){
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_ENTER;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
int main() {
    stdio_init_all();
    hidInit();

    // Choose PIO instance (0 or 1)
    PIO pio = pio0;
    // Get first free state machine in PIO 0
    uint wsSm = pio_claim_unused_sm(pio, true);
    // Init WS PIO
    initWSPio(pio, wsSm, clock_get_hz(clk_sys));
    initKbScan(KEYBOARD_PIN_X_BEGIN, KEYBOARD_PIN_Y_BEGIN, KEYBOARD_SIZE_X, KEYBOARD_SIZE_Y, 100);
    // gpio_init(KEYBOARD_PIN_X_BEGIN);
    // gpio_set_dir(KEYBOARD_PIN_X_BEGIN, GPIO_IN);
    // gpio_init(KEYBOARD_PIN_Y_BEGIN);
    // gpio_set_dir(KEYBOARD_PIN_Y_BEGIN, GPIO_OUT);
    // gpio_put(KEYBOARD_PIN_Y_BEGIN, true);
    while (true) {
        // if(gpio_get(KEYBOARD_PIN_X_BEGIN)){
        //     put_pixel(rgb_u32(255, 0, 0), pio, wsSm);
        //     put_pixel(rgb_u32(0, 255, 0), pio, wsSm);
        //     put_pixel(rgb_u32(0, 0, 255), pio, wsSm);
        // }else{
        //     put_pixel(rgb_u32(0, 0, 0), pio, wsSm);
        //     put_pixel(rgb_u32(0, 0, 0), pio, wsSm);
        //     put_pixel(rgb_u32(0, 0, 0), pio, wsSm);
        // }
        //hidRun(gpio_get(KEYBOARD_PIN_X_BEGIN));
        sleep_ms(10);
        uint16_t report = getKbReport();
        printBits(sizeof(report), &report);
        if(report == 1){
            sendkey1(true);

        }else if(report == 2){
            sendkey2(true);
        }else if(report == 4){
            sendkey3(true);
        }else if(report == 8){
            sendkey4(true);
        }else if(report == 16){
            sendkey5(true);
        }else if (report == 32){
            sendkey6(true);
        }else if (report == 64){
            sendkey7(true);
        }else if (report == 128){
            sendkey8(true);
        }else{
            sendkey1(false);
            sendkey2(false);
            sendkey3(false);
            sendkey4(false);
            sendkey5(false);
            sendkey6(false);
            sendkey7(false);
            sendkey8(false);
        }
        //printf(" - %u\n", report);
    }
}
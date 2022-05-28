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
void sendkey9(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_HOME;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey10(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_END;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey11(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_CONTROL_LEFT;
    keycode[1] = HID_KEY_Z;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey12(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_BACKSPACE;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey13(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_DELETE;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey14(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_SPACE;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey15(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_CONTROL_LEFT;
    keycode[1] = HID_KEY_C;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    has_keyboard_key = true;
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
void sendkey16(bool btn){
  static bool has_keyboard_key = false;
  if ( btn )
  {
    uint8_t keycode[6] = { 0 };
    keycode[0] = HID_KEY_CONTROL_LEFT;
    keycode[1] = HID_KEY_V;
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
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
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
        hidRun(false);
        sleep_ms(10);
        uint16_t report = getKbReport();
        //printBits(sizeof(report), &report);
        bool pressed = false;
        // TODO
        // https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c
        
        // TODO
        // instead of doing thiss, each function adds to the key report array (6 bytes) and that is sent instead, this will support multiple button presses
        put_pixel(rgb_u32(3, 144, 252), pio, wsSm);
        put_pixel(rgb_u32(40, 3, 252), pio, wsSm);
        put_pixel(rgb_u32(255, 234, 5), pio, wsSm);
        put_pixel(rgb_u32(117, 235, 133), pio, wsSm);

        put_pixel(rgb_u32(80, 173, 162), pio, wsSm);
        put_pixel(rgb_u32(138, 138, 138), pio, wsSm);
        put_pixel(rgb_u32(143, 0, 0), pio, wsSm);
        put_pixel(rgb_u32(4, 255, 0), pio, wsSm);

        put_pixel(rgb_u32(162, 255, 0), pio, wsSm);
        put_pixel(rgb_u32(255, 106, 0), pio, wsSm);
        put_pixel(rgb_u32(5, 213, 232), pio, wsSm);
        put_pixel(rgb_u32(232, 54, 5), pio, wsSm);

        put_pixel(rgb_u32(255, 0, 0), pio, wsSm);
        put_pixel(rgb_u32(0, 199, 50), pio, wsSm);
        put_pixel(rgb_u32(195, 0, 255), pio, wsSm);
        put_pixel(rgb_u32(255, 0, 247), pio, wsSm);

        if(isPressedAtPos(report, 0)){
          sendkey1(true);
          pressed = true;
        }
        if(isPressedAtPos(report, 1)){
            sendkey2(true);
            pressed = true;
        }
        if(isPressedAtPos(report, 2)){
            sendkey3(true);
            pressed = true;
        }
        if(isPressedAtPos(report, 3)){
            sendkey4(true);
            pressed = true;
        }
        if(isPressedAtPos(report, 4)){
            sendkey5(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 5)){
            sendkey6(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 6)){
            sendkey7(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 7)){
            sendkey8(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 8)){
            sendkey9(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 9)){
            sendkey10(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 10)){
            sendkey11(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 11)){
            sendkey12(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 12)){
            sendkey13(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 13)){
            sendkey14(true);
            pressed = true;
        }
        if (isPressedAtPos(report, 14)){
            sendkey15(true);
            pressed = true;
        }
        if(isPressedAtPos(report, 15)){
            sendkey16(true);
            pressed = true;
        }
        gpio_put(PICO_DEFAULT_LED_PIN, pressed);
        if (!pressed) {
            sendkey1(false);
            sendkey2(false);
            sendkey3(false);
            sendkey4(false);
            sendkey5(false);
            sendkey6(false);
            sendkey7(false);
            sendkey8(false);
            sendkey9(false);
            sendkey10(false);
            sendkey11(false);
            sendkey12(false);
            sendkey13(false);
            sendkey14(false);
            sendkey15(false);
            sendkey16(false);
        }
        if(board_button_read()){
          printf("rebooting");
          sleep_ms(100);
          reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
        }
        //printf(" - %u\n", report);
    }
}
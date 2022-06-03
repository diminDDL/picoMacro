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
Key key2(REPORT_ID_KEYBOARD, 2, 1);
shortcutBase q = {HID_KEY_Q, 0, 100};
shortcutBase b = {HID_KEY_B, 110, 200};
shortcutBase c = {HID_KEY_C, 210, 300};
shortcutBase d = {HID_KEY_D, 310, 400};
shortcutBase e = {HID_KEY_E, 410, 500};
shortcutBase f = {HID_KEY_F, 610, 700};
shortcutBase g = {HID_KEY_G, 710, 800};
int main() {
    stdio_init_all();
    hidInit();
    key2.addKey(q);
    key2.addKey(b);
    key2.addKey(c);
    key2.addKey(d);
    key2.addKey(e);
    key2.addKey(f);
    key2.addKey(g);

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
        hidRun(false);
        sleep_ms(10);
        uint16_t report = getKbReport();
        //printBits(sizeof(report), &report);
        // TODO
        // https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c
        
        // TODO
        // instead of doing thiss, each function adds to the key report array (6 bytes) and that is sent instead, this will support multiple button presses
        put_pixel(rgb_u32(100, 0, 0), pio, wsSm);
        put_pixel(rgb_u32(0, 50, 100), pio, wsSm);
        sendkey1(isPressedAtPos(report, 0));
        key2.sendShortcut(isPressedAtPos(report, 1));
        gpio_put(PICO_DEFAULT_LED_PIN, isPressedAtPos(report, 1));
        if(board_button_read()){
          printf("rebooting\n");
          sleep_ms(100);
          reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
        }
        //printf(" - %u\n", report);
    }
}
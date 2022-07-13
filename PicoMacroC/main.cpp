#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "lib/config.h"
#include "lib/wsLED.h"
#include "lib/usb_hid.h"
#include "lib/kbScan.h"
//TODO remove the printf's
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
    printf("\n");
  }else
  {
    // send empty key report if previously has key pressed
    if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    has_keyboard_key = false;
  }
}
Key key2(REPORT_ID_KEYBOARD, 2, 1);
shortcutBase a = {HID_KEY_CONTROL_LEFT, 0, 10};
shortcutBase b = {HID_KEY_CONTROL_RIGHT, 0, 10};
shortcutBase c = {HID_KEY_SHIFT_LEFT, 50, 80};
// shortcutBase d = {HID_KEY_D, 0, 10};
// shortcutBase e = {HID_KEY_E, 0, 10};
// shortcutBase f = {HID_KEY_F, 0, 10};
// shortcutBase g = {HID_KEY_G, 50, 60};

int main() {
    stdio_init_all();
    hidInit();
    key2.addKey(a);
    key2.addKey(b);
    key2.addKey(c);
    // key2.addKey(d);
    // key2.addKey(e);
    // key2.addKey(f);
    // key2.addKey(g);

    // Choose PIO instance (0 or 1)
    PIO pio = pio0;
    // Get first free state machine in PIO 0
    uint wsSm = pio_claim_unused_sm(pio, true);
    // Init WS PIO
    initWSPio(pio, wsSm, clock_get_hz(clk_sys));
    initKbScan(KEYBOARD_PIN_X_BEGIN, KEYBOARD_PIN_Y_BEGIN, KEYBOARD_SIZE_X, KEYBOARD_SIZE_Y, 100);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    uint16_t report = 0;
    put_pixel(rgb_u32(100, 0, 0), pio, wsSm);
    put_pixel(rgb_u32(0, 50, 100), pio, wsSm);
    sleep_ms(3000);
    printf("Initialising key pulling\n");

    //startKeyPulling(key2, &report, 10);

    while (true) {
        hidRun();
        sleep_ms(5);
        report = getKbReport();
        //printBits(sizeof(report), &report);
        // TODO
        // https://github.com/raspberrypi/pico-examples/blob/master/flash/program/flash_program.c
        
        sendkey1(isPressedAtPos(report, 0));

        key2.sendShortcut(isPressedAtPos(report, 1));

        if(board_button_read()){
          printf("rebooting\n");
          // send zeros to all the pixels
          sleep_ms(50);
          for(int i = 0; i < KEYBOARD_SIZE_X * KEYBOARD_SIZE_Y; i++){
            put_pixel(rgb_u32(0, 0, 0), pio, wsSm);
          }
          sleep_ms(50);
          reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
        }
        //printf(" - %u\n", report);
    }
}
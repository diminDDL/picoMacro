#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "lib/config.h"
#include "lib/wsLED.h"
#include "lib/usb_hid.h"

int main() {
    stdio_init_all();
    hidInit();

    // Choose PIO instance (0 or 1)
    PIO pio = pio0;

    // Get first free state machine in PIO 0
    uint sm = pio_claim_unused_sm(pio, true);

    // Init PIO
    initPio(pio, sm, clock_get_hz(clk_sys));

    gpio_init(KEYBOARD_PIN_X_BEGIN);
    gpio_set_dir(KEYBOARD_PIN_X_BEGIN, GPIO_IN);
    gpio_init(KEYBOARD_PIN_Y_BEGIN);
    gpio_set_dir(KEYBOARD_PIN_Y_BEGIN, GPIO_OUT);
    gpio_put(KEYBOARD_PIN_Y_BEGIN, true);
    while (true) {
        if(gpio_get(KEYBOARD_PIN_X_BEGIN)){
            put_pixel(rgb_u32(255, 0, 0), pio, sm);
            put_pixel(rgb_u32(0, 255, 0), pio, sm);
            put_pixel(rgb_u32(0, 0, 255), pio, sm);
        }else{
            put_pixel(rgb_u32(0, 0, 0), pio, sm);
            put_pixel(rgb_u32(0, 0, 0), pio, sm);
            put_pixel(rgb_u32(0, 0, 0), pio, sm);
        }
        hidRun(gpio_get(KEYBOARD_PIN_X_BEGIN));
        sleep_ms(10);
        printf("this is a test\n");
        

        // reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
    }
}
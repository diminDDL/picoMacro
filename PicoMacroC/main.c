#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "lib/config.h"
#include "lib/wsLED.h"
#include "lib/usb_hid.h"

int main() {
    stdio_init_all();
    hidInit();

    static const uint led_pin = 25;
    static const float pio_freq = 2000;

    // Choose PIO instance (0 or 1)
    PIO pio = pio0;

    // Get first free state machine in PIO 0
    uint sm = pio_claim_unused_sm(pio, true);

    // Add PIO program to PIO instruction memory. SDK will find location and
    // return with the memory offset of the program.
    uint offset = pio_add_program(pio, &WS_LED_program);

    // Calculate the PIO clock divider
    float div = (float)clock_get_hz(clk_sys) / pio_freq;

    // Initialize the program using the helper function in our .pio file
    ws_program_init(pio, sm, offset, WS2812_PIN, WS2812_frequency, WS2812_WHITE);

    // Do nothing

    gpio_init(KEYBOARD_PIN_X_BEGIN);
    gpio_set_dir(KEYBOARD_PIN_X_BEGIN, GPIO_IN);
    gpio_init(KEYBOARD_PIN_Y_BEGIN);
    gpio_set_dir(KEYBOARD_PIN_Y_BEGIN, GPIO_OUT);
    gpio_put(KEYBOARD_PIN_Y_BEGIN, true);
    while (true) {
        // for(int8_t i = 0; i < NUM_OF_LEDS/3; i++) {
        //     put_pixel(rgb_u32(255, 0, 0), pio, sm);
        //     put_pixel(rgb_u32(0, 255, 0), pio, sm);
        //     put_pixel(rgb_u32(0, 0, 255), pio, sm);
        // }
        if(gpio_get(KEYBOARD_PIN_X_BEGIN))
            put_pixel(rgb_u32(255, 0, 0), pio, sm);
        else
            put_pixel(rgb_u32(0, 0, 0), pio, sm);
        sleep_ms(10);

        hidRun(gpio_get(KEYBOARD_PIN_X_BEGIN));
        // reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
    }
}
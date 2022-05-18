#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "config.h"

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t rgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b);
}



int main() {
    stdio_init_all();
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
    int t = 0;
    while (true) {
        for(int8_t i = 0; i < NUM_OF_LEDS/3; i++) {
            put_pixel(rgb_u32(255, 0, 0));
            put_pixel(rgb_u32(0, 255, 0));
            put_pixel(rgb_u32(0, 0, 255));
        }
        put_pixel(rgb_u32(255, 0, 0));
        sleep_ms(100);
        // reset_usb_boot(0,0); // allows us to reboot the pico in to the bootloader mode
    }
}
#include "wsLED.h"
#include "config.h"
#include "ws2812.pio.h"

void put_pixel(uint32_t pixel_grb, PIO pio, uint8_t sm) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

uint32_t rgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b);
}

void initPio(PIO pio, uint sm, int systemClock){
    // Add PIO program to PIO instruction memory. SDK will find location and
    // return with the memory offset of the program.
    uint offset = pio_add_program(pio, &WS_LED_program);
    
    // Initialize the program using the helper function in our .pio file
    ws_program_init(pio, sm, offset, WS2812_PIN, WS2812_frequency, WS2812_WHITE, systemClock);
}
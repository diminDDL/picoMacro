#include "wsLED.h"
void put_pixel(uint32_t pixel_grb, PIO pio, uint8_t sm) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

uint32_t rgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b);
}
#include "pico/stdlib.h"
#include "hardware/pio.h"
void put_pixel(uint32_t pixel_grb, PIO pio, uint8_t sm);
uint32_t rgb_u32(uint8_t r, uint8_t g, uint8_t b);
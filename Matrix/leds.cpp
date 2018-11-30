#include "leds.h"

LEDs::LEDs (uint16_t num_pixels, uint16_t bright) {
  _num_pixels = num_pixels; 
  _brightness = bright;
}

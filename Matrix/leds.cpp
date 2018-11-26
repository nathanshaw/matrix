
#include "leds.h"

#ifdef NEOPIXEL_STRIPS
#include "Configuration.h"
// #include "Adafruit_NeoPixel.h"

#include "pins.h"
extern const int neo_pins[];

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel strip, byte WheelPos) {
  uint32_t color = 0;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    color = strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    return color;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    color = strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    return color;
  }
  WheelPos -= 170;
  color = strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  return color;
}


// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipeBright(Adafruit_NeoPixel strip, uint8_t c, uint8_t bright, uint8_t wait) {
  strip.setBrightness(bright);
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(strip, c));
    strip.show();
    delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel strip, uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, (i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel strip, uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip, ((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel strip, uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel strip, uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel(strip, (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

#ifdef SYSTEM_LED_FEEDBACK
    extern Adafruit_NeoPixel sys_led_strip;
#endif

void setupNeoPixels() {
  #ifdef SYSTEM_LED_FEEDBACK
    sys_led_strip = Adafruit_NeoPixel(SYSTEM_LED_NUM, neo_pins[SYSTEM_LED_FEEDBACK], NEO_RGB + NEO_KHZ800);
    sys_led_strip.begin();
    colorWipe(SYSTEM_LED_FEEDBACK, Wheel(sys_led_strip, 100), 0);
    Serial.print("Setup system led feedback neopixel strip to #");
    Serial.println(SYSTEM_LED_FEEDBACK);
  #endif
}
/*
Adafruit_NeoPixel* setupNeoPixels(uint8_t neo_pins[]) {
  for (int i = 0; i < NUM_NEOPIXEL_STRIPS; i++) {
    strips[i] = Adafruit_NeoPixel(20, neo_pins[i], NEO_RGB + NEO_KHZ800);
    strips[i].begin();
    // colorWipe(i, Wheel(100), 0);
    Serial.print("Setup strip #");
    Serial.println(i);
  }
  return strips;
}

void testNeoPixels(int wait) {
  Serial.println("----- Testing NeoPixels -----");
  for (uint8_t i = 0; i < NUM_NEOPIXEL_STRIPS; i++) {
    Serial.print("about to call rainbow on neostrip #");
    Serial.println(i);
    rainbow(i, wait);
    Serial.print("Finished rainbow for #");
    Serial.println(i);
  }
  Serial.println("---------- NeoPixel Test Complete ----------");
}
*/
#endif // NEOPIXEL_STRIPS

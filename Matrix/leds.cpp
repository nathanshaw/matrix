#ifdef NEOPIXELS
#include "Configuration.h"

public class NeoStrip() {
    // Input a value 0 to 255 to get a color value.
    // The colours are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos) {
      WheelPos = 255 - WheelPos;
      if (WheelPos < 85) {
        return strips[0].Color(255 - WheelPos * 3, 0, WheelPos * 3);
      }
      if (WheelPos < 170) {
        WheelPos -= 85;
        return strips[0].Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
      WheelPos -= 170;
      return strips[0].Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }

    // Fill the dots one after the other with a color
    void colorWipe(uint8_t idx, uint32_t c, uint8_t wait) {
      for (uint16_t i = 0; i < strips[idx].numPixels(); i++) {
        strips[idx].setPixelColor(i, c);
        strips[idx].show();
        delay(wait);
      }
    }

    // Fill the dots one after the other with a color
    void colorWipeBright(uint8_t idx, uint8_t c, uint8_t bright, uint8_t wait) {
      strips[idx].setBrightness(bright);
      for (uint16_t i = 0; i < strips[idx].numPixels(); i++) {
        strips[idx].setPixelColor(i, Wheel(c));
        strips[idx].show();
        delay(wait);
      }
    }

    void rainbow(uint8_t idx, uint8_t wait) {
      uint16_t i, j;

      for (j = 0; j < 256; j++) {
        for (i = 0; i < strips[idx].numPixels(); i++) {
          strips[idx].setPixelColor(i, Wheel((i + j) & 255));
        }
        strips[idx].show();
        delay(wait);
      }
    }

    // Slightly different, this makes the rainbow equally distributed throughout
    void rainbowCycle(uint8_t idx, uint8_t wait) {
      uint16_t i, j;

      for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        for (i = 0; i < strips[idx].numPixels(); i++) {
          strips[idx].setPixelColor(i, Wheel(((i * 256 / strips[idx].numPixels()) + j) & 255));
        }
        strips[idx].show();
        delay(wait);
      }
    }

    //Theatre-style crawling lights.
    void theaterChase(uint8_t idx, uint32_t c, uint8_t wait) {
      for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
          for (uint16_t i = 0; i < strips[idx].numPixels(); i = i + 3) {
            strips[idx].setPixelColor(i + q, c);  //turn every third pixel on
          }
          strips[idx].show();

          delay(wait);

          for (uint16_t i = 0; i < strips[idx].numPixels(); i = i + 3) {
            strips[idx].setPixelColor(i + q, 0);      //turn every third pixel off
          }
        }
      }
    }

    //Theatre-style crawling lights with rainbow effect
    void theaterChaseRainbow(uint8_t idx, uint8_t wait) {
      for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++) {
          for (uint16_t i = 0; i < strips[idx].numPixels(); i = i + 3) {
            strips[idx].setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
          }
          strips[idx].show();

          delay(wait);

          for (uint16_t i = 0; i < strips[idx].numPixels(); i = i + 3) {
            strips[idx].setPixelColor(i + q, 0);      //turn every third pixel off
          }
        }
      }
    }

    void setupNeoPixels() {
      for (int i = 0; i < NUM_NEOPIXEL_STRIPS; i++) {
        strips[i] = Adafruit_NeoPixel(20, neo_pins[i], NEO_RGB + NEO_KHZ800);
        strips[i].begin();
        colorWipe(i, Wheel(100), 0);
        Serial.print("Setup strip #");
        Serial.println(i);
      }
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
}
#endif // NEOPIXELS

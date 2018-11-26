#ifndef LEDS_H
  #define LEDS_H
  
  #ifdef NEOPIXELS
      #include <Adafruit_NeoPixel.h>
      
      #ifdef __AVR__
      #include <avr/power.h>
      #endif // __AVR__

      Adafruit_NeoPixel strips[NUM_NEOPIXEL_STRIPS];
     
      uint32_t Wheel(Adafruit_NeoPixel, byte){
        //uint32_t color = 0;
        //return color;
      };

      void colorWipe(Adafruit_NeoPixel, uint32_t, uint8_t);
      
      void colorWipeBright(Adafruit_NeoPixel, uint8_t, uint8_t, uint8_t);
      
      void setupNeoPixels();
      
      void testNeoPixels(int);

      /*
      class LedStrip:
        private:
          LedStrip(uint16_t, uint8_t);// number of pixels,
          uint32_t colors[];
          String pixel_func[];// what is the functionality of the pixel
          Adafruit_NeoPixel strip;
        public:
          getPColor(uint16_t);// which pixel
          getPBrightness(uint16_t);// which pixel
          getSBrightness(uint16_t);
          getStrip(Adafruit_NeoPixel);
      */
  #endif // NEOPIXELS

#endif // LEDS_H

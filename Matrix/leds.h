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
      
      void rainbow(Adafruit_NeoPixel, uint8_t);
      
      void rainbowCycle(Adafruit_NeoPixel, uint8_t);
      
      void theaterChase(Adafruit_NeoPixel, uint32_t, uint8_t);
      
      void theaterChaseRainbow(Adafruit_NeoPixel, uint8_t);
      
      void setupNeoPixels();
      
      void testNeoPixels(int);

  #endif // NEOPIXELS

#endif // LEDS_H

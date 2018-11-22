#ifndef LEDS_H
  #define LEDS_H
  
  #include "Configuration.h"
  
  #ifdef NEOPIXELS
  #include <Adafruit_NeoPixel.h>
  
  const uint8_t neo_pins[] = {A16, A17, A18}; // 35, 36, 37 // A16, A17, A18
  
  #ifdef __AVR__
  #include <avr/power.h>
  #endif // __AVR__
  
  class NeoStrip {
    private:
      uint32_t Wheel(byte);
      int _pin;
      int _num_pixels;
      Adafruit_NeoPixel strip;
   
    public:

      int getNumPixels();
    
      void colorWipe(uint8_t, uint32_t, uint8_t);
      
      void colorWipeBright(uint8_t, uint8_t, uint8_t, uint8_t);
      
      void rainbow(uint8_t, uint8_t);
      
      void rainbowCycle(uint8_t, uint8_t);
    
      void theaterChase(uint8_t, uint32_t, uint8_t);
      
      void theaterChaseRainbow(uint8_t, uint8_t);
      
      void setupNeoPixels();
      
      void testNeoPixels(int);
   };
  
  #endif // NEOPIXELS

#endif // LEDS_H

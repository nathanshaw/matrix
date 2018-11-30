#ifndef LEDS_H
  #define LEDS_H

 #include "actuator.h"

 class LEDs : public Actuator {
  
    public:
      LEDs(uint16_t, uint16_t);// num_pixels, brightness

      virtual void init() = 0;
      virtual void test() = 0;
      
      virtual void setBrightness(uint16_t) = 0;     
      uint16_t getBrightness() { return _brightness; };
     
      uint16_t getNumPixels() { return _num_pixels; };
      
    protected:
      uint16_t _brightness;
      uint16_t _num_pixels;
};

#endif // LEDS_H

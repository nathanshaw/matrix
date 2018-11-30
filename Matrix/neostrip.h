#ifndef NEOSTRIP_H
#define NEOSTRIP_H
#include <Adafruit_NeoPixel.h>
#include "pins.h"
#include "leds.h"
#ifdef __AVR__
#include <avr/power.h>
#endif // __AVR__

class NeoStrip : virtual public LEDs {

  public:
    NeoStrip( unsigned char, uint16_t, uint16_t );// pin#, number of pixels, brightness
    ~NeoStrip();

    void setColor(uint16_t, uint32_t);
    void setColor(uint32_t);
    uint32_t getColor(uint16_t);// which pixel

    uint16_t getBrightness();// which pixel
    void setBrightness(uint16_t);

    Adafruit_NeoPixel getStrip() {
      return _strip;
    };

    uint32_t Wheel(byte WheelPos);

    void on(uint16_t pixNum, uint32_t color);
    void allOn(uint32_t color, uint16_t bright);
    void allOn(uint32_t color);

    void off(uint16_t pixNum);
    void allOff();

    void init();
    void test();

  private:
    unsigned char _pin;
    uint32_t *_colors;

    // String _pixel_func[];// what is the functionality of the pixel
    Adafruit_NeoPixel _strip;// the adafruit neopixel strip object 
};

#endif

#include "neostrip.h"

extern const int neo_pins[];

// Constructors /////////////////////////////////////////////////////////////////////

NeoStrip::NeoStrip(unsigned char pin, uint16_t num_pixels, uint16_t bright) : LEDs (num_pixels, bright)
{
  _pin = pin;
  _colors = new uint32_t[_num_pixels];
  for (int i = 0; i < _num_pixels; i++) {
    _colors[i] = 50;
  }

  _brightness = 255;
  _strip = Adafruit_NeoPixel(getNumPixels(), _pin, NEO_RGB + NEO_KHZ800);
}

void NeoStrip::init ()
{
  _strip.setBrightness(_brightness);
  _strip.begin();
  _strip.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t NeoStrip::Wheel(byte WheelPos) {
  uint32_t _c = 0;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    _c = _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    return _c;
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    _c = _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    return _c;
  }
  WheelPos -= 170;
  _c = _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  return _c;
}

void NeoStrip::on(uint16_t num, uint32_t color) {
  setColor(num, color);
  _strip.setPixelColor(num, getColor(num));
  _strip.show();
}

void NeoStrip::allOn(uint32_t color, uint16_t bright) {
  for (int i = 0; i < getNumPixels(); i++) {
    setColor(i, color);
    _strip.setPixelColor(i, getColor(i));
  }
  _strip.setBrightness(bright);
  _strip.show();
}

void NeoStrip::allOn(uint32_t color ) {
  for (uint16_t i = 0; i < getNumPixels(); i++) {
    setColor(i, color);
    _strip.setPixelColor(i, getColor(i));
  }
  _strip.show();
}

void NeoStrip::off(uint16_t pixNum) {
  uint32_t _black = 0;
  setColor(_black);
}

void NeoStrip::allOff() {
  uint32_t _black = 0;
  setColor(_black);
  _strip.show();
}

void NeoStrip::setBrightness(uint16_t bright) {
  _brightness = bright;
  _strip.setBrightness(_brightness);
  _strip.show();
}

uint16_t NeoStrip::getBrightness()  {
  return _brightness;
}

void NeoStrip::setColor(uint32_t color) {
  for (int i = 0; i < _num_pixels; i++) {
    _colors[i] = color;
    _strip.setPixelColor(i, _colors[i]);
  }
  _strip.show();
}

void NeoStrip::setColor(uint16_t which, uint32_t color) {
  _colors[which] = color;
  _strip.setPixelColor(which, _colors[which]);
  _strip.show();
}

uint32_t NeoStrip::getColor(uint16_t which) {
  return _colors[which];
}

void NeoStrip::test() {
  for (int i = 0; i < 255; i++) {
    setColor(Wheel(i));
    delay(20);
  }
}

NeoStrip::~NeoStrip() {

}
/*
  void setupNeoPixels() {
  #ifdef SYSTEM_LED_FEEDBACK
    sys_led_strip = Adafruit_NeoPixel(SYSTEM_LED_NUM, neo_pins[SYSTEM_LED_FEEDBACK], NEO_RGB + NEO_KHZ800);
    sys_led_strip.begin();
    colorWipe(SYSTEM_LED_FEEDBACK, Wheel(sys_led_strip, 100), 0);
    Serial.print("Setup system led feedback neopixel strip to #");
    Serial.println(SYSTEM_LED_FEEDBACK);
  #endif
  }
*/

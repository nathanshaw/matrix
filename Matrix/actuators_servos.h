////////////////////////////////////////////
// RC Servos
////////////////////////////////////////////
#include <Servo.h>

#define NUM_SERVOS 4

const uint8_t ser_pins[] = {A6, A7, A8, A9}; // A6,A7,A8,A9 // 20, 21, 22, 23
int16_t ser_pos[] = {180, 180, 180, 180};

Servo servos[NUM_SERVOS];

void setupServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(ser_pins[i]);
  }
}

void testRCServos(uint8_t wait) {
  for (int i = 0; i < NUM_SERVOS; i++) {
    Serial.print("Testing RC Servo #");
    Serial.println(i);
    for (int pos = ser_pos[i]; pos < 180; pos++) {
      ser_pos[i] = pos;
      servos[i].write(ser_pos[i]);
      delay(wait);
    }
    for (int pos = ser_pos[i]; pos > 0; pos--) {
      ser_pos[i] = pos;
      servos[i].write(ser_pos[i]);
      delay(wait);
    }
  }
}

void testLewanServos(uint8_t wait) {
  delay(wait);
}

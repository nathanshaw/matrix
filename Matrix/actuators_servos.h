#ifndef ACTUATORS_SERVOS_H
#define ACTUATORS_SERVOS_H
////////////////////////////////////////////
// RC Servos
////////////////////////////////////////////
#ifdef NUM_SERVOS
  #include <Servo.h>

  const uint8_t ser_pins[] = {A6, A7, A8, A9}; // A6,A7,A8,A9 // 20, 21, 22, 23
  int16_t ser_pos[] = {180, 180, 180, 180};
  
  Servo servos[NUM_SERVOS];
  
  void setupServos();
  void testRCServos(uint8_t);  
  void testLewanServos(uint8_t);
  void testRobotServos();
#endif // NUM_SERVOS

#endif // ACTUATORS_SERVOS

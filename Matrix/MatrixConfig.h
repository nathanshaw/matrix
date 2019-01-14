#ifndef MATRIX_CONFIG_H
  #define MATRIX_CONFIG_H
 
  #include <Arduino.h>
  #include <stdint.h>
  #include "macros.h"
  #include "Configuration.h"
  #include "printing.h"
  #include "actuator.h"
  #include "sensor.h"
  
  #ifdef NEOPIXEL_STRIPS
    #include "neostrip.h"
  #endif
  #include "pololu_mc33926.h"
  
  #ifdef NUM_RC_SERVOS
    #include "actuators_servos.h"
  #endif

  #include "midi.h"
  
#endif // MATRIX_CONFIG_H

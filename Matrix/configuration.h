// pinout for the Beater-Board - v1.0 - v1.1
////////////////////////////////////////////
#define VERBOSE 1

////////////////////////////////////////////
// PCB Selection
////////////////////////////////////////////
// please uncomment the line corresponding to the PCB you are using
#define BEATER_BOARD
// #define HERMES
// #define HOMADOS
// #define BRIGID

////////////////////////////////////////////
// LEDS
////////////////////////////////////////////
#include <Arduino.h>
// #define ONBOARD_LED
#define NEOPIXEL_STRIPS 3
#define SYSTEM_LED_FEEDBACK 2
#define SYSTEM_LED_NUM 20
// #define ODRIVE_LED_FEEDBACK 1
// #define MIDI_LED_FEEDBACK 0
// #define MIRROR_ACTUATORS // for strip #1

// LED Feedback

////////////////////////////////////////////
// SOLENOIDS
////////////////////////////////////////////
// #define SOLENOIDS
// #define NUM_SOLENOIDS 4
// #define TEST_SOLENOIDS

////////////////////////////////////////////
// RC Servos
////////////////////////////////////////////
// #define NUM_RC_SERVOS 4
// #define TEST_RC_SERVOS

////////////////////////////////////////////
// Robot Servos
////////////////////////////////////////////
// #define ROBOT_SERVOS
// #define NUM_ROBOT_SERVO_BUSSES
// #define TEST_LEWAN_SOUL_SERVOS

///////////////////////////////////////////////////////////////////////////////
//////////////////// MOTORS ////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define DC_MOTORS
////////////////////////////////////////////
// ODrive motors
////////////////////////////////////////////
// #define ODRIVE_MOTORS
// #define TEST_ODRIVE_LOOP
// #define ODRIVE_SERIAL Serial5
// #define TEST_ODRIVE_INTERACTIVE
// #define NUM_ODRIVE_MOTORS
// #define SYSTEM_FEEDBACK 2//strip #2 will now be used for system feedback

////////////////////////////////////////////
// Pololu Motors
////////////////////////////////////////////
#define POLOLU_MC33926
#define POLOLU_MOTORS
// #define B1M1_TYPE ROTATION
// #define B1M1_TYPE INFINATE
#define POLOLU_BOARD_1
// #define POLOLU_BOARD_2
#define TEST_POLOLU_MOTORS

////////////////////////////////////////////
// MIDI
////////////////////////////////////////////
// beaterboard uses RX/TX 6 for the MIDI communication
// #define USB_MIDI
// #define HARDWARE_MIDI 
// #define MIDI_BUS Serial6 // for the beaeterbot shield

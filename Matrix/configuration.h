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
#define NEOPIXELS
#define NUM_NEOPIXEL_STRIPS 3
#define TEST_NEOPIXELS
#define MIRROR_ACTUATORS // for strip #1

////////////////////////////////////////////
// SOLENOIDS
////////////////////////////////////////////
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

////////////////////////////////////////////
// ODrive motors
////////////////////////////////////////////
// #define ODRIVE_MOTORS
// #define NUM_ODRIVE_MOTORS

////////////////////////////////////////////
// Pololu Motors
////////////////////////////////////////////
// #define B1M1_TYPE ROTATION
// #define B1M1_TYPE INFINATE
#define POLOLU_BOARD_1
// #define POLOLU_BOARD_2
// #define TEST_POLOLU_MOTORS


////////////////////////////////////////////
// MIDI
////////////////////////////////////////////
// beaterboard uses RX/TX 6 for the MIDI communication
#define USB_MIDI
// #define HARDWARE_MIDI 
// #define MIDI_BUS Serial6 // for the beaeterbot shield

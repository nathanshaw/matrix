/*
 * This firmware was developed by Nathan Villicana-Shaw
 * at the Victoria University of Wellington.
 * 
 * https://github.com/nathanshaw/matrix
 */

#include "MatrixConfig.h"

////////////////////////////////////////////
////////////////////////////////////////////
// Setup Loop
////////////////////////////////////////////
////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println("----- Started Serial -----");
  
  delay(300);
  #ifdef SOLENOID_NUM
    Serial.println("----- Started settting up Solenoids -----");
    setupSolenoids();
    Serial.println("----- Finished Setting Up Solenoids -----");
  #endif

  #ifdef NEOPIXELS
    Serial.println("----- Started settting up Neopixels -----");
    setupNeoPixels();
    colorWipeBright(0, 20, 50, 0);
    colorWipeBright(1, 20, 50, 0);
    colorWipeBright(2, 20, 50, 0);
    Serial.println("----- Finished Setting Up Neopixels -----"); 
  #endif
  
  #ifdef SERVOS
    Serial.println("----- Started Setting Up Servos -----");
    setupServos();
    Serial.println("----- Finished Setting Up Servos -----");
  #endif

  #ifdef USB_MIDI
    Serial.println("----- Started Setting Up USB MIDI -----");
    setupUSBMIDI();
    Serial.println("----- Finished Setting Up USB MIDI -----");
  #endif

  #ifdef HARDWARE_MIDI
    Serial.println("----- Started Setting Up Hardware MIDI -----");
    HW_MIDI.begin(MIDI_CHANNEL_OMNI); // what MIDI channels to listen to (OMNI selects all)
    Serial.println("----- Finished Setting Up Hardware MIDI -----");
  #endif

  #ifdef POLOLU_BOARD_1
    Serial.println("----- Started Setting Up POLOLU Motor driver #1 -----");
    md1.init();
    Serial.println("----- Finished Setting Up POLOLU Motor driver #1 -----");
  #endif // POLOLU_BOARD_1
  
  #ifdef POLOLU_BOARD_2
    Serial.println("----- Started Setting Up POLOLU Motor driver #2 -----");
    md2.init();
    Serial.println("----- Finished Setting Up POLOLU Motor driver #2 -----");  
  #endif // POLOLU_BOARD_2
  
  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
  Serial.println("------------- Finished setup loop -------------------");
  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
}
////////////////////////////////////////////
////////////////////////////////////////////
// Main Loop
////////////////////////////////////////////
////////////////////////////////////////////

void testRobotServos() {
  Serial.println("TODO TEST ROBOT SERVOS");
}

void loop() {
  #if defined(TEST_NEOPIXELS) & defined(NEOPIXELS) 
    testNeoPixels(20);
  #endif
  
  #if defined(TEST_SOLENOIDS) & defined(SOLENOIDS)
    testSolenoids(20);
  #endif
  
  #ifdef TEST_LEWAN_SOUL_SERVOS 
    testLewanServos(20);
  #endif

  #ifdef TEST_POLOLU_MOTORS
    testPololuMotors();
  #endif

  #ifdef TEST_RC_SERVOS
     testRCServos(4);
  #endif

  #ifdef TEST_ROBOT_SERVOS
    testRobotServos();
  #endif

  ///////////////////////////////////////////////////
  // Main loop functions
  ///////////////////////////////////////////////////
  #ifdef HARDWARE_MIDI
    listenForHardwareMIDI();
  #endif

  #ifdef USB_MIDI
    usbMIDI.read();
  #endif
}

/*
   This firmware was developed by Nathan Villicana-Shaw
   at the Victoria University of Wellington.

   https://github.com/nathanshaw/matrix
*/

#include "MatrixConfig.h"

#ifndef MAIN_H
#define MAIN_H

#ifdef SYSTEM_LED_FEEDBACK
Adafruit_NeoPixel sys_led_strip = Adafruit_NeoPixel(SYSTEM_LED_NUM, neo_pins[SYSTEM_LED_FEEDBACK], NEO_RGB + NEO_KHZ800);
#endif

////////////////////////////////////////////
////////////////////////////////////////////
// Setup Loop
////////////////////////////////////////////
////////////////////////////////////////////
void setup() {
  delay(300);
  Serial.begin(115200);
  Serial.println("----- Started Serial -----");

#ifdef NEOPIXEL_STRIPS
  Serial.println("----- Started setting up Neopixels -----");
#ifdef SYSTEM_LED_FEEDBACK
  sys_led_strip.begin();
  // colorWipeBright(sys_led_strip, 0xFF0055, 20, 50);
  Serial.println("Created a system led feedback strip");
#endif
  Serial.println("----- Finished Setting Up Neopixels -----");
#endif

#ifdef SOLENOID_NUM
  Serial.println("----- Started settting up Solenoids -----");
  setupSolenoids();
  Serial.println("----- Finished Setting Up Solenoids -----");
#endif

#ifdef SERVOS
  Serial.println("----- Started Setting Up Servos -----");
  setupServos();
  Serial.println("----- Finished Setting Up Servos -----");
#endif

#ifdef SYSTEM_LED_FEEDBACK
  //  colorWipeBright(sys_led_strip, 0xFFFF55, 50, 50);
#endif

#ifdef USB_MIDI
  Serial.println("----- Started Setting Up USB MIDI -----");
  MIDIBus midi_bus = MIDIBus("usb");
  Serial.println("----- Finished Setting Up USB MIDI -----");
#endif

#ifdef HARDWARE_MIDI
  Serial.println("----- Started Setting Up Hardware MIDI -----");
  // HW_MIDI.begin(MIDI_CHANNEL_OMNI); // what MIDI channels to listen to (OMNI selects all)
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

#ifdef ODRIVE_MOTORS
  setupODrive();
  runODriveCalibration(0);
  runODriveCalibration(1);
#endif // ODRIVE_MOTORS

#ifdef TEST_ODRIVE_INTERACTIVE
  Serial.println("Ready!");
  Serial.println("Send the character '0' or '1' to calibrate respective motor (you must do this before you can command movement)");
  Serial.println("Send the character 's' to exectue test move");
  Serial.println("Send the character 'b' to read bus voltage");
  Serial.println("Send the character 'p' to read motor positions in a 10s loop");
#endif // TEST_ODRIVE_INTERACTIVE
  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
  Serial.println("------------- Finished setup loop -------------------");
  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
#ifdef SYSTEM_LED_FEEDBACK
  colorWipeBright(sys_led_strip, 0x00FF55, 50, 50);
#endif
}
////////////////////////////////////////////
////////////////////////////////////////////
// Main Loop
////////////////////////////////////////////
////////////////////////////////////////////

void loop() {
#if defined(TEST_NEOPIXELS) & defined(NEOPIXEL_STRIPS)
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
  //usbMIDI.read();
#endif

#ifdef TEST_ODRIVE_LOOP
#ifdef SYSTEM_FEEDBACK
  //colorWipeBright(SYSTEM_FEEDBACK, 40, 50, 0);
#endif
  odriveTest();
#endif // TEST_ODRIVE_LOOP
}
#endif // MAIN_H

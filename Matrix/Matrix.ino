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
  
  delay(1000);
  #ifdef SOLENOID_NUM
    setupSolenoids();
  #endif

  #ifdef NEO_PIXELS
    setupNeoPixels();
  #endif
  
  #ifdef SERVOS
    setupServos();
  #endif
  
  delay(500);

  #ifdef HARDWARE_MIDI
    MIDI.begin(MIDI_CHANNEL_OMNI); // what MIDI channels to listen to (OMNI selects all)
    Serial.println("Began MIDI channel listening to all channels");
  #endif

  #ifdef POLOLU_MOTORS
    Serial.println("initializing the Dual MC33926MotorShield #1 ");
    md1.init();
    Serial.println("initializing the Dual MC33926MotorShield #2 ");
    md2.init();
  #endif
  
  Serial.println("Finished setup loop");
  Serial.println("------------------------------");
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
  #ifdef TEST_NEOPIXELS 
    testNeoPixels(20);
  #endif
  
  #ifdef TEST_SOLENOIDS
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

  #ifdef TEST_SOLENOIDS
    testSolenoids(100);
    digitalWrite(2, HIGH); 
    delay(100);
    digitalWrite(2, LOW);
    delay(200);
  #endif // TEST_SOLENOIDS 

  #ifdef TEST_ROBOT_SERVOS
    testRobotServos();
  #endif

  ///////////////////////////////////////////////////
  // Main loop functions
  ///////////////////////////////////////////////////
  #ifdef HARDWARE_MIDI
    listenForMIDI();
  #endif
}

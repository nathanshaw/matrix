////////////////////////////////////////////
////////////////////////////////////////////
// Setup Loop
////////////////////////////////////////////
////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  Serial.println("----- Started Serial -----");
  delay(1000);
  setupSolenoids();
  setupNeoPixels();
  setupServos();
  delay(1000);
  MIDI.begin(MIDI_CHANNEL_OMNI); // what MIDI channels to listen to (OMNI selects all)
  Serial.println("initializing the Dual MC33926MotorShield #1 ");
  md1.init();
  Serial.println("initializing the Dual MC33926MotorShield #2 ");
  md2.init();
  Serial.println("Finished setup loop");
  Serial.println("------------------------------");
}
////////////////////////////////////////////
////////////////////////////////////////////
// Main Loop
////////////////////////////////////////////
////////////////////////////////////////////

void testRobotServos() {
  
}

void loop() {
  #ifndef NEOPIXEL_TEST 
    testNeoPixels(20);
  #endif
  
  // testPololuMotors();
  // testRCServos(4);
  /*
  testSolenoids(100);
  digitalWrite(2, HIGH); 
  delay(100);
  digitalWrite(2, LOW);
  delay(200);
  */
  // listenForMIDI();
  testRobotServos();
}

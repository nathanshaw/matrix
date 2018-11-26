#include "actuators_motors.h"
#include "Configuration.h"
#include <ODriveArduino.h>

extern DualMC33926MotorShield md1;
extern DualMC33926MotorShield md2;

// Printing with stream operator
template<class T> inline Print& operator <<(Print &obj,     T arg) {
  obj.print(arg);
  return obj;
}
template<>        inline Print& operator <<(Print &obj, float arg) {
  obj.print(arg, 4);
  return obj;
}

extern ODriveArduino odrive;

////////////////////////////////////////////
// ODrive Motors
////////////////////////////////////////////

void setupODrive() {
  ODRIVE_SERIAL.begin(115200);

  // In this example we set the same parameters to both motors.
  // You can of course set them different if you want.
  // See the documentation or play around in odrivetool to see the available parameters
  for (int axis = 0; axis < 2; ++axis) {
    ODRIVE_SERIAL << "w axis" << axis << ".controller.config.vel_limit " << 22000.0f << '\n';
    ODRIVE_SERIAL << "w axis" << axis << ".motor.config.current_lim " << 11.0f << '\n';
    // This ends up writing something like "w axis0.motor.config.current_lim 10.0\n"
  }
  Serial.println("Began ODRIVE serial");
}

void runODriveCalibration(int motornum) {
  int requested_state;
  requested_state = ODriveArduino::AXIS_STATE_MOTOR_CALIBRATION;
  Serial << "Axis" << motornum << ": Requesting state " << requested_state << '\n';
  odrive.run_state(motornum, requested_state, true);

  requested_state = ODriveArduino::AXIS_STATE_ENCODER_OFFSET_CALIBRATION;
  Serial << "Axis" << motornum << ": Requesting state " << requested_state << '\n';
  odrive.run_state(motornum, requested_state, true);

  requested_state = ODriveArduino::AXIS_STATE_CLOSED_LOOP_CONTROL;
  Serial << "Axis" << motornum << ": Requesting state " << requested_state << '\n';
  odrive.run_state(motornum, requested_state, false); // don't wait
  Serial.println("Finished Calibration");
}

void runODriveSinTest() {
  Serial.println("Executing test move");
  for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
    float pos_m0 = 20000.0f * cos(ph);
    float pos_m1 = 20000.0f * sin(ph);
    odrive.SetPosition(0, pos_m0);
    odrive.SetPosition(1, pos_m1);
    delay(5);
  }
  Serial.println("Finished Test Move");
}

void odriveInteractiveTestLoop() {
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print("Read in a character : ");
    Serial.println(c);
    // Run calibration sequence
    if (c == '0' || c == '1') {
      runODriveCalibration(c);
    }

    // Sinusoidal test move
    if (c == 's') {
      runODriveSinTest();
    }

    // Read bus voltage
    if (c == 'b') {
      Serial5 << "r vbus_voltage\n";
      Serial << "Vbus voltage: " << odrive.readFloat() << '\n';
    }

    // print motor positions in a 10s loop
    if (c == 'p') {
      static const unsigned long duration = 10000;
      unsigned long start = millis();
      while (millis() - start < duration) {
        for (int motor = 0; motor < 2; ++motor) {
          Serial5 << "r axis" << motor << ".encoder.pos_estimate\n";
          Serial << odrive.readFloat() << '\t';
        }
        Serial << '\n';
      }
    }
  }
}

void odriveTest() {
  Serial.println("Executing test move");
  for (float ph = 0.0f; ph < 6.28318530718f; ph += 0.01f) {
    float pos_m0 = 20000.0f * cos(ph);
    float pos_m1 = 20000.0f * sin(ph);
    odrive.SetPosition(0, pos_m0);
    odrive.SetPosition(1, pos_m1);
    delay(5);
  }
  Serial.println("Finished Test Move");
  Serial5 << "r vbus_voltage\n";
  Serial << "Vbus voltage: " << odrive.readFloat() << '\n';
  static const unsigned long duration = 5000;
  unsigned long start = millis();
  while (millis() - start < duration) {
    for (int motor = 0; motor < 2; ++motor) {
      Serial5 << "r axis" << motor << ".encoder.pos_estimate\n";
      Serial << odrive.readFloat() << '\t';
    }
    Serial << '\n';
  }
}

////////////////////////////////////////////
// Brushed Motor Functions
////////////////////////////////////////////

void stopIfFault()
{
#ifdef POLOLU_BOARD_1
  if (md1.getFault())
  {
    Serial.println("MD1 fault");
    while (1);
  }
#endif // POLOLU_BOARD_1
#ifdef POLOLU_BOARD_2
  if (md2.getFault())
  {
    Serial.println("MD2 fault");
    while (1);
  }
#endif // POLOLU_BOARD_2
}

////////////////////////////////////////////
// Test Functions
////////////////////////////////////////////
void testPololuMotors() {

#ifdef POLOLU_BOARD_1
  Serial.println("TESTING POLOLU MOTORS");
  for (int i = 0; i <= 400; i++)
  {
    md1.setM1Speed(i);
    stopIfFault();
    if (abs(i) % 20 == 10)
    {
      Serial.print("MD1 m1 current: ");
      Serial.println(md1.getM1CurrentMilliamps());
    }
    delay(2);
  }
  for (int i = 0; i <= 400; i++)
  {
    md1.setM2Speed(i);
    stopIfFault();
    if (abs(i) % 20 == 10)
    {
      Serial.print("MD1 m2 current: ");
      Serial.println(md1.getM2CurrentMilliamps());
    }
    delay(2);
  }
#endif // POLOLU_BOARD_1
  /////////////////////////////////////////////////////////////
  ////////////////// SECOND SET OF MOTORS /////////////////////
  /////////////////////////////////////////////////////////////
#ifdef POLOLU_BOARD_2
  for (int i = 0; i <= 400; i++)
  {
    md2.setM1Speed(i);
    stopIfFault();
    if (abs(i) % 200 == 100)
    {
      Serial.print("MD2 m1 current: ");
      Serial.println(md2.getM1CurrentMilliamps());
    }
    delay(2);
  }
  for (int i = 0; i <= 400; i++)
  {
    md2.setM2Speed(i);
    stopIfFault();
    if (abs(i) % 200 == 100)
    {
      Serial.print("MD2 m2 current: ");
      Serial.println(md2.getM2CurrentMilliamps());
    }
    delay(2);
  }
#endif // POLOLU_BOARD_2
}

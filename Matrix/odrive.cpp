#include "motor.h"
#include "Configuration.h"
#include <ODriveArduino.h>

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

#ifdef ODRIVE_SERIAL
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

#endif // ODRIVE_SERIAL

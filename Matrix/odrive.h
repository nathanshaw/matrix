#ifndef ODRIVE_H
#define ODRIVE_H

#include <Arduino.h>
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


class ODrive {
  public:
    ODriveArduino odrive(ODRIVE_SERIAL);
    void setupODrive();
    void runODriveSinTest();
    void runODriveCalibration(int);
    void odriveInteractiveTestLoop();
    void odriveTest();
  private:
    

    // ODrive object

};

#endif

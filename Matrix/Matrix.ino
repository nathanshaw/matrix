/*
   This firmware was developed by Nathan Villicana-Shaw
   at the Victoria University of Wellington.

   https://github.com/nathanshaw/matrix
*/

#include "MatrixConfig.h"
#include "configuration.h"
#include <MIDI.h>

#ifdef SYSTEM_LED_FEEDBACK
NeoStrip sys_strip = NeoStrip(neo_pins[2], SYSTEM_LED_NUM, 0xFF00);
#endif

#ifdef USB_MIDI
MIDIBus midi_bus = MIDIBus("usb");
#endif

#ifdef HARDWARE_MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, MIDI_BUS, hw_midi);
#endif

#include <i2c_t3.h>
uint8_t slave_addr = 0x90;

// Memory
#define MEM_LEN 256
char databuf[MEM_LEN];
int count;


unsigned long _timer = 0;
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
  sys_strip.init();
  sys_strip.allOn(0xFF0055, 20);
  Serial.println("Created a system led feedback strip");
#endif
  Serial.println("----- Finished Setting Up Neopixels -----");
#endif

#ifdef SOLENOID_NUM
  Serial.println("----- Started settting up Solenoids -----");
#ifdef ONBOARD_SOLENOIDS
  setupSolenoids();
#endif
  // Data init
  memset(databuf, 0, sizeof(databuf));
  count = 0;
  Serial.println("----- Finished Setting Up Solenoids -----");
#endif

#ifdef NUM_RC_SERVOS
  Serial.println("----- Started Setting Up RC Servos -----");
  setupRCServos();
  Serial.println("----- Finished Setting Up RC Servos -----");
#endif

#ifdef SYSTEM_LED_FEEDBACK
  sys_strip.allOn(0xFFFF55, 50);
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

#ifdef USB_MIDI
  midi_bus.begin();
  Serial.println("----- Set Up USB MIDI before setup loop-----");
#endif

#ifdef HARDWARE_MIDI
  Serial.println("----- Started Setting Up Hardware MIDI -----");
  hw_midi.begin(MIDI_CHANNEL_OMNI); // what MIDI channels to listen to (OMNI selects all)
  Serial.println("----- Finished Setting Up Hardware MIDI -----");
#endif

#ifdef TEST_ODRIVE_INTERACTIVE
  Serial.println("Ready!");
  Serial.println("Send the character '0' or '1' to calibrate respective motor (you must do this before you can command movement)");
  Serial.println("Send the character 's' to exectue test move");
  Serial.println("Send the character 'b' to read bus voltage");
  Serial.println("Send the character 'p' to read motor positions in a 10s loop");
#endif // TEST_ODRIVE_INTERACTIVE
#ifdef SYSTEM_LED_FEEDBACK
  delay(100);
  sys_strip.allOn(0x44, 50);
#endif

  // I2C
  Serial.println("setting up I2C master");
  // Setup for Master mode, pins 18/19, external pullups, 400kHz, 200ms default timeout
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
  Wire.setDefaultTimeout(200000); // 200ms
  Serial.println("I2C master is set up");


  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
  Serial.print("------------- ");
  Serial.print("V 0.1");
  Serial.println(" -------------------");
  Serial.println("|||||||||||||||||||||||||||||||||||||||||||||||||||||");
}

void loop() {
  // Serial.println("loop");
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
  vprintln("testing pololu motors");
  testPololuMotors();
#endif

#ifdef TEST_RC_SERVOS
  vprintln("Testing RC Servos");
  testRCServos(NUM_RC_SERVOS);
#endif

#ifdef TEST_ROBOT_SERVOS
  testRobotServos();
#endif

  ///////////////////////////////////////////////////
  // Main loop functions
  ///////////////////////////////////////////////////
#ifdef HARDWARE_MIDI
  readHWMidi();
#endif

#ifdef USB_MIDI
  Serial.print("reading USB MIDI : ");
  // String _t = midi_bus.getType();
  //Serial.println(_t);
  midi_bus.read();
#endif

#ifdef TEST_ODRIVE_LOOP
#ifdef SYSTEM_FEEDBACK
  colorWipeBright(SYSTEM_FEEDBACK, 40, 50, 0);
#endif
  odriveTest();
#endif // TEST_ODRIVE_LOOP
}

void matrixNoteOn(byte channel, byte note, byte velocity) {
  // for now the note on will turn on strip = channel to color = note at brightness = velocity
  // Serial.println("Entered into matrixNoteOn()");
#ifdef NEOPIXELS
  colorWipeBright(MIDI_LED_FEEDBACK, note, velocity, 0);
#endif // NEOPIXELS

  // if it is channel 1 it is for the motors
  // note 0 ==
#ifdef POLOLU_MOTORS
  // extern DualMC33926MotorShield md1;
  int v = velocity * 3;
  if (channel == 1) {
    if (note == 0) {
      md1.setM1Speed(v);
      vprint("Turned on md1 Motor 1 at velocity ");
      vprintln(v);
    } else if (note == 1) {
      v = v * -1;
      md1.setM1Speed(v);
      vprint("Turned on md1 Motor 1 at velocity ");
      vprintln(v);
    } else if (note == 2) {
      md1.setM2Speed(v);
      vprint("Turned on md1 Motor 2 at velocity ");
      vprintln(v);
    } else if (note == 3) {
      v = v * -1;
      md1.setM2Speed(v);
      vprint("Turned on md1 Motor 2 at velocity ");
      vprintln(v);
    }

    else if (note == 4) {
      md2.setM1Speed(v);
      vprint("Turned on md2 Motor 1 at velocity ");
      vprintln(v);
    }
    else if (note == 5) {
      v = v * -1;
      md2.setM1Speed(v);
      vprint("Turned on md2 Motor 1 at velocity ");
      vprintln(v);
    }
    else if (note == 6) {
      md2.setM2Speed(v);
      vprint("Turned on md2 Motor 2 at velocity ");
      vprintln(v);
    }
    else if (note == 7) {
      v = v * -1;
      md2.setM2Speed(v);
      vprint("Turned on md2 Motor 2 at velocity ");
      vprintln(v);
    }
    else {
      vprintln(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + v, 0);
      vprintln("WARNING!!! NO MAPPING FOR THAT NOTE PLEASE TRY MIDI NOTES 1-7");
    }
  }
#endif // POLOLU_MOTORS

  // if it is channel 2 then it is for the dampeners (velocity corresponds to dampening amount)
#ifdef NUM_RC_SERVOS
  if (channel == 2) {
    if (note < NUM_RC_SERVOS) {
      servos[note].write(velocity);
    } else {
      Serial.print("WARNING!!! the note you are sending is not mapped to a servo, please try a note lower than MIDI ");
      Serial.println(NUM_RC_SERVOS);
    }
  }
#endif

  // Solenoids
#ifdef NUM_SOLENOIDS
  if (channel == 3) {
    if (note < NUM_SOLENOIDS) {
      // TODO right noe we are assuming that we are going to use a Brigid or Homados board for the solenoids, via I2C
      Wire.beginTransmission(slave_addr);
      Wire.write(databuf, strlen(databuf)+1);
      Wire.endTransmission();

      if (Wire.getError()) {
        Serial.print("I2C ERROR!!!");
        Serial.println(Wire.getError());
      } else {
        Serial.print("sent I2C message to aux solenoid board ");
        Serial.println(slave_addr);
      }

    } else {
      Serial.print("WARNING!!! The note ");
      Serial.print(note);
      Serial.println(" is not mapped to a solenoid");
      Serial.print("Please try a note number less than ");
      Serial.println(NUM_SOLENOIDS);
    }

  }
#endif // NUM_SOLENOIDS
}

void matrixNoteOff(byte channel, byte note, byte velocity)  {
  // will now just turn off the LEDs

#ifdef NEOPIXELS
  colorWipeBright(channel, 0, 0, 0);
#endif // NEOPIXELS

#ifdef POLOLU_MOTORS
  if (channel == 1) {
    if (note < 2) {
      md1.setM1Speed(0);
    } else if (note < 4) {
      md1.setM2Speed(0);
    } else if (note < 6) {
      md2.setM1Speed(0);
    } else if ( note < 8) {
      md2.setM2Speed(0);
    }
  }

#endif // POLOLU_MOTORS
}

void readHWMidi() {
  // Serial.print(".");
  int note, velocity, channel, d1, d2;
  if (hw_midi.read()) {                    // Is there a MIDI message incoming ?
    byte type = hw_midi.getType();
    switch (type) {
      case midi::NoteOn:
        note = hw_midi.getData1();
        velocity = hw_midi.getData2();
        channel = hw_midi.getChannel();

        if (velocity > 0) {
          vprintln(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity, 1);
        } else {
          vprintln(String("Note Off: ch=") + channel + ", note=" + note, 1);
        }
#ifdef MIRROR_ACTUATORS
        matrixNoteOn(channel, note, velocity);
#endif // MIRROR_ACTUATORS
        break;
      case midi::NoteOff:
        note = hw_midi.getData1();
        velocity = hw_midi.getData2();
        channel = hw_midi.getChannel();
        vprintln(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity, 1);
#ifdef MIRROR_ACTUATORS
        matrixNoteOff(channel, note, velocity);
#endif // MIRROR_ACTUATORS 
        break;
      default:
        d1 = hw_midi.getData1();
        d2 = hw_midi.getData2();
        vprintln(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
    _timer = millis();
  }
  if (millis() - _timer > 5000) {
    _timer += 5000;
    vprintln("(hardware MIDI inactivity)");
  }
}

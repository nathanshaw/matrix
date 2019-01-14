/*
#include "midi.h"
#include "pololu_mc33926.h"
#include "actuators_servos.h"

/////////////////////////////////////////////////////
// MIRROR_ACTUATOR
/////////////////////////////////////////////////////

void matrixNoteOn(byte channel, byte note, byte velocity) {
  // for now the note on will turn on strip = channel to color = note at brightness = velocity
  Serial.println("Entered into matrixNoteOn()");
#ifdef NEOPIXELS
  colorWipeBright(channel, note, velocity, 0);
#endif // NEOPIXELS

  // if it is channel 1 it is for the motors
#ifdef POLOLU_MOTORS
  // extern DualMC33926MotorShield md1;
  if (channel == 0) {
    md1.setM1Speed(velocity);
    vprint("Turned on md1 Motor 1 at velocity ");
    vprintln(velocity);
  }
#endif // POLOLU_MOTORS

  // if it is channel 2 then it is for the dampeners (velocity corresponds to dampening amount)
#ifdef NUM_RC_SERVOS
  if (channel == 1) {
    servos[0].write(velocity);
  }
#endif
}

void matrixNoteOff(byte channel, byte note, byte velocity)  {
  // will now just turn off the LEDs

#ifdef NEOPIXELS
  colorWipeBright(channel, 0, 0, 0);
#endif // NEOPIXELS

#ifdef POLOLU_MOTORS
  md1.setM1Speed(0);
  vprintln("Turned off md1 Motor 1");
#endif // POLOLU_MOTORS
}

MIDIBus::MIDIBus(String type) {
  _type = type;
  if (_type == "usb" || _type == "USB") {
    // setup the handlers
    // vprintln("Created USB MIDI Bus");

  } else if (type == "hw" || type == "HW") {
    // vprintln("TODO HW BUS CODE IS COMMENTED OUT");
  } else {
    // Serial.println("ERROR WHEN CREATING MIDI BUS: please specify a type of USB or HW");
  }
}

void MIDIBus::begin() {
#ifdef MIRROR_ACTUATORS
  usbMIDI.setHandleNoteOff(matrixNoteOff);
  usbMIDI.setHandleNoteOn(matrixNoteOn);
#endif
}

void MIDIBus::setType(String type) {
  _type = type;
}

String MIDIBus::getType() {
  return "usb";
}

MIDI_CREATE_INSTANCE(HardwareSerial, hw_midi, hw_midi);

void MIDIBus::read() {
  _type = "usb";
  // Serial.println("Entered into MIDIBus.read()");
  // Serial.println(_type);
  // extern String _type; // TODO THIS IS A DANGEROUS  HACK
  if (_type == "usb" || _type == "USB") {
    Serial.println("reading from USB MIDI");
    usbMIDI.read();
  }
  else if (_type == "HW" || _type == "hw" ) {
    // Serial.println("LISTENING FOR HARDWARE MIDI MESSAGES");
    int note, velocity, channel, d1, d2;
    if (hw_midi.read()) {                    // Is there a MIDI message incoming ?
      byte type = hw_midi.getType();
      switch (type) {
        case midi::NoteOn:
          note = hw_midi.getData1();
          velocity = hw_midi.getData2();
          channel = hw_midi.getChannel();
          if (velocity > 0) {
            vprintln(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          } else {
            vprintln(String("Note Off: ch=") + channel + ", note=" + note);
          }
#ifdef MIRROR_ACTUATORS
          matrixNoteOn(channel, note, velocity);
#endif // MIRROR_ACTUATORS
          break;
        case midi::NoteOff:
          note = hw_midi.getData1();
          velocity = hw_midi.getData2();
          channel = hw_midi.getChannel();
          vprintln(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
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
    if (millis() - _timer > 10000) {
      _timer += 10000;
      vprintln("(hardware MIDI inactivity)");
    }
  }
  // Serial.println("Leaving MIDIBus.read()");
}
*/

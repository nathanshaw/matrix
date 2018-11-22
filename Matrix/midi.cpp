#include "midi.h"

/////////////////////////////////////////////////////
// MIRROR_ACTUATOR
/////////////////////////////////////////////////////
#ifdef MIRROR_ACTUATOR
void matrixNoteOn(byte channel, byte note, byte velocity) {
  // for now the note on will turn on strip = channel to color = note at brightness = velocity
  
  #ifdef NEOPIXELS
    // colorWipeBright(channel, note, velocity, 0);  
  #endif // NEOPIXELS

  #ifdef POLOLU_MOTORS
    md1.setM1Speed(velocity);
    vprint("Turned on md1 Motor 1 at velocity ");
    vprintln(velocity);
  #endif // POLOLU_MOTORS
}

void matrixNoteOff(byte channel, byte note, byte velocity)  {
  // will now just turn off the LEDs
  
  #ifdef NEOPIXELS
    // colorWipeBright(channel, 0, 0, 0);  
  #endif // NEOPIXELS
  
  #ifdef POLOLU_MOTORS
    md1.setM1Speed(0);
    vprintln("Turned off md1 Motor 1");
  #endif // POLOLU_MOTORS
}
#endif // MIRROR_ACTUATORS

/////////////////////////////////////////////////////
// HARDWARE MIDI
/////////////////////////////////////////////////////
#ifdef HARDWARE_MIDI 
  void listenForHardwareMIDI() {
    // Serial.println("LISTENING FOR HARDWARE MIDI MESSAGES");
    int note, velocity, channel, d1, d2;
    if (HW_MIDI.read()) {                    // Is there a MIDI message incoming ?
      byte type = HW_MIDI.getType();
      switch (type) {
        case midi::NoteOn:
          note = HW_MIDI.getData1();
          velocity = HW_MIDI.getData2();
          channel = HW_MIDI.getChannel();
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
          note = HW_MIDI.getData1();
          velocity = HW_MIDI.getData2();
          channel = HW_MIDI.getChannel();
          vprintln(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          #ifdef MIRROR_ACTUATORS
            matrixNoteOff(channel, note, velocity);
          #endif // MIRROR_ACTUATORS 
          break;
        default:
          d1 = HW_MIDI.getData1();
          d2 = HW_MIDI.getData2();
          vprintln(String("Message, type=") + type + ", data = " + d1 + " " + d2);
      }
      t = millis();
    }
    if (millis() - t > 10000) {
      t += 10000;
      vprintln("(hardware MIDI inactivity)");
    }
  }

#endif // HARDWARE_MIDI

/////////////////////////////////////////////////////
// USB MIDI
/////////////////////////////////////////////////////
#ifdef USB_MIDI
void setupUSBMIDI() {
  // setup the handlers
  usbMIDI.setHandleNoteOff(matrixNoteOff);
  usbMIDI.setHandleNoteOn(matrixNoteOn);
}
#endif // USB_MIDI

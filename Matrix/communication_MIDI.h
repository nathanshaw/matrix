//////////////////////////////////////////////
// MIDI Section
//////////////////////////////////////////////
#include <MIDI.h>
#include "leds.h"

MIDI_CREATE_INSTANCE(HardwareSerial, Serial6, MIDI);

unsigned long t=0;

void listenForHardwareMIDI() {
  int note, velocity, channel, d1, d2;
  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    Serial.println("INIc MIDI MESSAGE DETECTED");
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        } else {
          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case midi::NoteOff:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
      default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
        Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
    t = millis();
  }
  if (millis() - t > 10000) {
    t += 10000;
    Serial.println("(inactivity)");
  }
}

#ifdef USB_MIDI
/////////////////////////////////////////////////////
// USB MIDI
/////////////////////////////////////////////////////
void matrixNoteOn(byte channel, byte note, byte velocity) {
  // for now the note on will turn on strip = channel to color = note at brightness = velocity
  vprint("NOTE ON : ");
  vprint(channel);
  vprint(" - ");
  vprint(note);
  vprint(" - ");
  vprintln(velocity);
  
  #ifdef NEOPIXELS
    colorWipeBright(channel, note, velocity, 0);  
  #endif // NEOPIXELS

  #ifdef POLOLU_MOTORS
    md1.setM1Speed(velocity);
    vprint("Turned on md1 Motor 1 at velocity ");
    vprintln(velocity);
  #endif // POLOLU_MOTORS
}

void matrixNoteOff(byte channel, byte note, byte velocity)  {
  // will now just turn off the LEDs
  vprint("NOTE OFF : ");
  vprint(channel);
  vprint(" - ");
  vprint(note);
  vprint(" - ");
  vprintln(velocity);
  
  #ifdef NEOPIXELS
    colorWipeBright(channel, 0, 0, 0);  
  #endif // NEOPIXELS
  
  #ifdef POLOLU_MOTORS
    md1.setM1Speed(0);
    vprintln("Turned off md1 Motor 1");
  #endif // POLOLU_MOTORS
}

void setupUSBMIDI() {
  // setup the handlers
  usbMIDI.setHandleNoteOff(matrixNoteOff);
  usbMIDI.setHandleNoteOn(matrixNoteOn);
}
#endif // USB_MIDI

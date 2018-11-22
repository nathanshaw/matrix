//////////////////////////////////////////////
// MIDI Section
//////////////////////////////////////////////
#ifndef MIDI_H
#define MIDI_H

#include <MIDI.h>
#include "leds.h"
#include "printing.h"

#ifdef MIRROR_ACTUATORS
  void matrixNoteOn(byte, byte, byte );
  void matrixNoteOff(byte, byte, byte);
#endif // MIRROR_ACTUATORS

#ifdef HARDWARE_MIDI 
  MIDI_CREATE_INSTANCE(HardwareSerial, MIDI_BUS, HW_MIDI);
  unsigned long t=0;
  void listenForHardwareMIDI();
#endif // HARDWARE_MIDI

#ifdef USB_MIDI
  void setupUSBMIDI();
#endif // USB_MIDI

#endif // MIDI_H

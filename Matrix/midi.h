//////////////////////////////////////////////
// MIDI Section
//////////////////////////////////////////////
#ifndef MIDI_H
  #define MIDI_H
  // TODO
  /*
   * Instead perhaps I should have a MIDI class which is initalized as either a hardware_MIDI or a USB_MIDI 
   * 
   */
  #include <MIDI.h>
  #include <Arduino.h>
  #include "printing.h"

  class MIDIBus {
    public:
      MIDIBus(String type);
    private:
      String _type;
      unsigned long timer = 0;
  };
  
  #ifdef MIRROR_ACTUATORS
    void matrixNoteOn(byte, byte, byte );
    void matrixNoteOff(byte, byte, byte);
  #endif // MIRROR_ACTUATORS
  
  #ifdef HARDWARE_MIDI 
    void listenForHardwareMIDI();
  #endif // HARDWARE_MIDI

#endif // MIDI_H

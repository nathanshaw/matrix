#include "printing.h"

#include "Configuration.h"

// verbose printing (basic)
void vprint(String text) {
  // TODO update this to use *args and add return line at the end if possible like in python
  if (VERBOSE > 0) {
    Serial.print(text);
  }
}

// verbose printing (basic)
void vprint(int text) {
  // TODO update this to use *args and add return line at the end if possible like in python
  if (VERBOSE > 0) {
    Serial.print(text);
  }
}

// verbose printing basic return line
void vprintln(String text) {
  if (VERBOSE > 0) {
    Serial.println(text);
  }
}

// verbose printing basic return line
void vprintln(int text) {
  if (VERBOSE > 0) {
    Serial.println(text);
  }
}

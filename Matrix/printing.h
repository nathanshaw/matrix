#ifndef PRINTING_H
#define PRINTING_H

// verbose printing (basic)
void vprint(String text) {
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

#endif

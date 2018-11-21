#ifndef MACROS_H
#define MACROS_H

// Macros to support option testing
#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH_ENABLED_false 0
#define SWITCH_ENABLED_true  1
#define SWITCH_ENABLED_0     0
#define SWITCH_ENABLED_1     1
#define SWITCH_ENABLED_      1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

////////////////////////////////////////////
// Pololu Motors
////////////////////////////////////////////
#define ROTATION 1 // has a "max position" and a "min position"
#define INFINATE 2 // can rotate in either direction without any issues


#endif // MACROS_H

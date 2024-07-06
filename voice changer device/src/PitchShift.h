#ifndef PITCHSHIFT_H
#define PITCHSHIFT_H

#include <Arduino.h>

class PitchShift {
public:
    void begin();
    int16_t process(int16_t input);
private:
    // Add internal state variables here
};

#endif

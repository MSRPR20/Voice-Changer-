#ifndef PHASEVOCODER_H
#define PHASEVOCODER_H

#include <Arduino.h>

class PhaseVocoder {
public:
    PhaseVocoder();
    void begin(float sampleRate);
    void process(float* real, float* imag, float pitchShiftAmount);
private:
    float sampleRate;
    float* lastPhase;
};

#endif

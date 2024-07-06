#include "PhaseVocoder.h"
#include <math.h>

PhaseVocoder::PhaseVocoder() {
    
    sampleRate = 0.0;  
    lastPhase = nullptr;
}

void PhaseVocoder::begin(float sampleRateHz) {
    sampleRate = sampleRateHz;
    
    lastPhase = new float[256];  
    memset(lastPhase, 0, 256 * sizeof(float));  
}

void PhaseVocoder::process(float* real, float* imag, float pitchShiftAmount) {
   
    float freqPerBin = sampleRate / 256.0;  
    float pi = 3.14159265358979323846;
    float magn, phase, tmp, phaseShift;

    for (int i = 0; i < 256; i++) {
        magn = 2 * sqrt(real[i] * real[i] + imag[i] * imag[i]);  
        phase = atan2(imag[i], real[i]);  

        // Calculate phase shift
        phaseShift = (2.0 * pi * i / 256.0) * pitchShiftAmount;

        // Adjust phase
        tmp = phase + phaseShift - lastPhase[i];

        // Wrap phase to -pi to pi
        while (tmp > pi) tmp -= 2.0 * pi;
        while (tmp < -pi) tmp += 2.0 * pi;

        // Store last phase
        lastPhase[i] = phase + phaseShift;

        
        real[i] = magn * cos(tmp);
        imag[i] = magn * sin(tmp);
    }
}

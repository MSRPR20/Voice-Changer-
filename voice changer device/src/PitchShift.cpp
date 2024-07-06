#include "PitchShift.h"

PitchShift::PitchShift() {
  
    sampleRate = 0.0;  // Initialize sample rate

}

void PitchShift::begin(float sampleRateHz) {
    
    fft.begin(); 
    phaseVocoder.begin(sampleRateHz); 
}

int16_t PitchShift::process(int16_t input, float pitchShiftAmount) {
    
    fft.transform(input);

    phaseVocoder.process(fft.getReal(), fft.getImag(), pitchShiftAmount);

  
    fft.inverseTransform();

  
    return fft.getOutput();
}

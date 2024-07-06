#ifndef FFT_H
#define FFT_H

#include <Arduino.h>

class FFT {
public:
    FFT();
    void begin();
    void transform(int16_t input);
    void inverseTransform();
    float* getReal();
    float* getImag();
    int16_t getOutput();
private:

    int N;                      
    float* real;                
    float* imag;                
    float* spectrumReal;        
    float* spectrumImag;        
    float* outputBufferReal;    
    float* outputBufferImag;    
    float* windowFunction;      
    int windowLength;           
};

#endif

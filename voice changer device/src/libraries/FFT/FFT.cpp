#include "FFT.h"
#include <math.h>

FFT::FFT() {
    // Constructor initialization
    N = 256;  
    real = new float[N];
    imag = new float[N];
    spectrumReal = new float[N];
    spectrumImag = new float[N];
    outputBufferReal = new float[N];
    outputBufferImag = new float[N];

    windowLength = N;
    windowFunction = new float[N];
    for (int i = 0; i < N; i++) {
        windowFunction[i] = 0.5 * (1 - cos(2 * M_PI * i / (N - 1)));
    }
}

void FFT::begin() {
    // Initialization of FFT parameters

void FFT::transform(int16_t input) {
    // Implement FFT transformation

    // Apply windowing to input
    real[0] = input * windowFunction[0];
    imag[0] = 0.0;


    for (int i = 1; i < N; i++) {
        real[i] = 0.0;
        imag[i] = 0.0;
    }

    // Performing FFT
    int k = N / 2;
    for (int i = 0; i < log2(N); i++) {
        k /= 2;
        for (int j = 0; j < N; j++) {
            if ((j / k) % 2 == 1) {
                float temp_real = real[j];
                float temp_imag = imag[j];
                int theta = -2 * M_PI * j / N;
                real[j] = temp_real + real[j + k] * cos(theta) - imag[j + k] * sin(theta);
                imag[j] = temp_imag + real[j + k] * sin(theta) + imag[j + k] * cos(theta);
                real[j + k] = temp_real - real[j + k] * cos(theta) + imag[j + k] * sin(theta);
                imag[j + k] = temp_imag - real[j + k] * sin(theta) - imag[j + k] * cos(theta);
            }
        }
    }

    memcpy(spectrumReal, real, N * sizeof(float));
    memcpy(spectrumImag, imag, N * sizeof(float));
}

void FFT::inverseTransform() {
    int k = 1;
    for (int i = 0; i < log2(N); i++) {
        k *= 2;
        for (int j = 0; j < N; j++) {
            if ((j / k) % 2 == 1) {
                float temp_real = real[j];
                float temp_imag = imag[j];
                int theta = 2 * M_PI * j / N;
                real[j] = temp_real + real[j + k] * cos(theta) - imag[j + k] * sin(theta);
                imag[j] = temp_imag + real[j + k] * sin(theta) + imag[j + k] * cos(theta);
                real[j + k] = temp_real - real[j + k] * cos(theta) + imag[j + k] * sin(theta);
                imag[j + k] = temp_imag - real[j + k] * sin(theta) - imag[j + k] * cos(theta);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        outputBufferReal[i] = real[i] / N;
        outputBufferImag[i] = imag[i] / N;
    }
}

float* FFT::getReal() {
    
    return spectrumReal;
}

float* FFT::getImag() {
    
    return spectrumImag;
}

int16_t FFT::getOutput() {

    return static_cast<int16_t>(outputBufferReal[0]);
}

#include "PitchShift.h"
#include "Config.h"
#include <Arduino.h>

PitchShift pitchShifter;

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize pitch shifter
    pitchShifter.begin(16000.0);
}

void loop() {
    // Read audio input from analog pin A0
    int16_t audioInput = analogRead(A0);

    // Apply pitch shift effect 
    float pitchShiftAmount = 1.5; 
    int16_t outputAudio = pitchShifter.process(audioInput, pitchShiftAmount);

    analogWrite(9, outputAudio / 4);  

    delayMicroseconds(62); 
}

/** BEGIN_JUCE_MODULE_DECLARATION

    ID:             Doppler-Delay-Line
    vendor:         
    version:        0.0.1
    name:           
    description:    Interpolated delay line.
    website:        
    license:        

    dependencies:   

    END_JUCE_MODULE_DECLARATION
*/

#pragma once
#include "JuceHeader.h"

class DelayLine
{
public:
    DelayLine() {};

    DelayLine (unsigned int maxLengthSamples);

    void setup (unsigned int maxLengthSamples); // Create the buffer with 'maxLengthSamples' number of samples.

    void setFractionalSamples (double fractionalSamples); // Set the current delay length in a fractional number of samples.

    float process (float& input); // The process function, to be called once for ever sample.

private:
    juce::AudioBuffer<float> buffer;
    unsigned int maxBufferSampleLength;

    double fractionalSampleLength;

    int writePointer;
    double readPointer;

    float out = 0;
};

/*
  ==============================================================================

    DelayLine.h
    Created: 8 Feb 2021 1:54:49pm
    Author:  maxba

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class DelayLine
{
public:
    DelayLine();

    DelayLine(unsigned int maxLengthSamples);

    void setup(unsigned int maxLengthSamples);

    void setFractionalSamples(double fractionalSamples);

    // Process function, on every update
    float process(double input);

private:
    double* buffer;
    int maxBufferSampleLength;
    double fractionalSampleLength;

    int writePointer;
    double readPointer;
};

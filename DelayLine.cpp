/*
  ==============================================================================

    DelayLine.cpp
    Created: 8 Feb 2021 1:54:49pm
    Author:  maxba

  ==============================================================================
*/

#include "DelayLine.h"

DelayLine::DelayLine(unsigned int maxLengthSamples)
{
    setup (maxLengthSamples);
}

void DelayLine::setup (unsigned int maxLengthSamples)
{
    readPointer = 0;
    writePointer = 0;

    maxBufferSampleLength = maxLengthSamples;
    buffer = new double[maxBufferSampleLength];
}

void DelayLine::setFractionalSamples (double fractionalSamples)
{
    fractionalSampleLength = fractionalSamples;
}

void DelayLine::setFeedbackGain (double gain)
{
    feedbackGain = gain;
}

void DelayLine::setFilterCutoff (double cutoff)
{

}

float DelayLine::process (double input)
{
    buffer[writePointer] = input;

    readPointer = fmod (((writePointer)-fractionalSampleLength + maxBufferSampleLength), maxBufferSampleLength);

    // Indexes used for interpolation
    int i_1 = static_cast<int> (readPointer) - 1;
    if (i_1 < 0)
        i_1 += maxBufferSampleLength;


    int i0 = static_cast <int> (readPointer);


    int i1 = static_cast <int> (readPointer) + 1;
    if (i1 >= maxBufferSampleLength)
        i1 -= maxBufferSampleLength;


    int i2 = static_cast <int> (readPointer) + 2;
    if (i2 >= maxBufferSampleLength)
        i2 -= maxBufferSampleLength;


    // Fractional indexes used for reading within the buffer
    double buffer_1 = buffer[i_1];
    double buffer0 = buffer[i0];
    double buffer1 = buffer[i1];
    double buffer2 = buffer[i2];

    float f1 = readPointer - i0;
    float f0 = 1 - f1;

    double c3 = -buffer_1 + buffer0 - buffer1 + buffer2;
    double c2 = buffer_1 - buffer0 - c3;
    double c1 = buffer1 - buffer_1;

    double d0 = c3 * pow (f1, 3) + c2 * pow (f1, 2) + c1 * f1 + buffer0;

    ++writePointer;
    if (writePointer == maxBufferSampleLength)
        writePointer = 0;

    return d0;
}
#pragma once
#include "fastmath.h"

// taken from Lowpass filter at https://www.musicdsp.org/en/latest/Filters/180-cool-sounding-lowpass-with-decibel-measured-resonance.html

class lpf
{
public:
void Init(float sample_rate)
{
    x1 = 0.0f;
    x2 = 0.0f;
    y1 = 0.0f;
    y2 = 0.0f;
    sr = sample_rate;
}

float Process(float input)
{
    c = 1.0f / (tanf(M_PI * (cutoff_ / sr)));
    csq = c * c;
    resonance = powf(10.0f, -(res_ * 0.1f));
    q = sqrt(2.0f) * resonance;
    a0 = 1.0f / (1.0f + (q * c) + (csq));
    a1 = 2.0f * a0;
    a2 = a0;
    b1 = (2.0f * a0) * (1.0f - csq);
    b2 = a0 * (1.0f - (q * c) + csq);

    float outputSample = a0 * input + a1 * x1 + a2 * x2
                       - b1 * y1 - b2 * y2;
    
    // Update state variables
    x2 = x1;
    x1 = input;
    y2 = y1;
    y1 = outputSample;
    
    return outputSample;
}

void SetResonance(float res)
{
    res_ = res;
}

void SetCutoff(float cut)
{
    cutoff_ = cut;
}

private:
float c, csq, resonance, q, a0, a1, a2, b1, b2, sr, x1, x2, y1, y2;
float res_, cutoff_;

};

#pragma once

#ifndef INPUT_GAIN_H
#define INPUT_GAIN_H

class InputGain
{
public:
    InputGain() {};
    ~InputGain() {}; 

    void Init() {
        gain_ = 0.f;
    }

    float Process(float input, float gain) {
        gain_ = gain;
        output_ = input * gain_;
        return output_;
    }

private:
    float gain_;
    float output_;
};

#endif // INPUT_GAIN_H
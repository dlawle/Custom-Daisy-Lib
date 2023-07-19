#include "daisy_patch_sm.h"
#include "daisysp.h"
#include "daisy_bed.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM hw;

Metro		 clock, clock2;

void clockTiming();
uint32_t previous_clock_;
float period_;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();
	for (size_t i = 0; i < size; i++)
	{
		OUT_L[i] = IN_L[i];
		OUT_R[i] = IN_R[i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	float samplerate = hw.AudioSampleRate();
	InitBed();
	hw.StartLog();
	clock.Init(2, samplerate);
	clock2.Init(0.001, samplerate);

	hw.StartAudio(AudioCallback);
	while(1) 
	{
		clock2.SetFreq(period_);
		if (clock.Process()) 
		{ 
			clockTiming();
			gen_led1.Toggle(); 
		}

		hw.PrintLine("Period %f", period_);
	}
}
	
uint32_t us_diff(uint32_t now, uint32_t last)
{
	// credit nick @  https://www.infrasonicaudio.com/
    if (now < last)
    {
        // handle wraparound
        now += UINT32_MAX / (System::GetTickFreq() / 1e6);
    }
    return now - last;
}


void clockTiming() 
{
	// credit awonak @ https://github.com/awonak
	period_ = us_diff(System::GetUs(), previous_clock_);
	previous_clock_ = System::GetUs();
}

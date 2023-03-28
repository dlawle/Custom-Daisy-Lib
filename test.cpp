#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;
using namespace seed;

DaisySeed				hw;

enum AdcChannel {
   pot1 = 0,
   pot2,
   pot3,
   pot4,
   pot5,
   NUM_ADC_CHANNELS
};

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
}

int main(void)
{
	hw.Init();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	float sample_rate = hw.AudioSampleRate();

	AdcChannelConfig adc_config[NUM_ADC_CHANNELS];
	adc_config[pot1].InitSingle(A0);
	adc_config[pot2].InitSingle(A1);
	adc_config[pot3].InitSingle(A4);
	adc_config[pot4].InitSingle(A5);
	adc_config[pot5].InitSingle(A9);
	hw.adc.Init(adc_config,NUM_ADC_CHANNELS);
	hw.adc.Start();

	hw.StartAudio(AudioCallback);
	while(1) {}
}

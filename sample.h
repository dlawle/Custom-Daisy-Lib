// idea from aidolon at https://github.com/TDE-synthesis/

class SamplePlayer {
public:
  SamplePlayer(SomeVectorType<float> *sample, size_t length) {
    _length = length;
    _sample.copyFrom(sample, length); // copy from the input buffer
  }
  
  void triggerPlayback(float start = 0.f, float playbackSpeed = 1.f) {
    _playbackSpeed = playbackSpeed;
    _scanner = min(start, (float)_length);    // this lets us start at any point in the sample
  }

  float tick() {
    if (_scanner < (_length - 1)) {
      size_t index = floor(_scanner);
      float ret = _sample[index] + (_sample[index + 1] - _sample[index]) * (_scanner - index);  // linear interpolation allows for non-integer indeces
      _scanner += _playbackSpeed; // advance playhead
      return ret;
    }
    else
      return 0.f;  // sample is over; we want silence
  }
private:
  float _scanner;  // keeps track of where we are in the sample
  float _playbackSpeed;  // speed multiplier allows for basic pitch control
  SomeVectorType<float> _sample;  // buffer to hold the actual sample
  size_t _length;  // length of sample
}

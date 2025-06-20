#pragma once

#include <JuceHeader.h>
#include "../Parameters.h"

class MDAAmbience
{
public:
    MDAAmbience(Parameters& params);

    void prepareToPlay(double sampleRate) noexcept;
    void releaseResources() noexcept;
    void reset() noexcept;
    void processBlock(juce::AudioBuffer<float>&) noexcept;

private:
    void update() noexcept;
    void flushBuffers() noexcept;

    Parameters& _params;

    // Delay lines. The maximum length of these is hardcoded to 1024 samples.
    float *_buf1 = nullptr, *_buf2, *_buf3, *_buf4;

    // Read position in the delay buffers.
    int _pos;

    // This sets the length of the delays.
    float _size;

    // Feedback coefficient for the allpass filters.
    float _feedback;

    // Low-pass filter coefficient for HF damping.
    float _damp;

    // Low-pass filter state value.
    float _filter;

    // Wet/dry mix.
    float _wet, _dry;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MDAAmbience)
};

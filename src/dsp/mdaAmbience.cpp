#include "dsp/mdaAmbience.h"

MDAAmbience::MDAAmbience(Parameters& params) : _params(params)
{
    // do nothing
}

void MDAAmbience::prepareToPlay([[maybe_unused]] double sampleRate) noexcept
{
    if (_buf1 == nullptr) {
        _buf1 = new (std::nothrow) float[1024];
        _buf2 = new (std::nothrow) float[1024];
        _buf3 = new (std::nothrow) float[1024];
        _buf4 = new (std::nothrow) float[1024];
    }
}

void MDAAmbience::releaseResources() noexcept
{
    delete [] _buf1; _buf1 = nullptr;
    delete [] _buf2; _buf2 = nullptr;
    delete [] _buf3; _buf3 = nullptr;
    delete [] _buf4; _buf4 = nullptr;
}

void MDAAmbience::reset() noexcept
{
    flushBuffers();
    _pos = 0;
    _filter = 0.0f;
}

void MDAAmbience::flushBuffers() noexcept
{
    memset(_buf1, 0, 1024 * sizeof(float));
    memset(_buf2, 0, 1024 * sizeof(float));
    memset(_buf3, 0, 1024 * sizeof(float));
    memset(_buf4, 0, 1024 * sizeof(float));
}

void MDAAmbience::update() noexcept
{
    _feedback = 0.8f;

    // Convert the percentage to a filter coefficient between 0.05 - 0.95.
    float fParam1 = _params.reverbDampParam->get() / 100.0f;
    _damp = 0.05f + 0.9f * fParam1;

    // Calculate a dry/wet balance based on the mix setting. If mix = 0%, only
    // the dry signal is used. At mix = 68%, dry and wet are both approx 0.54.
    // For mix = 100%, wet is 0.8 and dry is 0. So this is slightly different
    // from a regular dry/wet mix that does dry = 100% - wet.
    float fParam2 = _params.reverbMixParam->get() / 100.0f;
    _dry = 1.0f - fParam2 * fParam2;
    _wet = (0.4f + 0.4f) * fParam2;

    // Convert the size from 0 - 10 meters to a value between 0.025 - 2.69.
    // This size is used to set the delay times on the different delay lines:
    // a larger size means a longer delay. The sample rate is not taken into
    // consideration here, so the units (meters) seem to be kind of pointless,
    // and running the plugin at different sample rates will give different
    // results for the same size setting.
    float fParam0 = _params.reverbSizeParam->get() / 10.0f;
    float tmp = 0.025f + 2.665f * fParam0;
    if (_size != tmp) { flushBuffers(); }  // need to flush delay lines
    _size = tmp;
}

void MDAAmbience::processBlock(juce::AudioBuffer<float>& buffer) noexcept
{
    update();

    const float *in1 = buffer.getReadPointer(0);
    const float *in2 = buffer.getReadPointer(1);
    float *out1 = buffer.getWritePointer(0);
    float *out2 = buffer.getWritePointer(1);

    int p = _pos;

    // The main structure of this effect is four allpass filters in series.
    // Each of these is made up of a delay line with a different delay length.
    // The _size variable sets the actual delay time, with 1024 samples being
    // the maximum. (Note: 379 * the maximum size 2.69 is just less than 1024.)
    // The d1 - d4 variables are the write indices into the four delay lines.
    // We do `& 1023` to wrap around the index when it goes past the end.
    int d1 = (p + int(107 * _size)) & 1023;
    int d2 = (p + int(142 * _size)) & 1023;
    int d3 = (p + int(277 * _size)) & 1023;
    int d4 = (p + int(379 * _size)) & 1023;

    const float feedback = _feedback;
    const float damp = _damp;
    const float dry = _dry;
    const float wet = _wet;
    float f = _filter;

    for (int i = 0; i < buffer.getNumSamples(); ++i) {
        float a = in1[i];
        float b = in2[i];

        // Combine the left and right stereo inputs into a single mono value.
        // (This actually adds a +6 dB boost, which may be undesirable.)
        // Also multiply by the wetness amount. We can do this here already
        // because everything that follows are linear operations.
        float x = wet * (a + b);

        // HF damping. This is a simple low-pass filter: f = a*x + (1 - a)*f.
        f += damp * (x - f);
        float r = f;

        /*
          Next there are four sections of allpass filters, as explained here:
          https://ccrma.stanford.edu/~jos/pasp/Schroeder_Allpass_Sections.html

          Each of these allpass stages does the following:

                     ^-----------------------+
                     |                       |
                     |                       v
              r ---> + --------> delay ---------> + ---> new r
                           ^                      |
                           |                      |
                           <---- *(-feedback) ----v

          This is a typical allpass filter design. The feedback is always 0.8.
         */

        // First allpass stage.
        float t = _buf1[p];
        r -= feedback * t;
        _buf1[d1] = r;
        r += t;

        // Second allpass stage.
        t = _buf2[p];
        r -= feedback * t;
        _buf2[d2] = r;
        r += t;

        // Third allpass stage.
        t = _buf3[p];
        r -= feedback * t;
        _buf3[d3] = r;
        r += t;

        // The left output is a mix of the dry input with the allpass-filtered
        // signal. The original low-pass filtered signal is subtracted.
        // Not sure why the LPF value gets subtracted but that is what makes
        // this effect work; I'll need to read up on reverbs, I guess. ;-)
        a = dry * a + r - f;

        // Fourth allpass stage.
        t = _buf4[p];
        r -= feedback * t;
        _buf4[d4] = r;
        r += t;

        // The right channel output.
        b = dry * b + r - f;

        // Advance the read and write indices for the delay lines, wrap if needed.
        ++p  &= 1023;
        ++d1 &= 1023;
        ++d2 &= 1023;
        ++d3 &= 1023;
        ++d4 &= 1023;

        out1[i] = a;
        out2[i] = b;
    }

    _pos = p;

    // Catch denormals
    if (std::abs(f) > 1.0e-10f) {
        _filter = f;
    } else {
        _filter = 0.0f;
        flushBuffers();
    }
}

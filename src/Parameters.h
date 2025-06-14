#pragma once

#include <JuceHeader.h>

namespace ParameterID
{
    const juce::ParameterID outputLevel { "outputLevel", 1 };
}

class Parameters
{
public:
    Parameters(juce::AudioProcessorValueTreeState& apvts);

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    void prepareToPlay(float sampleRate) noexcept;
    void reset() noexcept;
    void update() noexcept;
    void smoothen() noexcept;

    float sampleRate = 44100.0f;

    float outputLevel = 1.0f;

private:
    juce::AudioParameterFloat* outputLevelParam;

    juce::LinearSmoothedValue<float> outputLevelSmoother;
};

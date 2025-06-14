#include "Parameters.h"

template<typename T>
inline void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);  // parameter does not exist or wrong type
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, ParameterID::outputLevel, outputLevelParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::outputLevel,
        "Output Level",
        juce::NormalisableRange<float>(-24.0f, 0.0f),
        -12.0f,
        juce::AudioParameterFloatAttributes().withLabel("dB")));

    return layout;
}

void Parameters::prepareToPlay(float newSampleRate) noexcept
{
    sampleRate = newSampleRate;

    double smoothTime = 0.02;
    outputLevelSmoother.reset(sampleRate, smoothTime);
}

void Parameters::reset() noexcept
{
    outputLevelSmoother.setCurrentAndTargetValue(juce::Decibels::decibelsToGain(outputLevelParam->get()));
}

void Parameters::update() noexcept
{
    outputLevelSmoother.setTargetValue(juce::Decibels::decibelsToGain(outputLevelParam->get()));
}

void Parameters::smoothen() noexcept
{
    outputLevel = outputLevelSmoother.getNextValue();
}

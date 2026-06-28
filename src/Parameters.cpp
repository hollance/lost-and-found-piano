#include "Parameters.h"

static juce::String stringFromDecibels(float value, int)
{
    return juce::String(value, 1) + " dB";
}

static juce::String stringFromPercent(float value, int)
{
    return juce::String(int(value)) + " %";
}

static juce::String cents()
{
    return { juce::CharPointer_UTF8(" ¢") };
}

static juce::String stringFromCents(float value, int)
{
    return juce::String(int(value)) + cents();
}

template<typename T>
inline static void castParameter(juce::AudioProcessorValueTreeState& apvts, const juce::ParameterID& id, T& destination)
{
    destination = dynamic_cast<T>(apvts.getParameter(id.getParamID()));
    jassert(destination);  // parameter does not exist or wrong type
}

Parameters::Parameters(juce::AudioProcessorValueTreeState& apvts)
{
    castParameter(apvts, ParameterID::instrument, instrumentParam);
    castParameter(apvts, ParameterID::fineTuning, fineTuningParam);
    castParameter(apvts, ParameterID::randomDetuning, randomDetuningParam);
    castParameter(apvts, ParameterID::stretchTuning, stretchTuningParam);
    castParameter(apvts, ParameterID::envDecay, envDecayParam);
    castParameter(apvts, ParameterID::envRelease, envReleaseParam);
    castParameter(apvts, ParameterID::velocitySensitivity, velocitySensitivityParam);
    castParameter(apvts, ParameterID::hardness, hardnessParam);
    castParameter(apvts, ParameterID::velocityToHardness, velocityToHardnessParam);
    castParameter(apvts, ParameterID::mufflingFilter, mufflingFilterParam);
    castParameter(apvts, ParameterID::velocityToMuffling, velocityToMufflingParam);
    castParameter(apvts, ParameterID::modulation, modulationParam);
    castParameter(apvts, ParameterID::lfoRate, lfoRateParam);
    castParameter(apvts, ParameterID::trebleBoost, trebleBoostParam);
    castParameter(apvts, ParameterID::overdrive, overdriveParam);
    castParameter(apvts, ParameterID::stereoWidth, stereoWidthParam);
    castParameter(apvts, ParameterID::reverbSize, reverbSizeParam);
    castParameter(apvts, ParameterID::reverbDamp, reverbDampParam);
    castParameter(apvts, ParameterID::reverbMix, reverbMixParam);
    castParameter(apvts, ParameterID::outputLevel, outputLevelParam);
}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    layout.add(std::make_unique<juce::AudioParameterChoice>(
        ParameterID::instrument,
        "Instrument",
        juce::StringArray { "Acoustic", "Electric" }, 0
        ));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::fineTuning,
        "Fine Tuning",
        juce::NormalisableRange<float>(-50.0f, 50.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromCents)));

    // The random detuning parameter is not linear but uses a bit of a curve.
    // Could do this with skew, but it's easier to keep this parameter in the
    // 0 - 1 range since we will only treat it indirectly as cents anyway.

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::randomDetuning,
        "Random Detuning",
        juce::NormalisableRange<float>(),
        0.0f,
        juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction(
                [](float value, int) {
                    return juce::String(50.0f * value * value, 1) + cents();
                }
            )));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::stretchTuning,
        "Stretch Tuning",
        juce::NormalisableRange<float>(-50.0f, 50.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromCents)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envDecay,
        "Envelope Decay",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::envRelease,
        "Envelope Release",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::velocitySensitivity,
        "Velocity Sensitivity",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        33.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::hardness,
        "Hardness",
        juce::NormalisableRange<float>(-50.0f, 50.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::velocityToHardness,
        "Velocity to Hardness",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    // The "Muffling Filter" goes from 100 to 0 but JUCE doesn't let us specify
    // the range starting at 100 and ending at 0, so we reverse it for display.

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::mufflingFilter,
        "Muffling Filter",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction(
                [](float value, int) {
                    return juce::String(100.0f - value, 1) + "%";
                }
            )));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::velocityToMuffling,
        "Velocity to Muffling",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        50.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::modulation,
        "Modulation",
        juce::NormalisableRange<float>(),
        0.5f,
        juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction(
                [](float value, int) {
                   if (value > 0.5f) {
                       return "Trem " + juce::String(int(200.0f * value - 100.0f));
                   } else {
                       return "Pan " + juce::String(int(100.0f - 200.0f * value));
                    }
                }
            )));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::lfoRate,
        "LFO Rate",
        juce::NormalisableRange<float>(),
        0.0f,
        juce::AudioParameterFloatAttributes()
            .withStringFromValueFunction(
                [](float value, int) {
                    return juce::String(std::exp(6.22f * value - 2.61f), 2) + " Hz";
                }
            )));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::trebleBoost,
        "EQ",
        juce::NormalisableRange<float>(-50.0f, 50.0f, 1.0f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::overdrive,
        "Overdrive",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::stereoWidth,
        "Stereo Width",
        juce::NormalisableRange<float>(0.0f, 200.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::reverbSize,
        "Size",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.01f),
        7.0f));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::reverbDamp,
        "HF Damp",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.01f),
        70.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::reverbMix,
        "Mix",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.01f),
        90.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromPercent)));

    layout.add(std::make_unique<juce::AudioParameterFloat>(
        ParameterID::outputLevel,
        "Output Level",
        juce::NormalisableRange<float>(-24.0f, 0.0f, 0.01f),
        -12.0f,
        juce::AudioParameterFloatAttributes().withStringFromValueFunction(stringFromDecibels)));

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

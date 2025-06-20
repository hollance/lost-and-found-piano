#pragma once

#include <JuceHeader.h>

namespace ParameterID
{
    const juce::ParameterID instrument { "instrument", 1 };
    const juce::ParameterID fineTuning { "fineTuning", 1 };
    const juce::ParameterID randomDetuning { "randomDetuning", 1 };
    const juce::ParameterID stretchTuning { "stretchTuning", 1 };
    const juce::ParameterID envDecay { "envDecay", 1 };
    const juce::ParameterID envRelease { "envRelease", 1 };
    const juce::ParameterID velocitySensitivity { "velocitySensitivity", 1 };
    const juce::ParameterID hardness { "hardness", 1 };
    const juce::ParameterID velocityToHardness { "velocityToHardness", 1 };
    const juce::ParameterID mufflingFilter { "mufflingFilter", 1 };
    const juce::ParameterID velocityToMuffling { "velocityToMuffling", 1 };
    const juce::ParameterID tremolo { "tremolo", 1 };
    const juce::ParameterID autopan { "autopan", 1 };
    const juce::ParameterID lfoRate { "lfoRate", 1 };
    const juce::ParameterID trebleBoost { "trebleBoost", 1 };
    const juce::ParameterID overdrive { "overdrive", 1 };
    const juce::ParameterID stereoWidth { "stereoWidth", 1 };
    const juce::ParameterID reverbSize { "reverbSize", 1 };
    const juce::ParameterID reverbDamp { "reverbDamp", 1 };
    const juce::ParameterID reverbMix { "reverbMix", 1 };
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

    bool isAcoustic() const noexcept
    {
        return instrumentParam->getIndex() == 0;
    }

    float sampleRate = 44100.0f;
    float outputLevel = 1.0f;

    juce::AudioParameterChoice* instrumentParam;
    juce::AudioParameterFloat* fineTuningParam;
    juce::AudioParameterFloat* randomDetuningParam;
    juce::AudioParameterFloat* stretchTuningParam;
    juce::AudioParameterFloat* envDecayParam;
    juce::AudioParameterFloat* envReleaseParam;
    juce::AudioParameterFloat* velocitySensitivityParam;
    juce::AudioParameterFloat* hardnessParam;
    juce::AudioParameterFloat* velocityToHardnessParam;
    juce::AudioParameterFloat* mufflingFilterParam;
    juce::AudioParameterFloat* velocityToMufflingParam;
    juce::AudioParameterFloat* tremoloParam;
    juce::AudioParameterFloat* autopanParam;
    juce::AudioParameterFloat* lfoRateParam;
    juce::AudioParameterFloat* trebleBoostParam;
    juce::AudioParameterFloat* overdriveParam;
    juce::AudioParameterFloat* stereoWidthParam;
    juce::AudioParameterFloat* reverbSizeParam;
    juce::AudioParameterFloat* reverbDampParam;
    juce::AudioParameterFloat* reverbMixParam;
    juce::AudioParameterFloat* outputLevelParam;

private:
    juce::LinearSmoothedValue<float> outputLevelSmoother;
};

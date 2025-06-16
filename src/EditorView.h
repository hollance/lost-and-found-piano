#pragma once

#include <JuceHeader.h>
#include "GroupView.h"
#include "LookAndFeel.h"
#include "MidiKeyboardComponent.h"
#include "PluginProcessor.h"
#include "RotaryKnob.h"

// The width is 52 white piano keys times 18 pixels, minus one pixel.
static constexpr int defaultWidth = 935;
static constexpr int defaultHeight = 561;

class EditorView : public juce::Component, private juce::AudioParameterChoice::Listener
{
public:
    EditorView(AudioProcessor& audioProcessor);
    ~EditorView() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int, bool) override { }

    void updateUI();

    AudioProcessor& audioProcessor;

    GroupView tuningGroup { "Tuning" };
    RotaryKnob fineTuningKnob { "Fine", audioProcessor.apvts, ParameterID::fineTuning };
    RotaryKnob randomDetuningKnob { "Random", audioProcessor.apvts, ParameterID::randomDetuning };
    RotaryKnob stretchTuningKnob { "Stretch", audioProcessor.apvts, ParameterID::stretchTuning };

    GroupView envelopeGroup { "Envelope" };
    RotaryKnob envDecayKnob { "Decay", audioProcessor.apvts, ParameterID::envDecay };
    RotaryKnob envReleaseKnob { "Release", audioProcessor.apvts, ParameterID::envRelease };
    RotaryKnob velocitySensitivityKnob { "Velocity", audioProcessor.apvts, ParameterID::velocitySensitivity };

    GroupView filterGroup { "Filter" };
    RotaryKnob mufflingFilterKnob { "Muffling", audioProcessor.apvts, ParameterID::mufflingFilter };
    RotaryKnob velocityToMufflingKnob { "Velocity", audioProcessor.apvts, ParameterID::velocityToMuffling };

    GroupView modulationGroup { "Modulation" };
    RotaryKnob tremoloKnob { "Tremolo", audioProcessor.apvts, ParameterID::tremolo };
    RotaryKnob autopanKnob { "Panning", audioProcessor.apvts, ParameterID::autopan };
    RotaryKnob lfoRateKnob { "Rate", audioProcessor.apvts, ParameterID::lfoRate };

    GroupView hardnessGroup { "Hardness" };
    RotaryKnob hardnessKnob { "Hardness", audioProcessor.apvts, ParameterID::hardness };
    RotaryKnob velocityToHardnessKnob { "Velocity", audioProcessor.apvts, ParameterID::velocityToHardness };

    GroupView effectsGroup { "FX" };
    RotaryKnob trebleBoostKnob { "EQ", audioProcessor.apvts, ParameterID::trebleBoost };
    RotaryKnob overdriveKnob { "Overdrive", audioProcessor.apvts, ParameterID::overdrive };
    RotaryKnob stereoWidthKnob { "Stereo", audioProcessor.apvts, ParameterID::stereoWidth };

    GroupView reverbGroup { "Reverb" };
    RotaryKnob reverbSizeKnob { "Size", audioProcessor.apvts, ParameterID::reverbSize };
    RotaryKnob reverbDampKnob { "Damp", audioProcessor.apvts, ParameterID::reverbDamp };
    RotaryKnob reverbMixKnob { "Dry/Wet", audioProcessor.apvts, ParameterID::reverbMix };

    GroupView outputGroup { "Out" };
    RotaryKnob outputLevelKnob { "Level", audioProcessor.apvts, ParameterID::outputLevel };

    MidiKeyboardComponent keyboardComponent;

    juce::VBlankAnimatorUpdater animatorUpdater { this };

    juce::Animator animator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEase())
        .withDurationMs(500.0)
        .withValueChangedCallback([this](auto value) {
            if (audioProcessor.params.instrumentParam->getIndex() == 0) {
                filterGroup.setAlpha(value);
                modulationGroup.setAlpha(1.0f - value);
            } else {
                filterGroup.setAlpha(1.0f - value);
                modulationGroup.setAlpha(value);
            }
        })
        .withOnCompleteCallback([this]() {
            filterGroup.setAlpha(1.0f);
            modulationGroup.setAlpha(1.0f);
            updateUI();
        })
        .build();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorView)
};

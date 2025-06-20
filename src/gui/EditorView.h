#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "GroupView.h"
#include "LookAndFeel.h"
#include "MidiKeyboardComponent.h"
#include "RadioButtonAttachment.h"
#include "RotaryKnob.h"
#include "SelectionBar.h"

// The width is 52 white piano keys times 18 pixels, minus one pixel.
static constexpr int defaultWidth = 935;
static constexpr int defaultHeight = 500;

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

    LookAndFeel lf;

    juce::TextButton acousticButton;
    juce::TextButton electricButton;
    SelectionBar selectionBar;

    RadioButtonAttachment instrumentAttachment;

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
    RotaryKnob depthKnob { "Depth", audioProcessor.apvts, ParameterID::modulation };
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

    juce::Animator barAnimator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseOutBack())
        .withDurationMs(300.0)
        .withValueChangedCallback([this](auto value) {
            if (audioProcessor.params.isAcoustic()) {
                float dx = (electricButton.getX() - acousticButton.getX()) * (1.0f - value);
                selectionBar.setTransform(juce::AffineTransform::translation(dx, 0.0f));
            } else {
                float dx = (electricButton.getX() - acousticButton.getX()) * (value - 1.0f);
                selectionBar.setTransform(juce::AffineTransform::translation(dx, 0.0f));
            }
        })
        .withOnCompleteCallback([this]() {
            selectionBar.setBounds(
                audioProcessor.params.isAcoustic() ? acousticButton.getBounds()
                                                   : electricButton.getBounds());
            selectionBar.setTransform({});
        })
        .build();

    juce::Animator groupAnimator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseInOutCubic())
        .withDurationMs(500.0)
        .withValueChangedCallback([this](auto value) {
            if (filterGroup.isVisible()) {
                filterGroup.setAlpha(value);
            } else {
                modulationGroup.setAlpha(value);
            }
        })
        .withOnCompleteCallback([this]() {
            filterGroup.setAlpha(1.0f);
            modulationGroup.setAlpha(1.0f);
            updateUI();
        })
        .build();

    juce::Animator animator = juce::AnimatorSetBuilder(barAnimator).followedBy(groupAnimator).build();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorView)
};

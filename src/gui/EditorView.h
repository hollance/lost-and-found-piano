#pragma once

#include "PluginProcessor.h"
#include "gui/GroupView.h"
#include "gui/LookAndFeel.h"
#include "gui/MidiKeyboardComponent.h"
#include "gui/PresetPicker.h"
#include "gui/RadioButtonAttachment.h"
#include "gui/RotaryKnob.h"
#include "gui/SelectionBar.h"
#include <JuceHeader.h>

class EditorView : public juce::Component, private juce::AudioParameterChoice::Listener
{
public:
    EditorView(AudioProcessor& audioProcessor);
    ~EditorView() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

    void updatePresetNameButton();

private:
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int, bool) override { }

    void updateInstrument();
    void updateUI();

    void showPresetPicker();
    void showSaveDialog();

    AudioProcessor& audioProcessor;
    PresetManager& presetManager;

    LookAndFeel lf;
    PresetsLookAndFeel rightLF { juce::Justification::centredRight };
    PresetsLookAndFeel centerLF { juce::Justification::centred };

    juce::TextButton acousticButton;
    juce::TextButton electricButton;
    SelectionBar selectionBar;

    juce::TextButton prevButton;
    juce::TextButton nextButton;
    juce::TextButton saveButton;
    juce::TextButton presetNameButton;

    PresetPicker presetPicker;

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
    RotaryKnob reverbMixKnob { "Mix", audioProcessor.apvts, ParameterID::reverbMix };

    GroupView outputGroup { "Out" };
    RotaryKnob outputLevelKnob { "Level", audioProcessor.apvts, ParameterID::outputLevel };

    MidiKeyboardComponent keyboardComponent;

    juce::VBlankAnimatorUpdater animatorUpdater { this };

    juce::Animator barAnimator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseOutBack())
        .withDurationMs(300.0)
        .withValueChangedCallback([this](auto value) {
            if (audioProcessor.params.isAcoustic()) {
                float dx = float(electricButton.getX() - acousticButton.getX()) * (1.0f - value);
                selectionBar.setTransform(juce::AffineTransform::translation(dx, 0.0f));
            } else {
                float dx = float(electricButton.getX() - acousticButton.getX()) * (value - 1.0f);
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

    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorView)
};

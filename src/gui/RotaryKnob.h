#pragma once

#include "gui/LookAndFeel.h"
#include <JuceHeader.h>

class RotaryKnob : public juce::Component, private juce::Timer
{
public:
    RotaryKnob(juce::String text,
               juce::AudioProcessorValueTreeState& apvts,
               const juce::ParameterID& parameterID);

    ~RotaryKnob() override;

    void paint(juce::Graphics& g) override;

private:
    void timerCallback() override;

    void showValueLabel();
    void hideValueLabel();
    void updateValueLabel();

    LookAndFeel lf;

    juce::Slider slider;
    juce::Label nameLabel;
    juce::Label valueLabel;

    juce::String knobName;

    juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    juce::VBlankAnimatorUpdater animatorUpdater { this };

    juce::Animator animator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseInOutCubic())
        .withDurationMs(500.0)
        .withValueChangedCallback([this](auto value) {
            nameLabel.setAlpha(value);
            valueLabel.setAlpha(1.0f - value);
        })
        .withOnCompleteCallback([this]() {
            valueLabel.setVisible(false);
            valueLabel.setAlpha(1.0f);
        })
        .build();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnob)
};

#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"

class RotaryKnob : public juce::Component
{
public:
    RotaryKnob(const juce::String& text/*,
               juce::AudioProcessorValueTreeState& apvts,
               const juce::ParameterID& parameterID*/);

    ~RotaryKnob() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    LookAndFeel lf;

    juce::Slider slider;
    juce::Label label;

    //juce::AudioProcessorValueTreeState::SliderAttachment attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryKnob)
};

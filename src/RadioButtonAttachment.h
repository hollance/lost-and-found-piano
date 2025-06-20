#pragma once

#include <JuceHeader.h>

class RadioButtonAttachment : private juce::Button::Listener
{
public:
    RadioButtonAttachment(juce::AudioProcessorValueTreeState& stateToUse,
                          const juce::String& parameterID,
                          const std::vector<juce::Button*> paramButtons);

    ~RadioButtonAttachment() override;

    void sendInitialUpdate();

private:
    void setValue(float newValue);
    void buttonClicked(juce::Button*) override;

    std::vector<juce::Button*> buttons;
    juce::RangedAudioParameter& parameter;
    juce::ParameterAttachment attachment;
    bool ignoreCallbacks = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RadioButtonAttachment)
};

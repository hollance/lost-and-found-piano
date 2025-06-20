#pragma once

#include <JuceHeader.h>

class MidiKeyboardComponent : public juce::MidiKeyboardComponent
{
public:
    MidiKeyboardComponent(juce::MidiKeyboardState& state, juce::MidiKeyboardComponent::Orientation orientation);

    void drawWhiteNote(int, juce::Graphics&, juce::Rectangle<float>, bool, bool, juce::Colour, juce::Colour) override;
    void drawBlackNote(int, juce::Graphics&, juce::Rectangle<float>, bool, bool, juce::Colour) override;
    juce::String getWhiteNoteText(int midiNoteNumber) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiKeyboardComponent)
};

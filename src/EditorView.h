#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "MidiKeyboardComponent.h"
#include "PluginProcessor.h"
#include "RotaryKnob.h"

// The width is 52 white piano keys times 18 pixels, minus one pixel.
static constexpr int defaultWidth = 935;
static constexpr int defaultHeight = 425;

class EditorView : public juce::Component
{
public:
    EditorView(AudioProcessor& processor);
    ~EditorView() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void drawGroup(juce::Graphics&, const juce::String& name, int x, int y, int width);

    RotaryKnob reverbSizeKnob { "Size" };
    RotaryKnob reverbDampKnob { "Damp" };
    RotaryKnob reverbMixKnob { "Dry/Wet" };

    // TODO: add all components here!

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorView)
};

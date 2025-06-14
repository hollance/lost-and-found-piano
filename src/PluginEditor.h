#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "EditorView.h"
#include "LookAndFeel.h"

class AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AudioProcessorEditor(AudioProcessor&);
    ~AudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    AudioProcessor& audioProcessor;
    LookAndFeel lf;
    juce::ComponentBoundsConstrainer constrainer;
    EditorView editorView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorEditor)
};

#pragma once

#include "PluginProcessor.h"
#include "gui/EditorView.h"
#include "gui/LookAndFeel.h"
#include <JuceHeader.h>

class AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    AudioProcessorEditor(AudioProcessor&);
    ~AudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    LookAndFeel lf;
    juce::ComponentBoundsConstrainer constrainer;
    EditorView editorView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorEditor)
};

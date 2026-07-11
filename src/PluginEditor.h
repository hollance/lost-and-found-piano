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

    void resized() override;
    void visibilityChanged() override;

    void updatePresetNameButton();

private:
    void updateSize();
    void restoreDefaultSize();

    LookAndFeel lf;
    juce::ComponentBoundsConstrainer constrainer;

    EditorView editorView;
    Settings& settings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessorEditor)
};

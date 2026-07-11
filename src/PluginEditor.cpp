#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioProcessorEditor::AudioProcessorEditor(AudioProcessor& p)
    : juce::AudioProcessorEditor(p), editorView(p), settings(p.settings)
{
    setLookAndFeel(&lf);

    editorView.setBounds(0, 0, defaultWidth, defaultHeight);
    addAndMakeVisible(editorView);

    constrainer.setMinimumSize(defaultWidth / 2, defaultHeight / 2);
    constrainer.setMaximumSize(defaultWidth * 2, defaultHeight * 2);
    constrainer.setFixedAspectRatio(double(defaultWidth) / double(defaultHeight));
    setConstrainer(&constrainer);

    setResizable(true, true);
    updateSize();
}

AudioProcessorEditor::~AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void AudioProcessorEditor::resized()
{
    auto scale = float(getWidth()) / float(defaultWidth);
    editorView.setTransform(juce::AffineTransform::scale(scale));
    settings.setWindowWidth(getWidth());
}

void AudioProcessorEditor::visibilityChanged()
{
    if (isVisible()) {
        settings.reload();
        updateSize();
    }
}

void AudioProcessorEditor::updateSize()
{
    int width = settings.getWindowWidth();
    int height = int(width * double(defaultHeight) / double(defaultWidth));
    setSize(width, height);    
}

void AudioProcessorEditor::restoreDefaultSize()
{
    setSize(defaultWidth, defaultHeight);
}

void AudioProcessorEditor::updatePresetNameButton()
{
    editorView.updatePresetNameButton();
}

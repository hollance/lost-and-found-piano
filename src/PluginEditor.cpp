#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessorEditor::AudioProcessorEditor(AudioProcessor& p)
    : juce::AudioProcessorEditor(&p), audioProcessor(p), editorView(p)
{
    setOpaque(true);
    setLookAndFeel(&lf);

    editorView.setBounds(0, 0, defaultWidth, defaultHeight);
    addAndMakeVisible(editorView);

    constrainer.setMinimumSize((defaultWidth * 6) / 10, (defaultHeight * 6) / 10);
    constrainer.setMaximumSize(defaultWidth * 10, defaultHeight * 10);
    constrainer.setFixedAspectRatio(double(defaultWidth) / double(defaultHeight));
    setConstrainer(&constrainer);

    setResizable(true, true);
    setSize(defaultWidth, defaultHeight);
}

AudioProcessorEditor::~AudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void AudioProcessorEditor::paint([[maybe_unused]] juce::Graphics& g)
{
}

void AudioProcessorEditor::resized()
{
    float scale = getWidth() / float(defaultWidth);
    editorView.setTransform(juce::AffineTransform::scale(scale));
}

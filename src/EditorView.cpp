#include "EditorView.h"

EditorView::EditorView(AudioProcessor& p)
    : keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setOpaque(true);

    addAndMakeVisible(reverbSizeKnob);
    addAndMakeVisible(reverbDampKnob);
    addAndMakeVisible(reverbMixKnob);

    addAndMakeVisible(keyboardComponent);
}

EditorView::~EditorView()
{
}

void EditorView::paint(juce::Graphics& g)
{
    g.fillAll(Colors::background);

    g.setColour(juce::Colour(0xff000000));
    g.fillRect(0, 0, defaultWidth, 38);

    g.setColour(Colors::accent1);
    g.fillRect(0, 38, defaultWidth, 2);

    g.setFont(Fonts::getFont(32.0f));
    g.setColour(juce::Colours::white);
    g.drawSingleLineText("Lost & Found", 20, 27);
    g.setColour(Colors::accent1);
    g.drawSingleLineText("Piano", 166, 27);

    drawGroup(g, "Tuning", 20, 100, 270);
    drawGroup(g, "Envelope", 310, 100, 270);
    drawGroup(g, "Hardness", 600, 100, 180);
    drawGroup(g, "Out", 800, 100, 115);

    drawGroup(g, "Piano", 40, 200, 270);
    drawGroup(g, "Reverb", 330, 200, 270);
    drawGroup(g, "FX", 620, 200, 270);

    g.setColour(Colors::accent1);
    g.fillRect(0, defaultHeight - 84, defaultWidth, 4);

    g.setColour(juce::Colour(0xff000000));
    g.fillRect(0, defaultHeight - 80, defaultWidth, 90);
}

void EditorView::drawGroup(juce::Graphics& g, const juce::String& name, int x, int y, int width)
{
    auto font = Fonts::getFont();
    auto textWidth = int(std::ceil(juce::TextLayout::getStringWidth(font, name)));

    int offset = (width - textWidth) / 2;

    g.setColour(Colors::text);
    g.setFont(Fonts::getFont());
    g.drawSingleLineText(name, x + offset, y + 22);

    g.setColour(Colors::text.withAlpha(0.5f));
    g.fillRect(x, y + 14, offset - 5, 2);
    g.fillRect(x + width - (offset - 5), y + 14, offset - 5, 2);

    //g.setColour(juce::Colours::yellow);
    //g.drawRect(x, y, width, 30);
}

void EditorView::resized()
{
    reverbSizeKnob.setTopLeftPosition(330, 235);
    reverbDampKnob.setTopLeftPosition(reverbSizeKnob.getRight(), reverbSizeKnob.getY());
    reverbMixKnob.setTopLeftPosition(reverbDampKnob.getRight(), reverbDampKnob.getY());

    keyboardComponent.setBounds(0, defaultHeight - 80, defaultWidth + 1, 80);
}

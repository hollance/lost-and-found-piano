#include "EditorView.h"

EditorView::EditorView(AudioProcessor& p) :
    audioProcessor(p),
    keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setOpaque(true);

    addAndMakeVisible(fineTuningKnob);
    addAndMakeVisible(randomDetuningKnob);
    addAndMakeVisible(stretchTuningKnob);

    addAndMakeVisible(envDecayKnob);
    addAndMakeVisible(envReleaseKnob);
    addAndMakeVisible(velocitySensitivityKnob);

    addAndMakeVisible(hardnessKnob);
    addAndMakeVisible(velocityToHardnessKnob);

    addAndMakeVisible(mufflingFilterKnob);
    addAndMakeVisible(velocityToMufflingKnob);

    addChildComponent(tremoloKnob);
    addChildComponent(autopanKnob);
    addChildComponent(lfoRateKnob);

    addAndMakeVisible(trebleBoostKnob);
    addAndMakeVisible(overdriveKnob);
    addAndMakeVisible(stereoWidthKnob);

    addAndMakeVisible(reverbSizeKnob);
    addAndMakeVisible(reverbDampKnob);
    addAndMakeVisible(reverbMixKnob);

    addAndMakeVisible(outputLevelKnob);

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

    drawGroup(g, "Tuning", 40, 110, 270);
    drawGroup(g, "Envelope", 330, 110, 270);
    drawGroup(g, "Piano", 620, 110, 270);
    //drawGroup(g, "E-Piano", 620, 110, 270);

    drawGroup(g, "Hardness", 25, 300, 180);
    drawGroup(g, "FX", 225, 300, 270);
    drawGroup(g, "Reverb", 515, 300, 270);
    drawGroup(g, "Out", 805, 300, 105);

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
    g.fillRect(x + 10, y + 14, offset - 15, 2);
    g.fillRect(x + width - (offset - 5), y + 14, offset - 15, 2);

    //g.setColour(juce::Colours::yellow);
    //g.drawRect(x, y, width, 30);
}

void EditorView::resized()
{
    fineTuningKnob.setTopLeftPosition(40, 160);
    randomDetuningKnob.setTopLeftPosition(fineTuningKnob.getRight(), fineTuningKnob.getY());
    stretchTuningKnob.setTopLeftPosition(randomDetuningKnob.getRight(), randomDetuningKnob.getY());

    envDecayKnob.setTopLeftPosition(330, 160);
    envReleaseKnob.setTopLeftPosition(envDecayKnob.getRight(), envDecayKnob.getY());
    velocitySensitivityKnob.setTopLeftPosition(envReleaseKnob.getRight(), envReleaseKnob.getY());

    mufflingFilterKnob.setTopLeftPosition(665, 160);
    velocityToMufflingKnob.setTopLeftPosition(mufflingFilterKnob.getRight(), mufflingFilterKnob.getY());

    tremoloKnob.setTopLeftPosition(620, 160);
    autopanKnob.setTopLeftPosition(tremoloKnob.getRight(), tremoloKnob.getY());
    lfoRateKnob.setTopLeftPosition(autopanKnob.getRight(), autopanKnob.getY());

    hardnessKnob.setTopLeftPosition(25, 350);
    velocityToHardnessKnob.setTopLeftPosition(hardnessKnob.getRight(), hardnessKnob.getY());

    trebleBoostKnob.setTopLeftPosition(225, 350);
    overdriveKnob.setTopLeftPosition(trebleBoostKnob.getRight(), trebleBoostKnob.getY());
    stereoWidthKnob.setTopLeftPosition(overdriveKnob.getRight(), overdriveKnob.getY());

    reverbSizeKnob.setTopLeftPosition(515, 350);
    reverbDampKnob.setTopLeftPosition(reverbSizeKnob.getRight(), reverbSizeKnob.getY());
    reverbMixKnob.setTopLeftPosition(reverbDampKnob.getRight(), reverbDampKnob.getY());

    outputLevelKnob.setTopLeftPosition(810, 350);

    keyboardComponent.setBounds(0, defaultHeight - 80, defaultWidth + 1, 80);
}

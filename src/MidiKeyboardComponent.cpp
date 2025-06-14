#include "MidiKeyboardComponent.h"
#include "LookAndFeel.h"

MidiKeyboardComponent::MidiKeyboardComponent(juce::MidiKeyboardState& state,
                                             juce::MidiKeyboardComponent::Orientation orientation)
    : juce::MidiKeyboardComponent(state, orientation)
{
    setAvailableRange(21, 108);
    setKeyWidth(18);
    setBlackNoteLengthProportion(0.66667f);
    setBlackNoteWidthProportion(0.66667f);
    setScrollButtonsVisible(false);
    setColour(shadowColourId, juce::Colour(0x4c000000));
    setColour(textLabelColourId, juce::Colour(0xff808080));
    setColour(keyDownOverlayColourId, Colors::accent2);
    setColour(mouseOverKeyOverlayColourId, Colors::accent2);
}

void MidiKeyboardComponent::drawWhiteNote(
    int midiNoteNumber,
    juce::Graphics& g,
    juce::Rectangle<float> area,
    bool isDown,
    bool isOver,
    [[maybe_unused]] juce::Colour lineColour,
    juce::Colour textColour)
{
    g.setColour(juce::Colour(0xff1d1c1a));
    g.fillRect(area);

    auto c = juce::Colour(0xffffffed);

    if (isOver) { c = findColour(mouseOverKeyOverlayColourId).brighter(); }
    if (isDown) { c = findColour(keyDownOverlayColourId); }

    auto x = area.getX();
    auto y = area.getY();
    auto width = area.getWidth();
    auto height = area.getHeight();

    juce::Path path;
    path.addRoundedRectangle(x, y, width - 1.0f, height, 2.0f, 2.0f, false, false, true, true);

    g.setColour(c);
    g.fillPath(path);

    auto text = getWhiteNoteText(midiNoteNumber);
    if (text.isNotEmpty()) {
        g.setColour(textColour);
        g.setFont(juce::FontOptions(12.0f));
        g.drawText(text, area.withTrimmedBottom(2.0f), juce::Justification::centredBottom, false);
    }

    auto shadowColor = findColour(shadowColourId);
    g.setGradientFill({ shadowColor, {}, shadowColor.withAlpha(0.0f), { 0.0f, 8.0f }, false });
    g.fillRect(x, y, width, 8.0f);
}

void MidiKeyboardComponent::drawBlackNote(
    [[maybe_unused]] int midiNoteNumber,
    juce::Graphics& g,
    juce::Rectangle<float> area,
    bool isDown,
    bool isOver,
    [[maybe_unused]] juce::Colour noteFillColour)
{
    juce::Colour c;
    if (isDown) {
        c = findColour(keyDownOverlayColourId).darker(0.6f);
    } else if (isOver) {
        c = findColour(mouseOverKeyOverlayColourId).darker();
    } else {
        c = juce::Colour(0xff1d1c1a);
    }

    area = area.toNearestIntEdges().toFloat();

    auto x = area.getX();
    auto y = area.getY();
    auto width = area.getWidth();
    auto height = area.getHeight();

    juce::Path path;
    path.addRoundedRectangle(x, y, width, height, 2.0f, 2.0f, false, false, true, true);

    g.setColour(c);
    g.fillPath(path);

    if (isDown) {
        c = findColour(keyDownOverlayColourId);
    } else if (isOver) {
        c = findColour(mouseOverKeyOverlayColourId).brighter();
    } else {
        c = juce::Colour(0xff1d1c1a).brighter();
    }
    g.setColour(c);

    auto sideIndent = 1.5f / 12.0f;
    auto topIndent = 7.0f / 8.0f;
    g.fillRect(area.reduced(width * sideIndent, 0).removeFromTop(height * topIndent));
}

juce::String MidiKeyboardComponent::getWhiteNoteText(int midiNoteNumber)
{
    if (midiNoteNumber == 60) {
        return "C";
    }
    return {};
}

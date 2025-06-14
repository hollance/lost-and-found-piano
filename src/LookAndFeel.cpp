#include "LookAndFeel.h"
#include "BinaryData.h"

namespace Fonts
{
static const juce::Typeface::Ptr typeface = juce::Typeface::createSystemTypefaceFor(
    BinaryData::GoudyBookletter1911_otf, BinaryData::GoudyBookletter1911_otfSize);

juce::Font getFont(float height)
{
    return juce::Font(juce::FontOptions(typeface).withHeight(height));
}

}  // namespace Fonts

LookAndFeel::LookAndFeel()
{
    knobSVG = juce::Drawable::createFromImageData(BinaryData::Knob_svg, BinaryData::Knob_svgSize);
}

void LookAndFeel::drawCornerResizer(
    juce::Graphics& g,
    int w,
    int h,
    [[maybe_unused]] bool isMouseOver,
    [[maybe_unused]] bool isMouseDragging)
{
    juce::Path path;
    path.startNewSubPath(4.0f, h - 3.0f);
    path.lineTo(w - 3.0f, h - 3.0f);
    path.lineTo(w - 3.0f, 4.0f);
    path.closeSubPath();

    g.setColour(juce::Colour(0xff1d1c1a).brighter());
    g.fillPath(path);
}

void LookAndFeel::drawRotarySlider(
     juce::Graphics& g,
     int x,
     int y,
     int width,
     [[maybe_unused]] int height,
     float sliderPos,
     float rotaryStartAngle,
     float rotaryEndAngle,
     [[maybe_unused]] juce::Slider& slider)
{
    auto knobRect = juce::Rectangle<float>(x + (width - 60.0f) / 2.0f, y, 60.0f, 60.0f);
    auto shadowRect = juce::Rectangle<float>(x + (width - 48.0f) / 2.0f, y + 12.0f, 48.0f, 48.0f);

    auto path = juce::Path();
    path.addEllipse(shadowRect);
    dropShadow.drawForPath(g, path);

    knobSVG->drawWithin(g, knobRect, juce::RectanglePlacement::stretchToFit, 1.0f);

    /*
    float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    float dialRadius = 30.0f - 10.0f;

    float dialX = knobRect.getCentreX() + dialRadius * std::sin(angle);
    float dialY = knobRect.getCentreY() - dialRadius * std::cos(angle);

    g.setColour(juce::Colour(0xff0d2629));
    g.fillEllipse(dialX - 3, dialY - 4, 6, 6);

    g.setColour(Colors::accent2);
    g.fillEllipse(dialX - 3, dialY - 3, 6, 6);
    */

    g.saveState();

    float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto transform = juce::AffineTransform::rotation(angle).translated(knobRect.getCentreX(), knobRect.getCentreY());
    g.addTransform(transform);

    g.setColour(juce::Colour(0xff0d2629));
    g.fillRoundedRectangle(-2.0f, 7.0f - knobRect.getCentreY(), 4.0f, 12.0f, 2.0f);

    g.setColour(Colors::accent2);
    g.fillRoundedRectangle(-2.0f, 8.0f - knobRect.getCentreY(), 4.0f, 12.0f, 2.0f);

    g.restoreState();

    /*
    g.setColour(juce::Colours::yellow);
    g.drawRect(x, y, width, height);
    g.drawEllipse(knobRect, 1);
    g.fillEllipse(knobRect.getCentreX() - 3, knobRect.getCentreY() - 3, 6, 6);
    */
}

#pragma once

#include <JuceHeader.h>

namespace Colors {

const juce::Colour background { 0xff1f252a };
const juce::Colour accent1 { 0xffde4949 };
const juce::Colour accent2 { 0xff93de49 };
const juce::Colour text { 0xffc8c0c0 };

const juce::Colour listBackground { 0xff000000 };
const juce::Colour listSelected { 0xff93de49 };
const juce::Colour textSelected { 0xff1f252a };

}  // namespace Colors

namespace Fonts {

juce::Font getRegularFont(float height = 24.0f);
juce::Font getMonoFont(float height = 20.0f);

}  // namespace Fonts

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    LookAndFeel();

    void drawCornerResizer(juce::Graphics&, int, int, bool, bool) override;
    void drawRotarySlider(juce::Graphics&, int, int, int, int, float, float, float, juce::Slider&) override;

    void drawButtonText(juce::Graphics&, juce::TextButton&, bool, bool) override;
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;

private:
    std::unique_ptr<juce::Drawable> knobSVG;
    juce::DropShadow dropShadow { juce::Colour(0xff0a0c0b), 16, { 0, 4 } };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LookAndFeel)
};

class PresetsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    PresetsLookAndFeel(juce::Justification justification);

    void drawButtonText(juce::Graphics&, juce::TextButton&, bool, bool) override;
    void drawButtonBackground(juce::Graphics&, juce::Button&, const juce::Colour&, bool, bool) override;

    bool areScrollbarButtonsVisible() override;
    void drawScrollbarButton(juce::Graphics&, juce::ScrollBar&, int, int, int, bool, bool, bool) override;
    void drawScrollbar(juce::Graphics&, juce::ScrollBar&, int, int, int, int, bool, int, int, bool, bool) override;
    int getMinimumScrollbarThumbSize(juce::ScrollBar&) override;
    int getDefaultScrollbarWidth() override;

private:
    juce::Justification justification;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetsLookAndFeel)
};

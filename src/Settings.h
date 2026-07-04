#pragma once

#include <JuceHeader.h>

// The width is 52 white piano keys times 18 pixels, minus one pixel.
constexpr int defaultWidth = 935;
constexpr int defaultHeight = 500;

class Settings final
{
public:
    Settings();
    ~Settings();

    void reload();

    void setWindowWidth(int width);
    int getWindowWidth() const;

private:
    juce::ApplicationProperties applicationProperties;
    juce::PropertiesFile* settings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Settings)
};

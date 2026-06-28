#pragma once

#include "gui/LookAndFeel.h"
#include <JuceHeader.h>

class SelectionBar : public juce::Component
{
public:
    SelectionBar()
    {
        setInterceptsMouseClicks(false, false);
    }

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        juce::Path path;
        path.addRoundedRectangle(bounds.getX(), bounds.getBottom() - 5.0f, bounds.getWidth(),
                                 5.0f, 3, 3, true, true, false, false);
        g.setColour(Colors::accent2);
        g.fillPath(path);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SelectionBar)
};

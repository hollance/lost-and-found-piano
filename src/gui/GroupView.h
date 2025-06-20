#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"

class GroupView : public juce::Component
{
public:
    GroupView(const juce::String& name) : groupName(name) { }

    void paint(juce::Graphics& g) override
    {
        auto font = Fonts::getRegularFont();
        auto textWidth = int(std::ceil(juce::TextLayout::getStringWidth(font, groupName)));
        auto offset = (getWidth() - textWidth) / 2;

        g.setColour(Colors::text);
        g.setFont(Fonts::getRegularFont());
        g.drawSingleLineText(groupName, offset, 22);

        g.setColour(Colors::text.withAlpha(0.5f));
        g.fillRect(10, 14, offset - 15, 2);
        g.fillRect(getWidth() - (offset - 5), 14, offset - 15, 2);

        //g.setColour(juce::Colours::yellow);
        //g.drawRect(getLocalBounds());
    }

private:
    juce::String groupName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GroupView)
};

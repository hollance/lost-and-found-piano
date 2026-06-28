#include "gui/RadioButtonAttachment.h"

RadioButtonAttachment::RadioButtonAttachment(juce::AudioProcessorValueTreeState& stateToUse,
                                             const juce::String& parameterID,
                                             const std::vector<juce::Button*>& paramButtons)
    : buttons(paramButtons),
      parameter(*stateToUse.getParameter(parameterID)),
      attachment(parameter, [this] (float f) { setValue(f); })
{
    sendInitialUpdate();
    for (auto* button : buttons) {
        button->setToggleable(true);
        button->addListener(this);
    }
}

RadioButtonAttachment::~RadioButtonAttachment()
{
    for (auto* button : buttons) {
        button->removeListener(this);
    }
}

void RadioButtonAttachment::sendInitialUpdate()
{
    attachment.sendInitialUpdate();
}

void RadioButtonAttachment::setValue(float newValue)
{
    const auto normValue = parameter.convertTo0to1(newValue);
    const auto index = juce::roundToInt(normValue * float(buttons.size() - 1));

    const juce::ScopedValueSetter<bool> svs(ignoreCallbacks, true);

    // Note: Using radioGroupId would have been simpler but doesn't work
    // when the buttons are not in the same parent component.
    for (auto* button : buttons) {
        button->setToggleState(button == buttons[size_t(index)], juce::sendNotificationSync);
    }
}

void RadioButtonAttachment::buttonClicked(juce::Button* button)
{
    if (ignoreCallbacks) { return; }

    if (!button->getToggleState()) {
         button->setToggleState(true, juce::dontSendNotification);
    
        auto it = std::find(buttons.begin(), buttons.end(), button);
        if (it != buttons.end()) {
            int buttonIndex = static_cast<int>(std::distance(buttons.begin(), it));
            attachment.setValueAsCompleteGesture(float(buttonIndex));
        }
    }
}

#include "RotaryKnob.h"

RotaryKnob::RotaryKnob(const juce::String& text,
                       juce::AudioProcessorValueTreeState& apvts,
                       const juce::ParameterID& parameterID)
    : attachment(apvts, parameterID.getParamID(), slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setBounds(0, 0, 90, 95);
    addAndMakeVisible(slider);

    label.setText(text, juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::horizontallyCentred);
    label.setColour(juce::Label::textColourId, Colors::text);
    label.setFont(Fonts::getFont());
    label.setBounds(0, 70, 90, 25);
    addAndMakeVisible(label);

    setSize(90, 95);

    setLookAndFeel(&lf);

    float pi = juce::MathConstants<float>::pi;
    slider.setRotaryParameters(1.25f * pi, 2.75f * pi, true);
}

RotaryKnob::~RotaryKnob()
{
    setLookAndFeel(nullptr);
}

void RotaryKnob::paint([[maybe_unused]] juce::Graphics& g)
{
//    g.setColour(juce::Colours::purple);
//    g.drawRect(getLocalBounds());
//    g.setColour(juce::Colours::teal);
//    g.drawRect(label.getBounds());
}

void RotaryKnob::resized()
{
}

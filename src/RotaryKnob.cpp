#include "RotaryKnob.h"

RotaryKnob::RotaryKnob(const juce::String& text,
                       juce::AudioProcessorValueTreeState& apvts,
                       const juce::ParameterID& parameterID)
    : knobName(text), attachment(apvts, parameterID.getParamID(), slider)
{
    float pi = juce::MathConstants<float>::pi;
    slider.setRotaryParameters(1.25f * pi, 2.75f * pi, true);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    slider.setBounds(0, 0, 90, 95);
    addAndMakeVisible(slider);

    nameLabel.setText(knobName, juce::NotificationType::dontSendNotification);
    nameLabel.setJustificationType(juce::Justification::horizontallyCentred);
    nameLabel.setColour(juce::Label::textColourId, Colors::text);
    nameLabel.setFont(Fonts::getRegularFont());
    nameLabel.setBounds(0, 70, 90, 25);
    addAndMakeVisible(nameLabel);

    valueLabel.setText("", juce::NotificationType::dontSendNotification);
    valueLabel.setJustificationType(juce::Justification::horizontallyCentred);
    valueLabel.setColour(juce::Label::textColourId, Colors::text);
    valueLabel.setFont(Fonts::getMonoFont());
    valueLabel.setBounds(0, 70, 90, 25);
    addChildComponent(valueLabel);

    setLookAndFeel(&lf);

    setSize(90, 95);

    slider.onDragStart = [this]()
    {
        showValueLabel();
        updateValueLabel();
        stopTimer();
    };

    slider.onValueChange = [this]()
    {
        updateValueLabel();
    };

    slider.onDragEnd = [this]()
    {
        startTimer(500.0f);
    };
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

void RotaryKnob::timerCallback()
{
    hideValueLabel();
    stopTimer();
}

void RotaryKnob::showValueLabel()
{
    animatorUpdater.removeAnimator(animator);

    nameLabel.setVisible(false);
    nameLabel.setAlpha(1.0f);

    valueLabel.setVisible(true);
    valueLabel.setAlpha(1.0f);
}

void RotaryKnob::hideValueLabel()
{
    nameLabel.setVisible(true);

    animatorUpdater.addAnimator(animator, [this]
    {
        animatorUpdater.removeAnimator(animator);
    });

    animator.start();
}

void RotaryKnob::updateValueLabel()
{
    valueLabel.setText(slider.getTextFromValue(slider.getValue()),
                       juce::NotificationType::dontSendNotification);
}

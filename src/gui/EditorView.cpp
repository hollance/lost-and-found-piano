#include "EditorView.h"

EditorView::EditorView(AudioProcessor& p) :
    audioProcessor(p),
    instrumentAttachment(p.apvts, ParameterID::instrument.getParamID(), { &acousticButton, &electricButton }),
    keyboardComponent(p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    setOpaque(true);

    acousticButton.setButtonText("Acoustic");
    acousticButton.setLookAndFeel(&lf);
    addAndMakeVisible(acousticButton);

    electricButton.setButtonText("Electric");
    electricButton.setLookAndFeel(&lf);
    addAndMakeVisible(electricButton);

    addAndMakeVisible(selectionBar);

    addAndMakeVisible(tuningGroup);
    tuningGroup.addAndMakeVisible(fineTuningKnob);
    tuningGroup.addAndMakeVisible(randomDetuningKnob);
    tuningGroup.addAndMakeVisible(stretchTuningKnob);

    addAndMakeVisible(envelopeGroup);
    envelopeGroup.addAndMakeVisible(envDecayKnob);
    envelopeGroup.addAndMakeVisible(envReleaseKnob);
    envelopeGroup.addAndMakeVisible(velocitySensitivityKnob);

    addAndMakeVisible(filterGroup);
    filterGroup.addAndMakeVisible(mufflingFilterKnob);
    filterGroup.addAndMakeVisible(velocityToMufflingKnob);

    addAndMakeVisible(modulationGroup);
    modulationGroup.addAndMakeVisible(depthKnob);
    modulationGroup.addAndMakeVisible(lfoRateKnob);

    addAndMakeVisible(hardnessGroup);
    hardnessGroup.addAndMakeVisible(hardnessKnob);
    hardnessGroup.addAndMakeVisible(velocityToHardnessKnob);

    addAndMakeVisible(effectsGroup);
    effectsGroup.addAndMakeVisible(trebleBoostKnob);
    effectsGroup.addAndMakeVisible(overdriveKnob);
    effectsGroup.addAndMakeVisible(stereoWidthKnob);

    addAndMakeVisible(reverbGroup);
    reverbGroup.addAndMakeVisible(reverbSizeKnob);
    reverbGroup.addAndMakeVisible(reverbDampKnob);
    reverbGroup.addAndMakeVisible(reverbMixKnob);

    addAndMakeVisible(outputGroup);
    outputGroup.addAndMakeVisible(outputLevelKnob);

    addAndMakeVisible(keyboardComponent);

    updateUI();

    animatorUpdater.addAnimator(animator);

    audioProcessor.params.instrumentParam->addListener(this);
}

EditorView::~EditorView()
{
    audioProcessor.params.instrumentParam->removeListener(this);
}

void EditorView::paint(juce::Graphics& g)
{
    g.fillAll(Colors::background);

    g.setColour(juce::Colour(0xff000000));
    g.fillRect(0, 0, defaultWidth, 38);
    g.setColour(Colors::accent1);
    g.fillRect(0, 38, defaultWidth, 2);

    g.setFont(Fonts::getRegularFont(32.0f));
    g.setColour(juce::Colours::white);
    g.drawSingleLineText("Lost & Found", 20, 27);
    g.setColour(Colors::accent1);
    g.drawSingleLineText("Piano", 166, 27);

    g.setColour(Colors::accent1);
    g.fillRect(0, defaultHeight - 84, defaultWidth, 4);
    g.setColour(juce::Colour(0xff000000));
    g.fillRect(0, defaultHeight - 80, defaultWidth, 90);
}

void EditorView::resized()
{
    acousticButton.setBounds(365, 0, 100, 40);
    electricButton.setBounds(470, 0, 100, 40);

    selectionBar.setBounds(acousticButton.getToggleState() ? acousticButton.getBounds()
                                                           : electricButton.getBounds());

    tuningGroup.setBounds(40, 65, 270, 145);
    fineTuningKnob.setTopLeftPosition(0, 50);
    randomDetuningKnob.setTopLeftPosition(fineTuningKnob.getRight(), fineTuningKnob.getY());
    stretchTuningKnob.setTopLeftPosition(randomDetuningKnob.getRight(), randomDetuningKnob.getY());

    envelopeGroup.setBounds(330, 65, 270, 145);
    envDecayKnob.setTopLeftPosition(0, 50);
    envReleaseKnob.setTopLeftPosition(envDecayKnob.getRight(), envDecayKnob.getY());
    velocitySensitivityKnob.setTopLeftPosition(envReleaseKnob.getRight(), envReleaseKnob.getY());

    effectsGroup.setBounds(620, 65, 270, 145);
    trebleBoostKnob.setTopLeftPosition(0, 50);
    overdriveKnob.setTopLeftPosition(trebleBoostKnob.getRight(), trebleBoostKnob.getY());
    stereoWidthKnob.setTopLeftPosition(overdriveKnob.getRight(), overdriveKnob.getY());

    filterGroup.setBounds(40, 240, 200, 145);
    mufflingFilterKnob.setTopLeftPosition(10, 50);
    velocityToMufflingKnob.setTopLeftPosition(mufflingFilterKnob.getRight(), mufflingFilterKnob.getY());

    modulationGroup.setBounds(40, 240, 200, 145);
    depthKnob.setTopLeftPosition(10, 50);
    lfoRateKnob.setTopLeftPosition(depthKnob.getRight(), depthKnob.getY());

    hardnessGroup.setBounds(260, 240, 200, 145);
    hardnessKnob.setTopLeftPosition(10, 50);
    velocityToHardnessKnob.setTopLeftPosition(hardnessKnob.getRight(), hardnessKnob.getY());

    reverbGroup.setBounds(480, 240, 270, 145);
    reverbSizeKnob.setTopLeftPosition(0, 50);
    reverbDampKnob.setTopLeftPosition(reverbSizeKnob.getRight(), reverbSizeKnob.getY());
    reverbMixKnob.setTopLeftPosition(reverbDampKnob.getRight(), reverbDampKnob.getY());

    outputGroup.setBounds(770, 240, 120, 145);
    outputLevelKnob.setTopLeftPosition(15, 50);

    keyboardComponent.setBounds(0, defaultHeight - 80, defaultWidth + 1, 80);
}

void EditorView::parameterValueChanged(int, float)
{
    selectionBar.setBounds(audioProcessor.params.isAcoustic() ? acousticButton.getBounds()
                                                              : electricButton.getBounds());
    selectionBar.setTransform({});

    filterGroup.setVisible(audioProcessor.params.isAcoustic());
    modulationGroup.setVisible(!filterGroup.isVisible());

    filterGroup.setAlpha(0.0f);
    modulationGroup.setAlpha(0.0f);

    animator.start();
}

void EditorView::updateUI()
{
    filterGroup.setVisible(audioProcessor.params.isAcoustic());
    modulationGroup.setVisible(!filterGroup.isVisible());
}

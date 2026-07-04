#pragma once

#include "Parameters.h"
#include "Settings.h"
#include "dsp/mdaAmbience.h"
#include "dsp/mdaEPiano.h"
#include "dsp/mdaPiano.h"
#include <JuceHeader.h>

class AudioProcessor : public juce::AudioProcessor
{
public:
    AudioProcessor();

    bool hasEditor() const override { return true; }
    const juce::String getName() const override { return "Piano"; }
    bool acceptsMidi() const override { return true; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override { }
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override { }

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void reset() override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    juce::AudioProcessorEditor* createEditor() override;

    juce::AudioProcessorValueTreeState apvts;
    juce::MidiKeyboardState keyboardState;

    Parameters params;
    Settings settings;

private:
    MDAPiano acousticPiano { params };
    MDAEPiano electricPiano { params };
    MDAAmbience reverb { params };
    int lastInstrument = -1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioProcessor)
};

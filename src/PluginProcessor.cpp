#include "PluginProcessor.h"
#include "PluginEditor.h"

AudioProcessor::AudioProcessor() :
    juce::AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "Parameters", Parameters::createParameterLayout()),
    params(apvts)
{
    // do nothing
}

bool AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void AudioProcessor::prepareToPlay(double sampleRate, [[maybe_unused]] int maximumBlockSize)
{
    float synthRate = float(sampleRate);
    params.prepareToPlay(synthRate);
    //acousticPiano.prepareToPlay(sampleRate);
    electricPiano.prepareToPlay(sampleRate);
    reset();
}

void AudioProcessor::reset()
{
    params.reset();
    //acousticPiano.reset();
    electricPiano.reset();
}

void AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    params.update();
    buffer.clear();

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

//    acousticPiano.processBlock(buffer, midiMessages);
    electricPiano.processBlock(buffer, midiMessages);

    // TODO: apply output gain + fixed -12 dB

    midiMessages.clear();
}

void AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    copyXmlToBinary(*apvts.copyState().createXml(), destData);
}

void AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new AudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessor();
}

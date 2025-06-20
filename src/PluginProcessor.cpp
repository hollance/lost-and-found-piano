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
    acousticPiano.prepareToPlay(sampleRate);
    electricPiano.prepareToPlay(sampleRate);
    reverb.prepareToPlay(sampleRate);
    reset();
}

void AudioProcessor::releaseResources()
{
    reverb.releaseResources();
}

void AudioProcessor::reset()
{
    params.reset();
    reverb.reset();
    lastInstrument = -1;
}

void AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    params.update();
    buffer.clear();

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    // Render the active instrument, or switch instruments if necessary.
    int instrument = params.instrumentParam->getIndex();
    if (instrument == 0) {
        if (lastInstrument != instrument) {
            acousticPiano.reset();
        }
        acousticPiano.processBlock(buffer, midiMessages);
    } else {
        if (lastInstrument != instrument) {
            electricPiano.reset();
        }
        electricPiano.processBlock(buffer, midiMessages);
    }
    lastInstrument = instrument;

    reverb.processBlock(buffer);

    float *out0 = buffer.getWritePointer(0);
    float *out1 = buffer.getWritePointer(1);

    // Apply output gain and a fixed gain of -12 dB as the samples are quite loud.
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        float gain = params.outputLevelSmoother.getNextValue() * 0.25f;
        out0[sample] *= gain;
        out1[sample] *= gain;
    }

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

#include "PluginEditor.h"
#include "PluginProcessor.h"

AudioProcessor::AudioProcessor() :
    juce::AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    apvts(*this, nullptr, "Parameters", Parameters::createParameterLayout()),
    params(apvts)
{
    loadPresetAt(0);
    apvts.state.addListener(this);
}

AudioProcessor::~AudioProcessor()
{
    apvts.state.removeListener(this);
}

bool AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void AudioProcessor::prepareToPlay(double sampleRate, [[maybe_unused]] int maximumBlockSize)
{
    auto synthRate = float(sampleRate);
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

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        float gain = params.outputLevelSmoother.getNextValue();
        out0[sample] *= gain;
        out1[sample] *= gain;
    }

    midiMessages.clear();
}

void AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto xml = apvts.copyState().createXml();
    xml->addChildElement(presetManager.saveToXml());
    copyXmlToBinary(*xml, destData);
}

void AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr && xml->hasTagName(apvts.state.getType())) {
        presetManager.loadFromXml(xml.get());
        xml->deleteAllChildElementsWithTagName("PRESETS");
        apvts.replaceState(juce::ValueTree::fromXml(*xml));
    }

    juce::MessageManager::callAsync([this] { updateUI(); });
}

void AudioProcessor::loadPresetAt(int index)
{
    loadPreset(presetManager.loadPresetAt(index));
}

void AudioProcessor::prevPreset()
{
    loadPreset(presetManager.loadPrevPreset());
}

void AudioProcessor::nextPreset()
{
    loadPreset(presetManager.loadNextPreset());
}

void AudioProcessor::loadPreset(std::unique_ptr<juce::XmlElement> xml)
{
    if (xml == nullptr) {
        return;
    }

    apvts.state.removeListener(this);

    if (auto* parametersXml = xml->getChildByName(apvts.state.getType())) {
        apvts.replaceState(juce::ValueTree::fromXml(*parametersXml));
    }

    apvts.state.addListener(this);
}

void AudioProcessor::updateUI()
{
    if (auto* editor = dynamic_cast<AudioProcessorEditor*>(getActiveEditor())) {
        editor->updatePresetNameButton();
    }
}

void AudioProcessor::savePreset(juce::File& file)
{
    auto xml = std::make_unique<juce::XmlElement>("PRESET");
    xml->addChildElement(apvts.copyState().createXml().release());
    presetManager.savePreset(file, std::move(xml));
}

void AudioProcessor::valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&)
{
    juce::MessageManager::callAsync(
        [this]
        {
            presetManager.makeDirty();
            updateUI();
        });
}

juce::AudioProcessorEditor* AudioProcessor::createEditor()
{
    return new AudioProcessorEditor(*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioProcessor();
}

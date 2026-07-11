#pragma once

#include <JuceHeader.h>

juce::File getLibraryDir();
juce::File getUserPresetsDir();

struct Preset
{
    Preset() = default;

    bool isFactory() const
    {
        return xmlString.isNotEmpty();
    }

    juce::String name = "Unnamed";
    juce::String category = "Default";
    juce::String xmlString = "";  // factory presets only

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Preset)
};

class PresetManager
{
public:
    PresetManager();

    void loadFromXml(juce::XmlElement* xml);
    juce::XmlElement* saveToXml() const;

    int getNumPresets() const
    {
        return int(presets.size());
    }

    Preset* getPresetAt(int index)
    {
        return presets[size_t(index)].get();
    }

    std::unique_ptr<juce::XmlElement> loadPresetAt(int index);
    std::unique_ptr<juce::XmlElement> loadPrevPreset();
    std::unique_ptr<juce::XmlElement> loadNextPreset();

    void savePreset(juce::File& outFile, std::unique_ptr<juce::XmlElement> xml);

    Preset* getActivePreset();
    juce::String getActivePresetName();
    juce::String getActivePresetDisplayText();

    void makeDirty();

private:
    void loadFactoryPresets();
    void loadUserPresets();
    int indexOfPresetNamed(const juce::String& name);

    bool dirty = false;
    int activeIndex = -1;
    std::optional<juce::String> currentPresetName;

    std::vector<std::unique_ptr<Preset>> presets;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};

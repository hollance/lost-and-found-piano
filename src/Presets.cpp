#include "Presets.h"
#include "FactoryPresets.h"

juce::File getLibraryDir()
{
    juce::File dir = juce::File::getSpecialLocation(juce::File::SpecialLocationType::userApplicationDataDirectory);
#ifdef JUCE_MAC
    dir = dir.getChildFile("Application Support");
#endif
    return dir.getChildFile("Lost N Found").getChildFile("Piano");
}

juce::File getUserPresetsDir()
{
    return getLibraryDir().getChildFile("User Presets");
}

PresetManager::PresetManager()
{
    loadFactoryPresets();
    loadUserPresets();

    /*
    for (int i = 0; i < getNumPresets(); ++i) {
        auto* preset = getPresetAt(i);
        DBG("preset " << i << " name " << preset->name);
    }
    */
}

void PresetManager::loadFactoryPresets()
{
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Default Piano";
        preset->xmlString = presets::mdaPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Plain Piano";
        preset->xmlString = presets::plainPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Compressed Piano";
        preset->xmlString = presets::compressedPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Dance Piano";
        preset->xmlString = presets::dancePiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Concert Piano";
        preset->xmlString = presets::concertPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Dark Piano";
        preset->xmlString = presets::darkPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "School Piano";
        preset->xmlString = presets::schoolPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Acoustic";
        preset->name = "Broken Piano";
        preset->xmlString = presets::brokenPiano;
        presets.emplace_back(preset);
    }

    {
        auto* preset = new Preset;
        preset->category = "Electric";
        preset->name = "Default EPiano";
        preset->xmlString = presets::defaultEPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Electric";
        preset->name = "Bright EPiano";
        preset->xmlString = presets::brightEPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Electric";
        preset->name = "Mellow EPiano";
        preset->xmlString = presets::mellowEPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Electric";
        preset->name = "Autopan EPiano";
        preset->xmlString = presets::autopanEPiano;
        presets.emplace_back(preset);
    }
    {
        auto* preset = new Preset;
        preset->category = "Electric";
        preset->name = "Tremolo EPiano";
        preset->xmlString = presets::tremoloEPiano;
        presets.emplace_back(preset);
    }
}

void PresetManager::loadUserPresets()
{
    auto presetsDir = getUserPresetsDir();
    std::vector<juce::String> names;

    for (const auto& entry : juce::RangedDirectoryIterator {presetsDir, false, "*.xml"}) {
        const auto file = entry.getFile();
        if (file.existsAsFile()) {
            names.push_back(file.getFileNameWithoutExtension());
        }
    }

    std::sort(names.begin(), names.end(),
        [&](const juce::String& a, const juce::String& b) -> bool const {
            return a.compareNatural(b, false) < 0;
        });

    for (auto& name : names) {
        auto* preset = new Preset;
        preset->name = name;
        preset->category = "User";
        presets.emplace_back(preset);
    }
}

void PresetManager::loadFromXml(juce::XmlElement* parentXml)
{
    if (auto* xml = parentXml->getChildByName("PRESETS")) {
        currentPresetName = xml->getStringAttribute("name", "Unknown Preset");
        if (currentPresetName.has_value()) {
            activeIndex = indexOfPresetNamed(*currentPresetName);
        } else {
            activeIndex = -1;
        }

        dirty = xml->getBoolAttribute("dirty", false);
        if (activeIndex == -1) {
            dirty = true;
        }
    }
}

juce::XmlElement* PresetManager::saveToXml() const
{
    auto* xml = new juce::XmlElement("PRESETS");
    if (currentPresetName.has_value()) {
        xml->setAttribute("name", *currentPresetName);
    } else {
        xml->setAttribute("name", "Unknown Preset");
    }
    xml->setAttribute("dirty", dirty);
    return xml;
}

std::unique_ptr<juce::XmlElement> PresetManager::loadPresetAt(int index)
{
    activeIndex = index;

    auto* preset = getActivePreset();
    if (preset == nullptr) {
        return nullptr;  // shouldn't happen
    }

    currentPresetName = preset->name;
    dirty = false;

    if (preset->isFactory()) {
        return juce::parseXML(preset->xmlString);
    }

    auto xmlString = getUserPresetsDir().getChildFile(preset->name + ".xml").loadFileAsString();
    auto result = juce::parseXML(xmlString);
    if (result == nullptr) {
        dirty = true;
    }
    return result;
}

std::unique_ptr<juce::XmlElement> PresetManager::loadPrevPreset()
{
    if (presets.empty()) {
        return nullptr;
    }

    activeIndex -= 1;
    if (activeIndex < 0) {
        activeIndex = getNumPresets() - 1;
    }

    return loadPresetAt(activeIndex);
}

std::unique_ptr<juce::XmlElement> PresetManager::loadNextPreset()
{
    if (presets.empty()) {
        return nullptr;
    }

    activeIndex += 1;
    if (activeIndex >= getNumPresets()) {
        activeIndex = 0;
    }

    return loadPresetAt(activeIndex);
}

void PresetManager::savePreset(juce::File& outFile, std::unique_ptr<juce::XmlElement> xml)
{
    xml->writeTo(outFile);

    auto* newPreset = new Preset;
    newPreset->name = outFile.getFileNameWithoutExtension();
    newPreset->category = "User";

    currentPresetName = newPreset->name;
    dirty = false;

    for (auto it = presets.begin(); it != presets.end(); ++it) {
        auto& other = *it;
        if (!other->isFactory()) {
            auto compare = other->name.compareNatural(newPreset->name);

            // Overwrite existing?
            if (compare == 0) {
                activeIndex = int(std::distance(presets.begin(), it));
                other.reset(newPreset);
                return;
            }

            // Insert sorted
            if (compare > 0) {
                activeIndex = int(std::distance(presets.begin(), it));
                presets.insert(it, std::unique_ptr<Preset>(newPreset));
                return;
            }
        }
    }
    activeIndex = int(presets.size());
    presets.emplace_back(newPreset);
}

Preset* PresetManager::getActivePreset()
{
    if (activeIndex == -1) {
        return nullptr;
    } else {
        return getPresetAt(activeIndex);
    }
}

juce::String PresetManager::getActivePresetName()
{
    if (currentPresetName.has_value()) {
        return *currentPresetName;
    }
    if (const auto* p = getActivePreset()) {
        return p->name;
    }
    return "";
}

juce::String PresetManager::getActivePresetDisplayText()
{
    juce::String text = getActivePresetName();
    if (text.isNotEmpty()) {
        if (dirty) {
            text = "*" + text;
        }
        return text;
    }
    return "";
}

int PresetManager::indexOfPresetNamed(const juce::String& name)
{
    for (int i = 0; i < getNumPresets(); ++i) {
        if (getPresetAt(i)->name == name) {
            return i;
        }
    }
    return -1;
}

void PresetManager::makeDirty()
{
    dirty = true;
}

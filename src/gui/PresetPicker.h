#pragma once

#include "Presets.h"
#include "gui/LookAndFeel.h"

class PresetListModel : public juce::ListBoxModel
{
public:
    PresetListModel(PresetManager& presetManager);

    void updateContent();

    int getNumRows() override;
    juce::String getNameForRow(int rowNumber) override;
    void listBoxItemClicked(int, const juce::MouseEvent&) override;
    void paintListBoxItem(int, juce::Graphics&, int, int, bool) override;

    std::function<void(int)> onPresetSelected = nullptr;

private:
    struct Item
    {
        juce::String category = "";
        Preset* preset = nullptr;
        int presetIndex = -1;
    };
    std::vector<Item> items;

    PresetManager& presetManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetListModel)
};

class PresetPicker : public juce::Component
{
public:
    PresetPicker(PresetManager& presetManager);
    ~PresetPicker() override;

    void paint(juce::Graphics& g) override;
    void resized() final;

    void toggleVisibility();
    void show();
    void hide();
    bool isHidden() const;

    std::function<void(int)> onPresetSelected = nullptr;

private:
    PresetManager& presetManager;

    bool hidden = true;

    PresetsLookAndFeel lf { juce::Justification::centred };

    PresetListModel model;
    juce::ListBox list;

    juce::VBlankAnimatorUpdater animatorUpdater {this};

    juce::Animator showAnimator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseOut())
        .withDurationMs(200.0)
        .withValueChangedCallback([this](auto value)
        {
            float dx = (1.0f - value) * float(getWidth());
            setTransform(juce::AffineTransform::translation(dx, 0.0f));
            setVisible(true);
        })
        .withOnCompleteCallback([this]()
        {
            setTransform({});
            hidden = false;
        })
        .build();

    juce::Animator hideAnimator = juce::ValueAnimatorBuilder {}
        .withEasing(juce::Easings::createEaseIn())
        .withDurationMs(200.0)
        .withValueChangedCallback([this](auto value)
        {
            float dx = value * float(getWidth());
            setTransform(juce::AffineTransform::translation(dx, 0.0f));
        })
        .withOnCompleteCallback([this]()
        {
            setTransform({});
            setVisible(false);
        })
        .build();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetPicker)
};

#include "gui/PresetPicker.h"

PresetListModel::PresetListModel(PresetManager& manager)
    : presetManager(manager)
{}

void PresetListModel::updateContent()
{
    items.clear();

    int numPresets = presetManager.getNumPresets();
    juce::String category = "";

    for (int i = 0; i < numPresets; ++i) {
        auto* preset = presetManager.getPresetAt(i);
        if (preset->category != category) {
            items.emplace_back(preset->category, nullptr, -1);
            category = preset->category;
        }
        items.emplace_back("", preset, i);
    }
}

int PresetListModel::getNumRows()
{
    return int(items.size());
}

juce::String PresetListModel::getNameForRow(int rowNumber)
{
    if (rowNumber >= int(items.size())) {
        return {};
    }

    Item item = items[size_t(rowNumber)];
    if (item.category.isNotEmpty()) {
        return item.category.toUpperCase();
    }

    return item.preset->name;
}

void PresetListModel::listBoxItemClicked(int row, const juce::MouseEvent&)
{
    if (row != -1) {
        Item item = items[size_t(row)];
        if (item.preset != nullptr) {
            onPresetSelected(item.presetIndex);
        }
    }
}

void PresetListModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool isSelected)
{
    Item item = items[size_t(rowNumber)];
    bool isCategory = item.category.isNotEmpty();

    if (isSelected && !isCategory) {
        g.fillAll(Colors::listSelected);
    }

    if (isCategory) {
        g.setColour(Colors::text.withAlpha(0.5f));
        g.setFont(Fonts::getMonoFont(16.0f));
    } else if (isSelected) {
        g.setColour(Colors::textSelected);
        g.setFont(Fonts::getMonoFont());
    } else {
        g.setColour(Colors::text);
        g.setFont(Fonts::getMonoFont());
    }

    g.drawText(getNameForRow(rowNumber), 10, 0, width - 10, height, juce::Justification::left, true);
}

PresetPicker::PresetPicker(PresetManager& presetManager_)
    : presetManager(presetManager_), model(presetManager), list("Preset Browser", &model)
{
    setInterceptsMouseClicks(false, true);

    addAndMakeVisible(list);

    list.setMultipleSelectionEnabled(false);
    list.setMouseMoveSelectsRows(true);
    list.setRowHeight(25);
    list.setLookAndFeel(&lf);

    model.onPresetSelected = [this](int presetIndex) { onPresetSelected(presetIndex); };

    animatorUpdater.addAnimator(showAnimator);
    animatorUpdater.addAnimator(hideAnimator);
}

PresetPicker::~PresetPicker()
{
    list.setLookAndFeel(nullptr);
}

void PresetPicker::paint(juce::Graphics& g)
{
    g.setColour(Colors::listBackground);
    g.fillRect(getLocalBounds());

    g.setColour(Colors::accent1);
    g.fillRect(0, 0, 2, getHeight());
}

void PresetPicker::resized()
{
    list.setBounds(4, 0, getWidth() - 4, getHeight());
}

void PresetPicker::toggleVisibility()
{
    if (hidden) {
        show();
    } else {
        hide();
    }
}

void PresetPicker::show()
{
    model.updateContent();
    list.updateContent();

    showAnimator.start();
}

void PresetPicker::hide()
{
    hidden = true;
    hideAnimator.start();
}

bool PresetPicker::isHidden() const
{
    return hidden;
}

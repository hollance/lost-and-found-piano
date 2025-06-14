#pragma once

#include <JuceHeader.h>
#include "LookAndFeel.h"
#include "MidiKeyboardComponent.h"
#include "PluginProcessor.h"
#include "RotaryKnob.h"

// The width is 52 white piano keys times 18 pixels, minus one pixel.
static constexpr int defaultWidth = 935;
static constexpr int defaultHeight = 561;

class EditorView : public juce::Component
{
public:
    EditorView(AudioProcessor& audioProcessor);
    ~EditorView() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void drawGroup(juce::Graphics&, const juce::String& name, int x, int y, int width);

    AudioProcessor& audioProcessor;

    RotaryKnob fineTuningKnob { "Fine", audioProcessor.apvts, ParameterID::fineTuning };
    RotaryKnob randomDetuningKnob { "Random", audioProcessor.apvts, ParameterID::randomDetuning };
    RotaryKnob stretchTuningKnob { "Stretch", audioProcessor.apvts, ParameterID::stretchTuning };

    RotaryKnob envDecayKnob { "Decay", audioProcessor.apvts, ParameterID::envDecay };
    RotaryKnob envReleaseKnob { "Release", audioProcessor.apvts, ParameterID::envRelease };
    RotaryKnob velocitySensitivityKnob { "Velocity", audioProcessor.apvts, ParameterID::velocitySensitivity };

    RotaryKnob hardnessKnob { "Hardness", audioProcessor.apvts, ParameterID::hardness };
    RotaryKnob velocityToHardnessKnob { "Velocity", audioProcessor.apvts, ParameterID::velocityToHardness };

    RotaryKnob mufflingFilterKnob { "Muffling", audioProcessor.apvts, ParameterID::mufflingFilter };
    RotaryKnob velocityToMufflingKnob { "Velocity", audioProcessor.apvts, ParameterID::velocityToMuffling };

    RotaryKnob tremoloKnob { "Tremolo", audioProcessor.apvts, ParameterID::tremolo };
    RotaryKnob autopanKnob { "Panning", audioProcessor.apvts, ParameterID::autopan };
    RotaryKnob lfoRateKnob { "Rate", audioProcessor.apvts, ParameterID::lfoRate };

    RotaryKnob trebleBoostKnob { "EQ", audioProcessor.apvts, ParameterID::trebleBoost };
    RotaryKnob overdriveKnob { "Overdrive", audioProcessor.apvts, ParameterID::overdrive };
    RotaryKnob stereoWidthKnob { "Stereo", audioProcessor.apvts, ParameterID::stereoWidth };

    RotaryKnob reverbSizeKnob { "Size", audioProcessor.apvts, ParameterID::reverbSize };
    RotaryKnob reverbDampKnob { "Damp", audioProcessor.apvts, ParameterID::reverbDamp };
    RotaryKnob reverbMixKnob { "Dry/Wet", audioProcessor.apvts, ParameterID::reverbMix };

    RotaryKnob outputLevelKnob { "Level", audioProcessor.apvts, ParameterID::outputLevel };

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EditorView)
};

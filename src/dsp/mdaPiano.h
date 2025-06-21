#pragma once

#include <JuceHeader.h>
#include "../Parameters.h"
#include "SharedDefs.h"

class MDAPiano
{
public:
    MDAPiano(Parameters& params);

    void prepareToPlay(double sampleRate) noexcept;
    void reset() noexcept;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) noexcept;

private:
    void update() noexcept;
    void processEvents(juce::MidiBuffer& midiMessages) noexcept;
    void noteOn(int note, int velocity) noexcept;

    Parameters& _params;

    // The current sample rate and 1 / sample rate.
    float _sampleRate, _inverseSampleRate;

    // MIDI note on / note off events for the current block. Each event is
    // described by 3 values: delta time, note number, velocity.
    static const int EVENTBUFFER = 120;
    int _notes[EVENTBUFFER + 8];

    // Special event code that marks the end of the MIDI events list.
    const int EVENTS_DONE = 99999999;

    // Special "note number" that says this voice is now kept alive by the
    // sustain pedal being pressed down. As soon as the pedal is released,
    // this voice will fade out.
    const int SUSTAIN = 128;

    // Big lookup table with waveforms containing the piano samples.
    short *_waves;

    // Maps the waveforms from the _waves lookup table to ranges of notes.
    Keygroup _keygroups[15];

    // List of the active voices.
    Voice _voices[NVOICES];

    // How many voices are currently in use.
    int _numActiveVoices;

    // Status of the damper pedal: 64 = pressed, 0 = released.
    int _sustain;

    // Output gain in linear units. Can be changed by MIDI CC 7.
    float _volume;

    // Envelope decay length (lower is shorter). Used when playing a new note.
    float _envDecay;

    // Value of the envelope release parameter, 0.0 - 1.0. This is used after a
    // note off event (if the sustain pedal is not pressed).
    float _envRelease;

    // Value of the muffling filter parameter, 0.0 - 1.0.
    float _mufflingFilter;

    // How sensitive the muffling filter is to note velocity, 0.0 - 5.0
    float _mufflingVelocity;

    // Adjusts the amount of filtering. This variable is changed when the mod
    // wheel or soft pedal is used. Default value = 160.
    float _muff;

    // These two settings change which waveform to use for a given note, by not
    // selecting the note's keygroup but one of its neighboring keygroups.
    int _hardnessOffset;
    float _hardnessVelocity;

    // Settings for the treble boost filter.
    float _trebleGain;
    float _filtCoef;

    // Delay units for the treble boost filter.
    float _filtL, _filtR;

    // Used to set the envelope level for new notes. Value between 0.25 and 3.0.
    float _velocitySensitivity;

    // Amount of fine-tuning, in semitones.
    float _fine;

    // Amount of random detuning.
    float _random;

    // Amount of stretch tuning.
    float _stretch;

    // For calculating the stereo width.
    float _width, _trim;

    // Amount of overdrive.
    float _overdrive;

    // Delay line for comb filter. Used to enhance the stereo width.
    int _delayPos;
    int _delayMax;
    float _combDelay[256];

    // Amount of comb filtering. More means a wider stereo effect.
    float _comb;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MDAPiano)
};

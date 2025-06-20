#pragma once

#include <JuceHeader.h>
#include "../Parameters.h"
#include "SharedDefs.h"

class MDAEPiano
{
public:
    MDAEPiano(Parameters& params);

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
    Keygroup _keygroups[33];

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

    // This changes which waveform to use for a given note, by not selecting
    // the note's own keygroup but one of its neighboring keygroups.
    int _hardnessOffset;

    // Settings for the treble boost filter.
    float _trebleGain;
    float _filtCoef;

    // Delay units for the treble boost filter.
    float _filtL, _filtR;

    // Amount of modulation: 0.0 means 100% autopanning, 0.5 = no modulation,
    // 1.0 = 100% tremolo.
    float _modulation;

    // Amount of modulation (LFO depth) for left and right channels.
    float _lmod, _rmod;
    float _lmodw, _rmodw;  // from mod wheel

    // The LFO phase increment in radians.
    float _lfoRate;

    // Current phase for the LFO. _lf0 describes a sine wave, while _lfo1 is a
    // cosine wave.
    float _lfo0, _lfo1;

    // Used to set the envelope level for new notes. Value between 0.25 and 3.0.
    float _velocitySensitivity;

    // Amount of fine-tuning, in semitones.
    float _fine;

    // Amount of random detuning.
    float _random;

    // For calculating the stereo width.
    float _width;

    // Amount of overdrive.
    float _overdrive;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MDAEPiano)
};

#pragma once

const int NVOICES = 128;  // max polyphony

const float SILENCE = 0.0001f;  // voice choking

// A keygroup maps notes to waveforms. All the waveforms are stored inside one
// big lookup table (see mdaPianoData.h). There are 15 keygroups, each covering
// 4 semitones. That's 60 notes in total. A piano has 88 keys so very low notes
// all share the same waveform; likewise for very high notes. The waveforms are
// mono, 22050 Hz, and consist of an attack portion and a loop portion.
struct Keygroup
{
    int root;  // MIDI root note (usually the note in the middle of the keygroup)
    int high;  // highest note this waveform should be used for
    int pos;   // index of the first sample in the lookup table
    int end;   // index of the last sample in the lookup table
    int loop;  // how far from end the first sample of the loop is
};

// State for an active voice.
struct Voice
{
    // What note triggered this voice, or SUSTAIN when the key is released
    // but the sustain pedal is held down.
    int note;

    // The increment for stepping through the waveform table. This is stored as
    // a fixed point value, where 65536 = 1.0. For example, a step size of 0.5
    // has a delta of 32768.
    int delta;

    // The fractional part of the current position in the waveform. This is
    // stored using 16 bits. The highest value it can have is 65535, which is
    // approximately 0.99999.
    int frac;

    // These are copied from the keygroup for this note. When we start playing
    // the note, pos is incremented by delta until it reaches end, and then it
    // wraps back to the loop index.
    int pos;
    int end;
    int loop;

    // The current envelope level and the exponential decay value that the
    // envelope is multiplied with on every step. Setting the decay to 0.99
    // will fade out the sound almost immediately (used for all notes off).
    float env;
    float decay;

    // "Muffling" filter. This is a first-order LPF. Not used by EPiano.
    float f0;  // delay for y(n - 1)
    float f1;  // delay for x(n - 1)
    float ff;  // filter coefficient

    // Panning volumes for the left and right channels.
    float outl;
    float outr;
};

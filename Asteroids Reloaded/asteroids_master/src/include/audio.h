#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

/** How to use the audio functions

-- Loading sounds --

If you want to add more sounds, increase the amount of samples in the sample
array */
#define NUM_SAMPLES 7
/*
Then add code in audio_init to load the new .wav file. The index in the array
is handled internally by load_sample, so the first loaded sample will be 0,
the second is 1, etc.

-- The soundtrack --

The speed of the alternating beats increases linearly over time until it hits a
minimum value. The delay is described by the function

    max(-GRADIENT * t + MAX_DELAY, MIN_DELAY)

where t = The time since the soundtrack started.

Change the values below as needed: */

#define SOUNDTRACK_MAX_DELAY    2.0f
#define SOUNDTRACK_MIN_DELAY    0.2f
#define SOUNDTRACK_GRADIENT     -0.02

typedef struct {
    float elapsed_time;
    float target_delay;
    int playing;
    Mix_Chunk *beats[2];
    int beat;
    float time;
} soundtrack_t;

extern Mix_Chunk **sound_samples;

// Initialise the mixer system and load all sounds
int audio_init();

// Load a specific sound (called from audio_init)
int load_sample(const char *filename);

// Update the timings in the soundtrack and play a sound if needed
// Call as often as possible, i.e. every loop of the main game loop
void soundtrack_play(soundtrack_t *st, double delta_secs);

// Initialise the soundtrack, setting values to the defaults
void soundtrack_init(soundtrack_t *st);

void audio_cleanup();

#endif
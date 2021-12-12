#ifdef DO_AUDIO
#include "audio.h"
#include "SDL_mixer.h"

Mix_Chunk **sound_samples;

int audio_init() {
    sound_samples = malloc(sizeof(Mix_Chunk*) * NUM_SAMPLES);
    memset(sound_samples, 0, sizeof(Mix_Chunk*) * NUM_SAMPLES);
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 512) != 0) {
        printf("Couldn't open audio.\n");
        return 0;
    }

    if (!load_sample("src/soundfiles/beat1.wav")) return 0;
    if (!load_sample("src/soundfiles/beat2.wav")) return 0;

    if (!load_sample("src/soundfiles/bangSmall.wav")) return 0;
    if (!load_sample("src/soundfiles/bangMedium.wav")) return 0;
    if (!load_sample("src/soundfiles/bangLarge.wav")) return 0;

    if (!load_sample("src/soundfiles/fire.wav")) return 0;

    if (!load_sample("src/soundfiles/thrust.wav")) return 0;

    return 1;
}

int load_sample(const char *filename) {
    static int i = 0;
    sound_samples[i] = Mix_LoadWAV(filename);
    if (sound_samples[i] == NULL) {
        printf("Failed to load wav file: \"%s\"\n", filename);
        return 0;
    }
    i++;
    return 1;
}

void soundtrack_play(soundtrack_t *st, double delta_secs) {
    if (st->playing) {
        st->elapsed_time += (float)delta_secs;
        st->time += (float)delta_secs;

        if (st->elapsed_time >= st->target_delay) {
            Mix_PlayChannel(0, st->beats[st->beat], 0);
            st->beat = (st->beat + 1) % 2;
            st->elapsed_time = 0;

            st->target_delay = SOUNDTRACK_GRADIENT * st->time + SOUNDTRACK_MAX_DELAY;
            if (st->target_delay < SOUNDTRACK_MIN_DELAY) st->target_delay = SOUNDTRACK_MIN_DELAY;
        }
    }
}

void soundtrack_init(soundtrack_t *st) {
    st->elapsed_time = 0;
    st->target_delay = SOUNDTRACK_MAX_DELAY;
    st->playing = 1;
    st->beat = 0;
    st->time = 0;
}

void audio_cleanup() {
    for (int i = 0; i < NUM_SAMPLES; i++) {
        Mix_FreeChunk(sound_samples[i]);
    }

    Mix_CloseAudio();
}

#endif
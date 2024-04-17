#pragma once

/*
                                AUDIO.H
    This header file constitutes all the function needed to run audio
    for Void Scavenger.

*/

#include <pthread.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#define PI (3.1415926535897932384626433832795)
#define SAMPLE_RATE (44100)
#define SHIP_SOUND_DURATION (1.0)

#define PRINT_ERROR(s) {\
  if (AUDIO_DEBUG) \
    fprintf(stderr, "%s: %d\n", s, alGetError());\
}

static int enemy_audio_allowed = 1;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================
int check_source_playing(TRACK *, int);
void play_audio(int);
size_t add_audio(char *);
void exit_audio();
int init_audio();
void pause_audio(int);
void generate_sine_wave(float, float, ALshort *);
void generate_triangle_wave(float, float, ALshort *);
void generate_sine_tone(float);
void generate_triangle_tone(float);
void pause_ship_audio();
void update_tone_frequency(int, float);
void update_source_pos(vec3, int);
void update_listener_pos(vec3);
void update_listener_orientation(versor);
void update_station_player_audio(vec3, versor);
void update_source_gain(int, float);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
int gen_rand_int(int);
int game_over_check();
void add_timer(float, void *, int, void *);

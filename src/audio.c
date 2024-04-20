#include <audio.h>

// ==================== BUFFER INITIALIZATION AND CLEANUP ====================

int init_audio() {
  if (!alutInit(NULL, NULL)) {
    fprintf(stderr, "ALUT Initialization Error: %s\n",
            alutGetErrorString(alutGetError()));
    return -1;
  }
  tracks = (TRACK *) malloc(BUFF_STARTING_LEN * sizeof(TRACK));
  if (!tracks) {
    fprintf(stderr, "Failed to initialize audio tracks buffer!\n");
    return -1;
  }
  num_tracks = 0;
  tracks_buff_len = BUFF_STARTING_LEN;

  return 0;
}

void exit_audio() {
  free(tracks);
  alutExit();
}

// ================== INDIVIDUAL INITIALIZATION AND CLEANUP ==================

size_t add_audio(char *filepath) {
  if (!tracks) {
    fprintf(stderr, "Trying to add an audio path to a NULL tracks buffer\n");
    return INVALID_INDEX;
  }

  TRACK *t = tracks + num_tracks;

  if (!(t->buffer = alutCreateBufferFromFile(filepath))) {
    fprintf(stderr, "Failed to add %s as audio track!\n", filepath);
    return INVALID_INDEX;
  }

  alGenSources(1, &(t->source));
  if (alGetError()) {
    fprintf(stderr, "Unable to generate sources for %s\n", filepath);
    return INVALID_INDEX;
  }
  alSourcei(t->source, AL_BUFFER, t->buffer);
  if (alGetError()) {
    fprintf(stderr, "Unable to set integer property for %s\n", filepath);
    return INVALID_INDEX;
  }

  /* Special accomidations for specific tracks */
  if (num_tracks == ALIEN_NORMAL_TALKING_WAV ||
      num_tracks == ALIEN_BRUTE_TALKING_WAV) {
    alSourcef(t->source, AL_ROLLOFF_FACTOR, 3.0);
    PRINT_ERROR("alSourcef special accomidations")
  }
  if (num_tracks == MAIN_THEME || num_tracks == SPACE_THEME ||
      num_tracks == STATION_THEME) {
    alSourcei(t->source, AL_LOOPING, AL_TRUE);
  }

  num_tracks++;
  if (num_tracks == tracks_buff_len) {
    int status = double_buffer((void **) &tracks, &tracks_buff_len,
                               sizeof(TRACK));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate tracks buffer\n");
      return INVALID_INDEX;
    }
  }

  #ifdef __linux__
  fprintf(stderr, "Loaded track %ld: %s\n", num_tracks - 1, filepath);
  #else
  fprintf(stderr, "Loaded track %lld: %s\n", num_tracks - 1, filepath);
  #endif
  return num_tracks - 1;
}

// ============================= GENERAL HELPERS =============================

void play_audio(int track) {
  if (track < 0 || track >= tracks_buff_len) {
    fprintf(stderr, "Trying to play a track which doesn't exist!\n");
    return;
  }

  TRACK *t = tracks + track;
  alSourcePlay(t->source);
  int error = alGetError();
  if (error) {
    fprintf(stderr, "Error (%d): Unable to play track %d\n", error, track);
  }
}

int check_source_playing(TRACK *buff, int track) {
  ALint playing_source = 0;
  TRACK *t = buff + track;
  if (!t) {
    fprintf(stderr, "Error: Trying to check a source which doesn't exist\n");
    return INVALID_SOURCE;
  }
  alGetSourcei(t->source, AL_SOURCE_STATE, &playing_source);
  if (playing_source == AL_PLAYING) {
    return SOURCE_PLAYING;
  } else {
    return SOURCE_PAUSED;
  }
}

void pause_audio(int track) {
  TRACK *t = tracks + track;
  alSourceStop(t->source);
}

/*
  Expects a volume level as a float mulitplier
  0.0 - No volume
  1.0 - Standard gain preset
  2.0 - Twice the gain
  3.0 - Thrice the gain
  ...
*/
void update_volume(float volume) {
  global_volume = volume;
  alListenerf(AL_GAIN, volume);
}

// ========================== STATION PLAYER AUDIO ============================

void play_player_death() {
  int track = PLAYER_DEATH_1_WAV;
  track += gen_rand_int(2);
  play_audio(track);
}

void play_player_hurt() {
  int track = PLAYER_HURT_1_WAV;
  if (!AUDIO_EXPLICIT) {
    track += gen_rand_int(2);
  } else {
    track += gen_rand_int(4);
  }
  play_audio(track);
}

void update_station_player_audio(vec3 pos, versor quat) {
  update_listener_pos(pos);
  update_listener_orientation(quat);
  update_source_pos(pos, STATION_MODE_WEAPON_WAV);
}

// ============================ WORLD BOUNDS AUDIO ============================

void play_out_of_bounds_audio() {
  if (check_source_playing(tracks, WORLD_EXIT_WAV) == SOURCE_PAUSED) {
    play_audio(WORLD_EXIT_WAV);
  }
}

void pause_out_of_bounds_audio() {
  if (check_source_playing(tracks, WORLD_EXIT_WAV) == SOURCE_PLAYING) {
    pause_audio(WORLD_EXIT_WAV);
  }
}

// ============================= SPACESHIP AUDIO ==============================

void pause_ship_audio() {
  pause_audio(SHIP_SINE_WAVE);
  pause_audio(SHIP_TRI_WAVE_1);
  pause_audio(SHIP_TRI_WAVE_2);
}

/*
  Creates the ship tones and adds them to the tracks buffer
*/
void generate_ship_noises() {
  generate_sine_tone(BASE_SINE_FREQUENCY);
  generate_triangle_tone(BASE_TRIANGLE_FREQUENCY + 1.0);
  generate_triangle_tone(BASE_TRIANGLE_FREQUENCY);
}

/*
  Updates the frequency of the ship noises based on the velocity which
  the ship is currently moving at. Updates both triangle tones and the
  sine tone
*/
void update_ship_noises() {
  if (!game_over_check()) {
    float velocity = glm_vec3_norm(player_ship.ent->velocity);
    float tone = 0.0;
    if (velocity > MAX_SHIP_VELOCITY_TONE) {
      tone = MAX_TONE;
    } else {
      tone = (velocity / MAX_SHIP_VELOCITY_TONE) * MAX_TONE;
    }

    update_tone_frequency(SHIP_SINE_WAVE, 50.0 + tone);
    update_tone_frequency(SHIP_TRI_WAVE_1, 125.0 + tone);
    update_tone_frequency(SHIP_TRI_WAVE_2, 125.0 + tone + 1.0);

    if (check_source_playing(tracks, SHIP_SINE_WAVE) == SOURCE_PAUSED) {
      play_audio(SHIP_SINE_WAVE);
    }
    if (check_source_playing(tracks, SHIP_TRI_WAVE_1) == SOURCE_PAUSED) {
      play_audio(SHIP_TRI_WAVE_1);
    }
    if (check_source_playing(tracks, SHIP_TRI_WAVE_2) == SOURCE_PAUSED) {
      play_audio(SHIP_TRI_WAVE_2);
    }
  } else {
    pause_ship_audio();
  }
}

void play_ship_explosion() {
  play_audio(SPACESHIP_EXPLOSION_WAV);
}

void play_spaceship_hull() {
  play_audio(SPACESHIP_HULL_HIT_WAV);
}

// =============================== SHIELD AUDIO ==============================

void generate_shield_audio() {
  generate_sine_tone(BASE_SINE_FREQUENCY);
  generate_triangle_tone(BASE_TRIANGLE_FREQUENCY);

  alSourcef(tracks[SHIELD_SINE_WAVE].source, AL_GAIN, 0.50);
  alSourcef(tracks[SHIELD_TRI_WAVE].source, AL_GAIN, 0.50);
}

void update_shield_tone() {
  if (st_player.recharging_shield) {
    float cur_shield = st_player.cur_shield / st_player.max_shield;
    update_tone_frequency(SHIELD_SINE_WAVE, BASE_SINE_FREQUENCY +
                         (MAX_SHIELD_SINE_FREQUENCY * cur_shield));

    update_tone_frequency(SHIELD_TRI_WAVE, BASE_TRIANGLE_FREQUENCY +
                         (MAX_SHIELD_TRI_FREQUENCY * cur_shield));
    if (check_source_playing(tracks, SHIELD_SINE_WAVE) == SOURCE_PAUSED) {
      play_audio(SHIELD_SINE_WAVE);
    }
    if (check_source_playing(tracks, SHIELD_TRI_WAVE) == SOURCE_PAUSED) {
      play_audio(SHIELD_TRI_WAVE);
    }
  } else {
    pause_audio(SHIELD_SINE_WAVE);
    pause_audio(SHIELD_TRI_WAVE);
  }
}

// ============================= TONE GENERATION ==============================

/*
  Creates a sine wave based on the frequency and duration passed in
*/
void generate_sine_wave(float frequency, float duration, ALshort *buff) {
  int num_samples = duration * SAMPLE_RATE;
  for (int i = 0; i < num_samples; i++) {
    float time = i / ((float) SAMPLE_RATE);
    buff[i] = (ALshort) (sin(2.0 * PI * frequency * time) * 32767.0);
  }
}

/*
  Creates a triangle wave based on the frequency and duration passed in
*/
void generate_triangle_wave(float frequency, float duration, ALshort *buff) {
  int num_samples = duration * SAMPLE_RATE;
  for (int i = 0; i < num_samples; i++) {
    float time = i / ((float) SAMPLE_RATE);
    float period = 1.0 / frequency;
    float curr_time_in_period = fmod(time, period);
    float half_period = period / 2.0;
    if (curr_time_in_period < half_period) {
      buff[i] = (ALshort) (-32767.0 + (curr_time_in_period / half_period)
                           * 65535.0);
    } else {
      buff[i] = (ALshort) (32767.0 - ((curr_time_in_period - half_period)
                           / half_period) * 65535.0);
    }
  }
}

/*
  Adds a sine tone to the tracks buffer
*/
void generate_sine_tone(float frequency) {
  TRACK *t = tracks + num_tracks;
  int wave_buff_size = SHIP_SOUND_DURATION * SAMPLE_RATE * sizeof(ALshort);
  ALshort *buff = (ALshort *) malloc(wave_buff_size);
  generate_sine_wave(frequency, SHIP_SOUND_DURATION, buff);
  alGenBuffers(1, &t->buffer);
  PRINT_ERROR("alGenBuffers sine")
  alBufferData(t->buffer, AL_FORMAT_MONO16, buff, wave_buff_size, SAMPLE_RATE);
  PRINT_ERROR("alBufferData sine")
  alGenSources(1, &t->source);
  PRINT_ERROR("alGenSources sine")
  alSourcei(t->source, AL_BUFFER, t->buffer);
  PRINT_ERROR("alSourcei sine ~ AL_BUFFER")
  alSourcei(t->source, AL_LOOPING, AL_TRUE);
  PRINT_ERROR("alSourcei sine ~ AL_LOOPING")

  free(buff);
  #ifdef __linux__
  fprintf(stderr, "Loaded Track %ld: Sine Tone at %f hz\n", num_tracks,
          frequency);
  #else
  fprintf(stderr, "Loaded Track %lld: Sine Tone at %f hz\n", num_tracks,
          frequency);
  #endif
  num_tracks++;
  if (num_tracks == tracks_buff_len) {
    int status = double_buffer((void **) &tracks, &tracks_buff_len,
                               sizeof(TRACK));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate tracks buffer\n");
      return;
    }
  }
}

/*
  Adds a triangle tone to the tracks buffer
*/
void generate_triangle_tone(float frequency) {
  TRACK *t = tracks + num_tracks;
  int wave_buff_size = SHIP_SOUND_DURATION * SAMPLE_RATE * sizeof(ALshort);
  ALshort *buff = (ALshort *) malloc(wave_buff_size);
  generate_triangle_wave(frequency, SHIP_SOUND_DURATION, buff);
  alGenBuffers(1, &t->buffer);
  PRINT_ERROR("alGenBuffers tri")
  alBufferData(t->buffer, AL_FORMAT_MONO16, buff, wave_buff_size, SAMPLE_RATE);
  PRINT_ERROR("alBufferData tri")
  alGenSources(1, &t->source);
  PRINT_ERROR("alGenSources tri")
  alSourcei(t->source, AL_BUFFER, t->buffer);
  PRINT_ERROR("alSourcei tri ~ AL_BUFFER")
  alSourcei(t->source, AL_LOOPING, AL_TRUE);
  PRINT_ERROR("alSourcei tri ~ AL_LOOPING")

  free(buff);
  #ifdef __linux__
  fprintf(stderr, "Loaded Track %ld: Triangle Tone at %f hz\n", num_tracks,
          frequency);
  #else
  fprintf(stderr, "Loaded Track %lld: Triangle Tone at %f hz\n", num_tracks,
          frequency);
  #endif
  num_tracks++;
  if (num_tracks == tracks_buff_len) {
    int status = double_buffer((void **) &tracks, &tracks_buff_len,
                               sizeof(TRACK));
    if (status) {
      fprintf(stderr, "Error: Unable to reallocate tracks buffer\n");
      return;
    }
  }
}

/*
  Updates track's tone, assuming the track is a single frequency tone
*/
void update_tone_frequency(int track, float frequency) {
  alSourcef(tracks[track].source, AL_PITCH, frequency / 100.0);
}

// ============================ DIRECTIONAL AUDIO =============================

/*
  Moves the listeners position in 3D space (OpenGL coordinate axes)
  (world space)
*/
void update_listener_pos(vec3 pos) {
  alListenerfv(AL_POSITION, (ALfloat *) pos);
}

/*
  Should only be called right before a track is about to be played
  (world space)
*/
void update_source_pos(vec3 pos, int track) {
  alSourcefv(tracks[track].source, AL_POSITION, (ALfloat *) pos);
}

void update_source_gain(int track, float gain) {
  alSourcef(tracks[track].source, AL_GAIN, gain);
}

/*
  Updates the orientation of the listener (using world space)
*/
void update_listener_orientation(versor quat) {
  vec3 up;
  vec3 at = {-1.0, 0.0, 0.0};
  glm_vec3_copy(GLM_YUP, up);
  glm_quat_rotatev(quat, up, up);
  glm_quat_rotatev(quat, at, at);
  glm_vec3_normalize(up);
  glm_vec3_normalize(at);
  ALfloat orientation[6] = {at[0], at[1], at[2], up[0], up[1], up[2]};
  alListenerfv(AL_ORIENTATION, orientation);
}

void reset_listener_orientation() {
  ALfloat orientation[6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
  alListenerfv(AL_ORIENTATION, orientation);
}

void reset_listener_pos() {
  ALfloat pos[3] = {0.0, 0.0, 0.0};
  alListenerfv(AL_POSITION, pos);
}

void reset_source_pos(TRACK *t) {
  ALfloat pos[3] = {0.0, 0.0, 0.0};
  alSourcefv(t->source, AL_POSITION, pos);
}

// =========================== STATION ENEMY AUDIO ============================

void play_enemy_audio(vec3 pos, int track) {
  if (enemy_audio_allowed) {
    float dist = glm_vec3_distance(pos, st_player.ent->translation);
    float new_volume = 0.0;
    if (dist >= MAX_GAIN_DIST) {
      new_volume = 0.0;
    } else {
      new_volume = global_volume - ((dist / MAX_GAIN_DIST) * global_volume);
    }
    update_source_gain(track, new_volume);
    play_audio(track);
    add_timer(2.0, &enemy_audio_allowed, 1, NULL);
    enemy_audio_allowed = 0;
  }
}


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
  return 0;
}

void play_audio(int track) {
  if (track < 0 || track >= tracks_buff_len) {
    fprintf(stderr, "Trying to play a track which doesn't exist!\n");
    return;
  }

  TRACK *t = tracks + track;
  alSourcePlay(t->source);
  if (alGetError()) {
    fprintf(stderr, "Unable to play track %d\n", track);
  }
}

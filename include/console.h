/*
                      CONSOLE.h
  Responsible for handling console prototypes and functionality
*/
#include <pthread.h>
#include <global_vars.h>
#include <structs/player_str.h>
#include <structs/item_str.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <const.h>

/* DEFINES */
#define MAX_TOKENS (10)
#define CONSOLE_BUFFER_MAX (100)

typedef void (*close_error)();

// ================================= GLOBALS =================================
char cons_cmd[CONSOLE_BUFFER_MAX];
char cons_cursor[CONSOLE_BUFFER_MAX + 1];
unsigned int cons_cmd_len = 0;
extern unsigned int fps_enabled;

// ====================== INTERNALLY DEFINED FUNCTIONS =======================
void command_not_found();
void cursor_on(int);
void set_gamemode_station();
void set_gamemode_space();

// ====================== EXTERNALLY DEFINED FUNCTIONS =======================
void print_parse_table();
void add_timer(float, void *, int, void *);
void set_console_error(const char *);
void disable_console_error();
void clear_space_mode();
void clear_station_mode();
void init_space_mode();
void init_station_mode();
void cleanup_game();
void refresh_sim_distances();
void enable_fps();
void disable_fps();
void free_timer_queue();
I_SLOT *inv_first_avail();
void set_enhancements(ST_ITEM *, int, int);
void pause_ship_audio();
void reset_listener_orientation();
void reset_listener_pos();
void tick();
void play_audio(int);
void pause_audio(int);

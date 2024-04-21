#ifndef __INTERMEDIATE_UI__
#define __INTERMEDIATE_UI__

#include <pthread.h>
#include <engine/ui_component.h>
#include <ui/structs/ship_parts_ui_str.h>
#include <ui/structs/inventory_ui_str.h>
#include <global_vars.h>
#include <const.h>
#include <stdio.h>
#include <string.h>

/*
                                   INTERMEDIATE
Implements the functionality for defining UI components for intermediate menu.
*/

#define INTERMEDIATE_TEXT_BUFFER_SIZE (128)

/* GLOBALS */
UI_COMP *ui_intermediate_root;
UI_COMP *ui_intermediate_background;
UI_COMP *ui_intermediate_next_lv_background;
UI_COMP *ui_intermediate_next_lv_text_background;
UI_COMP *ui_intermediate_next_lv_text;
UI_COMP *ui_intermediate_next_lv_button_root;
UI_COMP *ui_intermediate_next_lv_button;
UI_COMP *ui_intermediate_enemy_1_type_background;
UI_COMP *ui_intermediate_enemy_1_type_text;
UI_COMP *ui_intermediate_enemy_1_info_background;
UI_COMP *ui_intermediate_enemy_1_info_text;
UI_COMP *ui_intermediate_enemy_2_type_background;
UI_COMP *ui_intermediate_enemy_2_type_text;
UI_COMP *ui_intermediate_enemy_2_info_background;
UI_COMP *ui_intermediate_enemy_2_info_text;
int last_terminal_state;
static int gen_sp_enemies = 1;

static char intermediate_next_lv_buffer[INTERMEDIATE_TEXT_BUFFER_SIZE];
//static char intermediate_enemy_1_type_buffer[INTERMEDIATE_TEXT_BUFFER_SIZE];
static char intermediate_enemy_1_info_buffer[INTERMEDIATE_TEXT_BUFFER_SIZE];
//static char intermediate_enemy_2_type_buffer[INTERMEDIATE_TEXT_BUFFER_SIZE];
static char intermediate_enemy_2_info_buffer[INTERMEDIATE_TEXT_BUFFER_SIZE];

/* ================= INTERNALLY DEFINED FUNCTIONS ================= */
int init_intermediate();
void update_intermediate();
void open_intermediate();
void close_intermediate();
void toggle_intermediate();
void launch_on_click();
void set_intermediate_enemy_type_info(int slot_number, int enemy_move_type, SHIP *enemy_ship);

/* ================= EXTERNALLY DEFINED FUNCTIONS ================ */
UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
int get_terminal_ui_state();
void set_gamemode_space();
void generate_sp_enemy_types();
void get_sp_enemy_type_strings(char *, size_t, char *, size_t);
void free_timer_queue();
void add_timer(float, void *, int, void *);
void reset_listener_orientation();
void reset_listener_pos();
void play_audio(int);
void pause_audio(int);
void clear_station_mode();
void init_space_mode();
void tick();

#endif

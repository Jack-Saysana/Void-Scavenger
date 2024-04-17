#include <stdio.h>
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>
#include <engine/engine.h>
#include <const.h>
#include <global_vars.h>

#define MAX_CMD_LEN (100)

/* GLOBALS */

/* Console */
extern char cons_cmd[MAX_CMD_LEN];
extern char cons_cursor[MAX_CMD_LEN + 1];
extern unsigned int cons_cmd_len;
extern unsigned int cons_cursor_pos;
extern unsigned int cons_cursor_enabled;


/* Key Handlers */
int holding_alpha[26];
int holding_num[10];
int holding_space = 0;
int holding_backspace = 0;
int holding_dot = 0;
int holding_underscore = 0;
int holding_shift = 0;
int holding_alt = 0;
int holding_enter = 0;
int holding_minus = 0;
int holding_tilde = 0;
int holding_slash = 0;
int holding_tab = 0;
int first_mouse_move = 0;
int can_shoot = 1;
float mouse_sens = 0.05;
vec2 prev_mouse_pos;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void fb_size_callback(GLFWwindow *, int, int);
void mouse_pos_callback(GLFWwindow *, double, double);
void mouse_scroll_callback(GLFWwindow *, double, double);
void mouse_button_callback(GLFWwindow *, int, int, int);
void input_keys(GLFWwindow *);
void advance_cursor();
void retreat_cursor();
void update_cursor_enabledness();
void set_can_shoot(int is_can_shoot);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void tokenize(char *, unsigned int);
void update_perspective();
int is_console_enabled();
void enable_console();
void disable_console();
void update_console_text(char *);
void move_camera(CAM *, MOVE_DIR);
void update_console_cursor(char *);
void disable_console_cursor();
void enable_console_cursor();
void add_timer(float, void *, int, void *);
size_t init_projectile(vec3, vec3, float, PROJ_SOURCE, S_WEAPON_T, float,
                       float, size_t);
int projectile_insert_sim(size_t);
void toggle_inventory();
void toggle_ship_parts();
void toggle_skill_tree();
int get_terminal_ui_state();
void set_gamemode_space();
void set_gamemode_station();
void reset_station();
void target_nearest_enemy();
void toggle_st_waypoint();

int get_item_prompt_state();
void pickup_item();
void drop_item(size_t);
size_t find_first_filled();

void quit();
void play_audio(int);
void update_station_player_audio(vec3, versor);

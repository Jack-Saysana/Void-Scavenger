#include <GLFW/glfw3.h>
#include <engine/engine.h>
#include <global_vars.h>
#include <stdio.h>

#define MAX_CMD_LEN (100)

/* GLOBALS */

/* Console */
extern char cons_cmd[MAX_CMD_LEN];
extern unsigned int cons_cmd_len;
extern UI_COMP *console;

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
int first_mouse_move = 0;
vec2 prev_mouse_pos;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void fb_size_callback(GLFWwindow *, int, int);
void mouse_pos_callback(GLFWwindow *, double, double);
void mouse_scroll_callback(GLFWwindow *, double, double);
void mouse_button_callback(GLFWwindow *, int, int, int);
void input_keys(GLFWwindow *);

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================
void tokenize(char *, unsigned int);
void update_perspective();
int is_console_enabled();
void enable_console();
void disable_console();
void update_console_text(char *);

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <math.h>
#include <engine/engine.h>
#include <global_vars.h>

// Framebuffer
static FRAMEBUFFER main_menu_ui_fb;

// Local UI components
static UI_COMP *main_menu_root = NULL;
static UI_COMP *title = NULL;
static UI_COMP *btn_root = NULL;
static UI_COMP *start_btn = NULL;
static UI_COMP *close_btn = NULL;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void start_game(UI_COMP *, void *);
void close_game(UI_COMP *, void *);
unsigned int render_main_menu_anim();

// ======================= EXTERNALLY DEFINED FUNCTIONS ======================

UI_COMP *init_blue_button(UI_COMP *, vec2, float, float, int);
void quit();
void render_skybox();
int init_space_mode();
void enable_fps();
void enable_coordinates();
MODEL *get_player_ship_model();
unsigned int get_model_shader();
unsigned int get_cubemap_shader();

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <structs/lexer_str.h>
#include <structs/parser_str.h>
#include <float.h>
#include <global_vars.h>
#include <structs/ship_str.h>

/* DEFINES */
/* Command identifiers and arguments */
#define SET                  ("set")
#define CURSOR               ("cursor")
#define ON                   ("on")
#define OFF                  ("off")
#define GIVE                 ("give")
#define SPAWN                ("spawn")
#define COORDS               ("coords")
#define RESPAWN              ("respawn")
#define WIRE                 ("wire")
#define HIT_BOXES            ("hb")
#define RENDER_ARENA         ("ra")
#define RENDER_BOUNDS        ("rb")
#define SET_SIM_DIST         ("ssd")
#define SET_RENDER_DIST      ("srd")
#define GAMEMODE             ("gamemode")
#define STATION_CMD          ("station")
#define SPACE_CMD            ("space")
#define QUIT                 ("quit")
#define PLAYER               ("player")
#define SPEED                ("speed")
#define RESET                ("reset")
#define FPS                  ("fps")
#define ARENA                ("arena")
#define SHIELD               ("shield")
#define HEALTH               ("health")
#define XP                   ("xp")
#define GAMELEVEL            ("gamelevel")
#define ESHOOT               ("eshoot")
#define GUN                  ("gun")
#define GAMEOVER             ("gameover")
#define BALLISTIC_CMD        ("ballistic")
#define LASER_CMD            ("laser")
#define PLASMA_CMD           ("plasma")
#define MAX_TOKS (10)

/* GLOBALS */
extern LEXER lexer;
CURRENT current;
TOKEN command[MAX_TOKS];

/* ================ INTERNALLY DEFINED FUNCTIONS =================== */
void parse();
TOKEN get_token();
enum KIND peek_token();
void console_dispatcher();
void init_parse_table();
void print_parse_table();
float create_float(int);

/* ================ EXTERNALLY DEFINED FUNCTIONS =================== */
void command_not_found();
void toggle_hit_boxes();
void toggle_wire_frame();
void toggle_render_arena();
void toggle_render_bounds();
void cursor_on(int);
void eshoot_on(int);
void set_gamemode_station();
void set_gamemode_space();
void quit();
void set_player_station_speed(float);
void enable_coordinates();
void disable_coordinates();
void set_render_dist(float);
void set_sim_dist(float);
void reset_station();
void reset_space();
void fps_toggle();
void set_arena(float);
void set_player_health(float, int);
void set_player_shield(float, int);
void set_player_xp(float);
void set_gamelevel(float);
void game_over();
void set_gun(S_WEAPON_T);

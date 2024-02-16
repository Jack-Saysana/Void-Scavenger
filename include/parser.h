#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <structs/lexer_str.h>
#include <structs/parser_str.h>
#include <float.h>

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
#define GAMEMODE             ("gamemode")
#define STATION              ("station")
#define SPACE                ("space")
#define QUIT                 ("quit")
#define PLAYER               ("player")
#define SPEED                ("speed")

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
void cursor_on(int);
void set_gamemode_station();
void set_gamemode_space();
void quit();
void set_player_station_speed(float);
void enable_coordinates();
void disable_coordinates();

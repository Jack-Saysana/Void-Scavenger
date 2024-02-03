#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <lexer_str.h>
#include <parser_str.h>
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
void cursor_on(int);

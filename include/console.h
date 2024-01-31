/*
                      CONSOLE.h
  Responsible for handling console prototypes and functionality
*/
#include <engine/engine.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

/* DEFINES */
#define MAX_TOKENS (10)
#define CONSOLE_BUFFER_MAX (100)

typedef void (*close_error)();

/* ------------- GLOBALS ------------ */
char cons_cmd[CONSOLE_BUFFER_MAX];
char cons_cursor[CONSOLE_BUFFER_MAX + 1];
unsigned int cons_cmd_len = 0;

/* ---------------- INTERNALLY DEFINED FUNCTIONS -------------- */
void command_not_found();

/* ---------------- EXTERNALLY DEFINED FUNCTIONS -------------- */
void print_parse_table();
void add_timer(float, void *, int);
void set_console_error(const char *);
void disable_console_error();

/*
                      CONSOLE.h
  Responsible for handling console prototypes and functionality
*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <engine/engine.h>

/* DEFINES */
#define MAX_TOKENS (10)
#define CONSOLE_BUFFER_MAX (100)

/* ------------- GLOBALS ------------ */
char cons_cmd[CONSOLE_BUFFER_MAX];
unsigned int cons_cmd_len = 0;

/* ---------------- INTERNALLY DEFINED FUNCTIONS -------------- */
void command_not_found();
void cursor_on(int);

/* ---------------- EXTERNALLY DEFINED FUNCTIONS -------------- */
void print_parse_table();

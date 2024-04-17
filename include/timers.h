/*
                              TIMERS.h
  Handles adding, decrementing, and expiration events for all timers
*/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <global_vars.h>

#define FUNC_PTR (-1000)

typedef void (*func_ptr)(void *);

typedef struct timer {
  float time;
  void *mem;
  void *args;
  int set_to;
} TIMER;

typedef struct timers {
  struct timers *next;
  struct timers *prev;
  TIMER *data;
} TIMERS;

/* GLOBALS */
static TIMERS *head;
static TIMERS *tail;

/* ========================== INTERNALLY DEFINED =========================== */
void add_timer(float, void *, int, void *);
void decrement_current_timer(float);
void timer_dispatcher(TIMERS *);
int init_timer_queue();
void free_timer_queue();

/* ========================== EXTERNALLY DEFINED =========================== */

void prepare_object_movement();
void update_object_movement();
//void update_object_movement(int);

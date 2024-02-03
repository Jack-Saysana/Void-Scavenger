/*
                              TIMERS.h
  Handles adding, decrementing, and expiration events for all timers
*/

#include <stdlib.h>
#include <stdio.h>

#define FUNC_PTR (-1000)

typedef void (*func_ptr)();

typedef struct timer {
  float time;
  void *mem;
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
void add_timer(float, void *, int);
void decrement_current_timer(float);
void timer_dispatcher(TIMERS *);
int init_timer_queue();
void free_timer_queue();

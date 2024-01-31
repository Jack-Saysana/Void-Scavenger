#include <timers.h>

/*
  Helper function to add a timer to the list

  time - How many seconds the timer is
  mem - location in memory to set
  set_to - value to change the location in memory to
*/
void add_timer(float time, void *mem, int set_to) {
  if (time <= 0.0) {
    return;
  }
  TIMERS *new = (TIMERS *) (malloc(sizeof(TIMERS)));
  if (!new) {
    fprintf(stderr, "timers.c: Failed to allocate a new timer!\n");
    exit(1);
  }
  new->data = (TIMER *) (malloc(sizeof(TIMER)));
  if (!new->data) {
    fprintf(stderr, "timers.c: Failed to allocate a new timer!\n");
    exit(1);
  }
  new->data->time = time;
  new->data->mem = mem;
  new->data->set_to = set_to;
  new->next = NULL;
  new->prev = NULL;

  if (!head) {
    head = new;
    tail = new;
    return;
  } else {
    new->data->time -= head->data->time;
    if (new->data->time < 0.0) {
      TIMERS *temp = head;
      head = new;
      temp->prev = new;
      temp->data->time -= time;
      new->next = temp;
      new->data->time = time;
      return;
    }
  }
  TIMERS *prev = head;
  TIMERS *next = head->next;
  while (next &&/* (next != tail) &&*/ (next->data->time <= new->data->time)) {
    new->data->time -= next->data->time;
    prev = next;
    next = next->next;
  }

  /* Insert new node between prev and next nodes */

  new->next = next;
  new->prev = prev;
  prev->next = new;
  if (next) {
    next->prev = new;
    next->data->time -= new->data->time;
  } else {
    tail = new;
  }
}

/*
  Simple helper function to decrement time
  from the timer in the front of the list
*/
void decrement_current_timer(float delta) {
  if (!head) {
    return;
  }
  if ((head->data->time -= delta) <= 0.0) {
    float residual = head->data->time - delta;  
    if (residual < 0.0) {
      residual *= -1.0;
    }
    TIMERS *temp = head;
    head = head->next;
    timer_dispatcher(temp);
    while (head && (residual > 0.0) && ((head->data->time - residual) <= 0.0)) {
      temp = head;
      residual -= head->data->time;
      head = head->next;
      timer_dispatcher(temp);
    }
  }
}

/*
  Dispatcher to perform the expiration event
*/
void timer_dispatcher(TIMERS *timer) {
  /* When timer has expired, set location stored in pointer */
  /* to the value passed in originally                      */
  if (timer->data->set_to == FUNC_PTR) {
    ((func_ptr) (timer->data->mem))();   
  } else {
    *((int *) timer->data->mem) = timer->data->set_to;
  }
  free(timer->data);
  free(timer);
}

/*
  Helper function to be called when the game starts
*/
int init_timer_queue() {
  head = NULL;
  tail = NULL;
  return 0;
}

/*
  Helper function to be called when the game terminates
*/
void free_timer_queue() {
  TIMERS *curr = head;
  TIMERS *next;
  while (curr) {
    next = curr->next; 
    if (curr->data) {
      free(curr->data);
    }
    free(curr);
    curr = NULL;
    curr = next;
  }
  head = NULL;
  tail = NULL;
}

void print_timer_queue() {
  TIMERS *temp = head;
  while (temp) {
    printf("node: %p | Time: %f | mem: %p | set_to: %d\n",
            temp, temp->data->time, temp->data->mem, temp->data->set_to);
    temp = temp->next;  
  }
}

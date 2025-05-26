#ifndef WHEEL_TIMER_H
#define WHEEL_TIMER_H

#include <pthread.h>
#include "llist_event.h"

typedef struct _wheel_timer_t {
	int current_clock_tic;		/* Current slot number which is pointed to by the clock tic. Increase by 1 each second */
	int clock_tic_interval;		/* Time interval by which the clock tick moved. Default 1 sec */
	int wheel_size;			/* Total number of slots in the wheel */
	int current_cycle_no;		/* Number of rotations the clock has completed, R value */
	pthread_t wheel_thread;		/* Wheel timer thread */
	struct event *slots;		/* Linked list attached to the slots of the wheel timer, size is set by wheel_size */
	
} wheel_timer_t;

wheel_timer_t *create_timer(int interval, int size);
void start_timer(wheel_timer_t *timer);


#endif

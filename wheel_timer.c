#include "wheel_timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utility.h"
#include <time.h>

#define CLOCKID CLOCK_REALTIME

static void *event_function(void *arg);

/*
	This function creates a wheel timer
	IN: interval: defines the interval which each slot is executed at
	IN: size: defines the number of slots in the wheel 
		timer that events can be allocted to
	RETURN: a pointer to the wheel timer
*/
wheel_timer_t *create_timer(int interval, int size) {
	
	/* Allocate memory to the wheen timer and return a pointer 
		to the memory area */
	wheel_timer_t *tmp_wheel_timer =  
		(wheel_timer_t *) calloc(1, 
		sizeof(wheel_timer_t) + (size * sizeof(struct event *)));

	/* If the allocation of memory failes then exit */
	if (tmp_wheel_timer == NULL) {
		fprintf(stderr, 
			"Unable to allocate memory for the wheel timer!\n");
		exit(EXIT_FAILURE);
	}

	/* Set the number of slots in the clock wheel. */	
	tmp_wheel_timer->wheel_size = size;
	
	/* Define the base execution period of the wheel timer */
	tmp_wheel_timer->clock_tic_interval = interval;

	/* Initalize the current slot counter and cycles run variables */
	tmp_wheel_timer->current_cycle_no = 0;
	tmp_wheel_timer->current_clock_tic = 0;
	
	/* Allocate space for the number of slots defined by the user.
	   The slots pointer will point to this allocated memory of type struct event.
	*/
	tmp_wheel_timer->slots =  
		calloc(tmp_wheel_timer->wheel_size, sizeof(struct event *));
	
	/* If memory allocation fails then exit with error */
	if (tmp_wheel_timer->slots == NULL) {
		fprintf(stderr, "Unable to allocate memory for \
			wheel timer slots!\n");
		exit(EXIT_FAILURE);
	}

	/* Create link list for each slot and save the pointer 
		in the slots memory area */
	for (int i=0;i<tmp_wheel_timer->wheel_size;i++) {
		tmp_wheel_timer->slots[i] = init_list();
		if (tmp_wheel_timer->slots[i] == NULL) {
			fprintf(stderr, "Error occured during creating \
				of linked list for slot: %d\n", i);
			exit(EXIT_FAILURE);
		}
	}	
	return tmp_wheel_timer;
}

void start_timer(wheel_timer_t *timer) {
	
	/*POSIX timer */
	timer_t exec_timer;
	struct sigevent timer_notification;
	struct itemerspec timer_interval;
:


}


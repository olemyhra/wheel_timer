#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "wheel_timer.h"

void process(union sigval arg) {
	wheel_timer_t *timer = (wheel_timer_t *) arg.sival_ptr;
	
	if (timer->current_clock_tic < timer->wheel_size - 1) {
		timer->current_clock_tic++;
	} else {

		timer->current_clock_tic = 0;
		timer->current_cycle_no++;
	}

	printf("Clock tic: %d Cycle: %d\n", timer->current_clock_tic, timer->current_cycle_no);
	
	struct event* head = NULL;
	struct event* tmp = NULL;
	struct event* last = NULL;
	void * void_pointer = NULL;

	head = timer->slots[timer->current_clock_tic];
	tmp = head;

	while (tmp != NULL) {
		tmp->event_function((void *) &(timer->current_clock_tic));
		tmp = tmp->next;
	}
		
}

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

	return tmp_wheel_timer;
}

void start_timer(wheel_timer_t *timer) {
	
	/*POSIX timer */
	timer_t exec_timer;
	memset(&exec_timer, 0, sizeof(timer_t));

	struct sigevent timer_settings = {0};

	timer_settings.sigev_notify = SIGEV_THREAD;
	timer_settings.sigev_notify_function = process;
	timer_settings.sigev_value.sival_ptr = (void *) timer;
	if (timer_create(CLOCK_REALTIME, &timer_settings, &exec_timer) == -1 ) {
		fprintf(stderr, "Unable to create exec timer!\n");
		exit(EXIT_FAILURE);
	}


	struct itimerspec timer_interval = {0};

	timer_interval.it_value.tv_sec = timer->clock_tic_interval / 1000;
	timer_interval.it_value.tv_nsec = (timer->clock_tic_interval % 1000) * 1000000;
	timer_interval.it_interval.tv_sec = timer->clock_tic_interval / 1000;
	timer_interval.it_interval.tv_nsec = (timer->clock_tic_interval % 1000) * 1000000;

	if (timer_settime(exec_timer, 0, &timer_interval, NULL) == -1) {
		fprintf(stderr, "Error occuring setting exec timer interval!\n");
		exit(EXIT_FAILURE);
	}

}



void slot_scheduler(void (*event_function) (void *arg), int interval, 
		int arg_size, wheel_timer_t *timer) {
	
	int slot_allocation = 0;

	do {
		slot_allocation = (slot_allocation + interval) % timer->wheel_size;
		printf("Slot allocation is %d\n", slot_allocation);

		add_event(&(timer->slots[slot_allocation]),
			event_function, interval, arg_size);	

	} while (slot_allocation != 0);
}


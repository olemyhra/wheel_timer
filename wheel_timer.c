#include "wheel_timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void *event_function(void *arg);

wheel_timer_t *create_timer(int interval, int size) {

	wheel_timer_t *tmp_wheel_timer =  (wheel_timer_t *) calloc(1, sizeof(wheel_timer_t) + (size * sizeof(struct event *)));

	if (tmp_wheel_timer == NULL) {
		fprintf(stderr, "Unable to allocate memory for the wheel timer!\n");
		exit(EXIT_FAILURE);
	}

	tmp_wheel_timer->wheel_size = size;
	tmp_wheel_timer->clock_tic_interval = interval;
	tmp_wheel_timer->current_cycle_no = 0;
	tmp_wheel_timer->current_clock_tic = 0;

	memset((&tmp_wheel_timer->wheel_thread), 0, sizeof(wheel_timer_t));
	
	tmp_wheel_timer->slots = init_list();
	struct event *tmp_pointer = tmp_wheel_timer->slots + 1;
	
	for (int i=1;i<size;i++) {
		tmp_pointer = init_list();	
		tmp_pointer++;
	}
	
	return tmp_wheel_timer;
}

void start_timer(wheel_timer_t *timer) {
	pthread_t new_thread;
	if (pthread_create(&new_thread, NULL, &event_function, (void *) timer) != 0) {
		fprintf(stderr, "Unable to create wheel timer thread!\n");
		exit(EXIT_FAILURE);
	}
}

static void *event_function(void *arg)
{
	wheel_timer_t *timer = (wheel_timer_t *) arg;
	while(1) {
		timer->slots->event_function(NULL);
		sleep(1);
	}
	return NULL;
}


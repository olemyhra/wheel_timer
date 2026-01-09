#include <stdio.h>
#include <stdlib.h>
#include "wheel_timer.h"
#include <unistd.h>
#include "utility.h"


#define WHEEL_TIMER_TIC_INTERVAL 1000
#define WHEEL_TIMER_SLOTS 60

void event_one(void *arg);
void event_two(void *arg);

int main(void) {

	wheel_timer_t *wheel_timer = 
		create_timer(WHEEL_TIMER_TIC_INTERVAL, WHEEL_TIMER_SLOTS);

	check_null(wheel_timer);
	slot_scheduler(&event_one, 5, 0, wheel_timer);
	slot_scheduler(&event_two, 30, 0, wheel_timer);
	start_timer(wheel_timer);

	sleep(86400);

	free(wheel_timer);

	return EXIT_SUCCESS;
}

void event_one(void *arg) {
	int *slot_nr = (int *) arg;
	printf("Event1: Hello from slot %d!\n", *slot_nr);
}

void event_two(void *arg) {
	int *slot_nr = (int *) arg;
	printf("Event2: Hello from slot %d!\n", *slot_nr);
}

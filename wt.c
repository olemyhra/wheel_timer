#include <stdio.h>
#include <stdlib.h>
#include "wheel_timer.h"
#include <unistd.h>
#include "utility.h"

void event_one(void *arg);

int main(void) {

	wheel_timer_t *wheel_timer = create_timer(1, 10);
	check_null(wheel_timer);
	start_timer(wheel_timer);
	
	add_event(wheel_timer->slots, &event_one);

	sleep(30);
	free(wheel_timer);
	return EXIT_SUCCESS;
}

void event_one(void *arg) {
	printf("Hello from event 1!\n");
}



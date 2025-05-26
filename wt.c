#include <stdio.h>
#include <stdlib.h>
#include "wheel_timer.h"
#include <unistd.h>

int main(void) {

	wheel_timer_t *wheel_timer = create_timer(1, 10);
	start_timer(wheel_timer);
	
	sleep(30);
	free(wheel_timer);
	return EXIT_SUCCESS;
}



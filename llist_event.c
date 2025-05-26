#include "llist_event.h"
#include <stdlib.h>
#include <stdio.h>

struct event *init_list() {
	struct event *tmp = calloc(1, sizeof(struct event));
	if (tmp == NULL) {
		fprintf(stderr, "Unable to allocate memory to llist_event!\n");
		exit(EXIT_FAILURE);
	}

	return tmp;
}

void add_event(struct event *head, void (*event_function) (void *arg)) {

}



#include "llist_event.h"
#include <stdlib.h>
#include <stdio.h>

void add_event(struct event **head, void (*event_function) (void *arg), 
			int interval, int arg_size) {
	if (*head == NULL) {
		*head = calloc(1, sizeof(struct event));
		
		if (*head == NULL) {
			fprintf(stderr, "Unable to add event data structure!\n");
			exit(EXIT_FAILURE);
		} else {
			  
			(*head)->time_interval = interval;
			(*head)->event_function = event_function;
			(*head)->arg_size = arg_size;	
		}	
	} else {
		struct event* tmp = NULL;
		struct event* last = NULL;

		tmp = (*head)->next;
		last = *head;

		while (tmp != NULL) {
			last = tmp;
			tmp = tmp->next;
		}

		tmp = calloc(1, sizeof(struct event));
		
		if (tmp == NULL) {
			fprintf(stderr, "Unable to expand slot datastructure!\n");
			exit(EXIT_FAILURE);
		} else {
			tmp->time_interval = interval;
			tmp->event_function = event_function;
			tmp->arg_size = arg_size;
			last->next = tmp;
		}

	}
}

void free_list(struct event* head) {

	struct event* tmp = NULL;
	struct event* last = NULL;

	tmp = head;

	while (tmp != NULL) {
		last = tmp;
		tmp = tmp->next;
		free(last);
	 }
}

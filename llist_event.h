#ifndef LLIST_EVENT_H
#define LLIST_EVENT_H

#include <stdbool.h>

struct event {
	
	/* Pointer to the next event in the list */
	struct event *next;		

	/* Pointer to the function which shall be initated by the wheel timer */
	void (*event_function) (void *arg);

	/* Interval at which the function shall be executated within the execution cycle */
	int time_interval;

	/* Pointer to the arguments to pass to the function to be executed */
	void *arg;

	/* Size of the argument passed to the function */
	int arg_size;				
	
};

void add_event(struct event **head, void (*event_function) (void *arg), 
		int interval, int arg_size);

void free_list(struct event* head);
#endif

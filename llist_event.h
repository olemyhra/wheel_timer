#ifndef LLIST_EVENT_H
#define LLIST_EVENT_H

#include <stdbool.h>

struct event {
	struct event *next;			/* Pointer to the next event in the list */
	void (*event_function) (void *arg);	/* Pointer to the function which shall be initated by the wheel timer */
	int time_interval;			/* Interval at which the function shall be executated within the execution cycle */
	int execution_cycle;			/* In which execution cycle shall the function be executed */
	void *arg;				/* Pointer to the arguments to pass to the function to be executed */
	int arg_size;				/* Size of the argument passed to the function */
	bool recurrance;			/* Determines if the function shall be run as a one-shot event or be repeated endless */
	
};

struct event *init_list();
void add_event(struct event *head, void (*event_function) (void *arg));

#endif

#ifndef LLIST_EVENT_H
#define LLIST_EVENT_H

#include <stdbool.h>

struct event {
	struct event *next;
	void (*event_function) (void *arg);
	int time_interval;
	int execution_cycle;
	void *arg;
	int arg_size;
	bool recurrance;
	
};

struct event *init_list();
void add_event(struct event *head, void (*event_function) (void *arg));

#endif

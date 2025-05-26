CC = gcc
CFLAGS1 = -Wall -Werror -O2 -g3 -std=c17 -pedantic
DEPS = llist_event.h wheel_timer.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wt:	wt.o llist_event.o wheel_timer.o
	$(CC) $(CFLAGS1) wt.o llist_event.o wheel_timer.o -o $@

clean:
	rm -f  wt wt.o llist_event.o wheel_timer.o

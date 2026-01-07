CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: state_sort state_search clear_state

state_sort:
	$(CC) $(CFLAGS) state_sort.c -o ../build/Quest_1

state_search:
	$(CC) $(CFLAGS) state_search.c -o ../build/Quest_2

clear_state:
	$(CC) $(CFLAGS) clear_state.c -o ../build/Quest_3

clean:
	rm -f ../build/Quest_1 ../build/Quest_2 ../build/Quest_3

.PHONY: all state_sort state_search clear_state clean
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

SRC1 = state_sort.c
SRC2 = state_search.c
SRC3 = clear_state.c

OBJ1=$(patsubst %.c,%,$(SRC1))
OBJ2=$(patsubst %.c,%,$(SRC2))
OBJ3=$(patsubst %.c,%,$(SRC3))

BUILD = ../build

Q1 = $(BUILD)/Quest_1
Q2 = $(BUILD)/Quest_2
Q3 = $(BUILD)/Quest_3

.PHONY: all clean rebuild clean_all state_sort state_search clear_state

all: state_sort state_search clear_state

state_sort: clean $(Q1)
$(Q1): $(OBJ1)_q1.o
	$(CC) $^ -o $@
$(OBJ1)_q1.o: $(SRC1)
	$(CC) $(CFLAGS) $^ -o $@

state_search: clean $(Q2)
$(Q2): $(OBJ2)_q2.o
	$(CC) $^ -o $@
$(OBJ2)_q2.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

clear_state: clean $(Q3)
$(Q3): $(OBJ3)_q3.o
	$(CC) $^ -o $@
$(OBJ3)_q3.o: $(SRC3)
	$(CC) $(CFLAGS) $^ -o $@

clean_all:
	rm -rf *.o
	rm 	$(BUILD)/*

clean:
	rm -rf *.o

rebuild: clean all

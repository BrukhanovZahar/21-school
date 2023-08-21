CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

SRC1 = main_module_entry_point.c
SRC2 = print_module.c
SRC3 = documentation_module.c
SRC4 = bst_create_test.c
SRC5 = bst.c
SRC6 = bst_insert_test.c
SRC7 = bst_traverse_test.c

OBJ1=$(patsubst %.c,%,$(SRC1))
OBJ2=$(patsubst %.c,%,$(SRC2))
OBJ3=$(patsubst %.c,%,$(SRC3))
OBJ4=$(patsubst %.c,%,$(SRC4))
OBJ5=$(patsubst %.c,%,$(SRC5))
OBJ6=$(patsubst %.c,%,$(SRC6))
OBJ7=$(patsubst %.c,%,$(SRC7))

BUILD = ../build

Q1 = $(BUILD)/Quest_1
Q2 = $(BUILD)/Quest_2
Q3 = $(BUILD)/Quest_3
Q4 = $(BUILD)/Quest_4
Q5 = $(BUILD)/Quest_5

.PHONY: all clean rebuild print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

print_module: clean $(Q1)
$(Q1): $(OBJ1)_q1.o $(OBJ2)_q1.o
	$(CC) $^ -o $@
$(OBJ1)_q1.o: $(SRC1)
	$(CC) -DQ1 $(CFLAGS) $^ -o $@
$(OBJ2)_q1.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

documentation_module: clean $(Q2)
$(Q2): $(OBJ1)_q2.o $(OBJ3)_q2.o
	$(CC) $^ -o $@
$(OBJ1)_q2.o: $(SRC1)
	$(CC) -DQ2 $(CFLAGS) $^ -o $@
$(OBJ3)_q2.o: $(SRC3)
	$(CC) $(CFLAGS) $^ -o $@

bst_create_test: clean $(Q3)
$(Q3): $(OBJ4)_q3.o $(OBJ5)_q3.o
	$(CC) $^ -o $@
$(OBJ4)_q3.o: $(SRC4)
	$(CC) -DQ3 $(CFLAGS) $^ -o $@
$(OBJ5)_q3.o: $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

bst_insert_test: clean $(Q4)
$(Q4): $(OBJ6)_q4.o $(OBJ5)_q4.o
	$(CC) $^ -o $@
$(OBJ6)_q4.o: $(SRC6)
	$(CC) -DQ4 $(CFLAGS) $^ -o $@
$(OBJ5)_q4.o: $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

bst_traverse_test: clean $(Q5)
$(Q5): $(OBJ7)_q5.o $(OBJ5)_q5.o
	$(CC) $^ -o $@
$(OBJ7)_q5.o: $(SRC7)
	$(CC) -DQ5 $(CFLAGS) $^ -o $@
$(OBJ5)_q5.o: $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

clean_all:
	rm -rf *.o
	rm 	$(BUILD)/*

clean:
	rm -rf *.o

rebuild: clean all

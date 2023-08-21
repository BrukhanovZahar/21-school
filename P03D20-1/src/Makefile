CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

SRC1 = graph.c
SRC2 = evaluate_postfix.c
SRC3 = infix_to_postfix.c
SRC4 = parse_expression.c
SRC5 = rendering_image.c
SRC6 = stack.c

OBJ1=$(patsubst %.c,%,$(SRC1))
OBJ2=$(patsubst %.c,%,$(SRC2))
OBJ3=$(patsubst %.c,%,$(SRC3))
OBJ4=$(patsubst %.c,%,$(SRC4))
OBJ5=$(patsubst %.c,%,$(SRC5))
OBJ6=$(patsubst %.c,%,$(SRC6))

BUILD = ../build

Q = $(BUILD)/graph

.PHONY: all clean rebuild clean_all

all: $(OBJ1)_q.o $(OBJ2)_q.o $(OBJ3)_q.o $(OBJ4)_q.o $(OBJ5)_q.o $(OBJ6)_q.o
	$(CC) $^ -o $(Q)
$(OBJ1)_q.o: $(SRC1)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ2)_q.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ3)_q.o: $(SRC3)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ4)_q.o: $(SRC4)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ5)_q.o: $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ6)_q.o: $(SRC6)
	$(CC) $(CFLAGS) $^ -o $@

clean_all:
	rm -rf *.o
	rm 	$(BUILD)/*

clean:
	rm -rf *.o

rebuild: clean all

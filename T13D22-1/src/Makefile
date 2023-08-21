CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

SRC1 = cipher.c
SRC2 = logger.c

OBJ1=$(patsubst %.c,%,$(SRC1))
OBJ2=$(patsubst %.c,%,$(SRC2))

BUILD = ../build

Q1 = $(BUILD)/cipher
Q2 = $(BUILD)/logging_cipher

.PHONY: all clean rebuild clean_all cipher logging_cipher

all: cipher logging_cipher

cipher: clean $(Q1)
$(Q1): $(OBJ1)_q1.o
	$(CC) $^ -o $@
$(OBJ1)_q1.o: $(SRC1)
	$(CC) $(CFLAGS) $^ -o $@

logging_cipher: clean $(Q2)
$(Q2): $(OBJ1)_q2.o $(OBJ2)_q2.o
	$(CC) $^ -o $@
$(OBJ1)_q2.o: $(SRC1)
	$(CC) -DLOG $(CFLAGS) $^ -o $@
$(OBJ2)_q2.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

clean_all:
	rm -rf *.o
	rm 	$(BUILD)/*

clean:
	rm -rf *.o

rebuild: clean all

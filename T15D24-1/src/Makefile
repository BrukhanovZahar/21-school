CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11

SRC1 = modules_db.c
SRC2 = modules.c
SRC3 = levels.c
SRC4 = status_events.c
SRC5 = shared.c

OBJ1 = $(patsubst %.c,%,$(SRC1))
OBJ2 = $(patsubst %.c,%,$(SRC2))
OBJ3 = $(patsubst %.c,%,$(SRC3))
OBJ4 = $(patsubst %.c,%,$(SRC4))
OBJ5 = $(patsubst %.c,%,$(SRC5))

BUILD = ../build

Q1 = $(BUILD)/database

.PHONY : all clean rebuild clean_all build_db

all : build_db

build_db : clean $(Q1)
$(Q1): $(OBJ1)_q1.o $(OBJ2)_q1.o $(OBJ3)_q1.o $(OBJ4)_q1.o $(OBJ5)_q1.o
	$(CC) $^ -o $@
$(OBJ1)_q1.o : $(SRC1)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ2)_q1.o : $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ3)_q1.o : $(SRC3)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ4)_q1.o : $(SRC4)
	$(CC) $(CFLAGS) $^ -o $@
$(OBJ5)_q1.o : $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

clean_all:
	rm -rf *.o
	rm $(BUILD)/*

clean:
	rm -rf *.o

rebuild: clean all

CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
BUILD_DIR = ../../build

PREFIX1 = ../data_libs
PREFIX2 = ../data_module
PREFIX3 = ../yet_another_decision_module

SRC11=$(PREFIX1)/data_io.c
SRC12=$(PREFIX1)/data_stat.c
SRC2 = $(PREFIX2)/data_process.c
SRC3 = $(PREFIX3)/decision.c
SRC4 = main_executable_module.c

SOURCES = $(SRC11) $(SRC12) $(SRC2) $(SRC3) $(SRC4)
SOURCES_Q5 = $(SRC11) $(SRC2) $(SRC3) $(SRC4)
SOURCES_Q6 = $(SRC11) $(SRC12) $(SRC3) $(SRC4)

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_Q5 = $(SOURCES_Q5:.c=.o)
OBJECT12 = $(SRC12:.c=.o)
OBJECT2 = $(SRC2:.c=.o)
OBJECTS_Q6 = $(SOURCES_Q6:.c=.o)

Q3 = $(BUILD_DIR)/Quest_3
Q4 = $(BUILD_DIR)/Quest_4
Q5 = $(BUILD_DIR)/Quest_5
Q6 = $(BUILD_DIR)/Quest_6

.PHONY: all clean rebuild

all: $(Q3)

$(Q3): $(OBJECTS)
	$(CC) $^ -o $@

$(Q4): $(OBJECTS)
	$(CC) $^ -o $@

$(Q5): $(OBJECTS_Q5)
	$(CC) $(PREFIX1)/data_stat.a $^ -o $@

$(Q6): $(OBJECTS_Q6)
	$(CC) $(PREFIX2)/data_process.so $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

data_stat.a: $(OBJECT12)
	ar -rcs $(PREFIX1)/$@ $<

data_process.so:
	$(CC) -shared -fPIC $(SRC12) $(SRC2) -o $(PREFIX2)/$@

build_with_macro: CFLAGS += -DMACRO_MODE
build_with_macro: clean $(Q4)

build_with_static: clean data_stat.a $(Q5)

build_with_dynamic: clean data_process.so $(Q6)

clean:
	find ../ -name "*.o" -type f -delete
	find ../ -name "*.a" -type f -delete
	find ../ -name "*.so" -type f -delete
	#rm -f $(Q3) $(Q4) $(Q5) $(Q6)

rebuild: clean all

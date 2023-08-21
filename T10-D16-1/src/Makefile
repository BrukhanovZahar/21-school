CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
BUILD_DIR = ../build

SRC1 = s21_string_test.c
SRC2 = s21_string.c
SRC3 = text_processor.c

OBJECT1=$(patsubst %.c,%,$(SRC1))
OBJECT2=$(patsubst %.c,%,$(SRC2))

Q1 = $(BUILD_DIR)/Quest_1
Q2 = $(BUILD_DIR)/Quest_2
Q3 = $(BUILD_DIR)/Quest_3
Q4 = $(BUILD_DIR)/Quest_4
Q5 = $(BUILD_DIR)/Quest_5
Q6 = $(BUILD_DIR)/Quest_6
Q7 = $(BUILD_DIR)/Quest_7
Q8 = $(BUILD_DIR)/Quest_8

.PHONY: all clean rebuild

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_processor

strlen_tests: clean $(Q1)
$(Q1): $(OBJECT1)_q1.o $(OBJECT2)_q1.o
	$(CC) $^ -o $@
$(OBJECT1)_q1.o: $(SRC1)
	$(CC) -DQ1 $(CFLAGS) $^ -o $@
$(OBJECT2)_q1.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strcmp_tests: clean $(Q2)
$(Q2): $(OBJECT1)_q2.o $(OBJECT2)_q2.o
	$(CC) $^ -o $@
$(OBJECT1)_q2.o: $(SRC1)
	$(CC) -DQ2 $(CFLAGS) $^ -o $@
$(OBJECT2)_q2.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strcpy_tests: clean $(Q3)
$(Q3): $(OBJECT1)_q3.o $(OBJECT2)_q3.o
	$(CC) $^ -o $@
$(OBJECT1)_q3.o: $(SRC1)
	$(CC) -DQ3 $(CFLAGS) $^ -o $@
$(OBJECT2)_q3.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strcat_tests: clean $(Q4)
$(Q4): $(OBJECT1)_q4.o $(OBJECT2)_q4.o
	$(CC) $^ -o $@
$(OBJECT1)_q4.o: $(SRC1)
	$(CC) -DQ4 $(CFLAGS) $^ -o $@
$(OBJECT2)_q4.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strchr_tests: clean $(Q5)
$(Q5): $(OBJECT1)_q5.o $(OBJECT2)_q5.o
	$(CC) $^ -o $@
$(OBJECT1)_q5.o: $(SRC1)
	$(CC) -DQ5 $(CFLAGS) $^ -o $@
$(OBJECT2)_q5.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strstr_tests: clean $(Q6)
$(Q6): $(OBJECT1)_q6.o $(OBJECT2)_q6.o
	$(CC) $^ -o $@
$(OBJECT1)_q6.o: $(SRC1)
	$(CC) -DQ6 $(CFLAGS) $^ -o $@
$(OBJECT2)_q6.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

strtok_tests: clean $(Q7)
$(Q7): $(OBJECT1)_q7.o $(OBJECT2)_q7.o
	$(CC) $^ -o $@
$(OBJECT1)_q7.o: $(SRC1)
	$(CC) -DQ7 $(CFLAGS) $^ -o $@
$(OBJECT2)_q7.o: $(SRC2)
	$(CC) $(CFLAGS) $^ -o $@

text_processor: $(SRC3)
	$(CC) -Wall -Werror -Wextra $^ -o $(Q8)

clean_all:
	rm -rf *.o **/*.o
	rm 	$(BUILD_DIR)/*

clean:
	rm -rf *.o **/*.o

rebuild: clean all

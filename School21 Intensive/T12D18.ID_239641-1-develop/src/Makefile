CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

SRC1 = main_module_entry_point.c
SRC2 = print_module.c
SRC3 = documentation_module.c
SRC4 = bst_create_test.c
SRC5 = bst.c
SRC6 = bst_insert_test.c
SRC7 = bst_traverse_test.c

BUILD = ../build

Q1 = $(BUILD)/Quest_1
Q2 = $(BUILD)/Quest_2
Q3 = $(BUILD)/Quest_3
Q4 = $(BUILD)/Quest_4
Q5 = $(BUILD)/Quest_5

.PHONY: all clean rebuild print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

all: print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

print_module: $(Q1)
$(Q1): $(SRC1) $(SRC2)
	$(CC) $(CFLAGS) -DQ1 $^ -o $@

documentation_module: $(Q2)
$(Q2): $(SRC1) $(SRC3)
	$(CC) $(CFLAGS) -DQ2 $^ -o $@

bst_create_test: $(Q3)
$(Q3): $(SRC4) $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

bst_insert_test: $(Q4)
$(Q4): $(SRC6) $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

bst_traverse_test: $(Q5)
$(Q5): $(SRC7) $(SRC5)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)/*

rebuild: clean all

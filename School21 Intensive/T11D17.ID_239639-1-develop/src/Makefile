# === Compiler & Flags ===
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
BUILD_DIR = ../build

# Executables
TARGETS = Quest_1 Quest_2 Quest_3

# Source groups
SRC_DOOR = dmanager_module.c
SRC_LIST = list.c list_test.c
SRC_STACK = stack.c stack_test.c

# === Phony ===
.PHONY: all clean format valgrind_all valgrind_door valgrind_list valgrind_stack

# === Default build ===
all: format $(addprefix $(BUILD_DIR)/,$(TARGETS)) valgrind_all
	@echo "All builds and Valgrind checks completed successfully!"

# === Create build directory ===
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	touch $(BUILD_DIR)/.gitkeep

# === Clang-format ===
format:
	@echo "🧹 Running clang-format..."
	@clang-format -i *.c *.h
	@echo "✨ Format check complete!"

# === Build rules ===
$(BUILD_DIR)/Quest_1: $(SRC_DOOR) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DOOR) -o $@

$(BUILD_DIR)/Quest_2: $(SRC_LIST) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_LIST) -o $@

$(BUILD_DIR)/Quest_3: $(SRC_STACK) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_STACK) -o $@

# === Valgrind on all ===
valgrind_all:
	@echo " Running Valgrind memory checks..."
	@for quest in $(TARGETS); do \
		if [ -f "$(BUILD_DIR)/$$quest" ]; then \
			echo "Checking $$quest ..."; \
			valgrind --quiet --leak-check=full --error-exitcode=1 $(BUILD_DIR)/$$quest || exit 1; \
			echo "$$quest passed Valgrind test."; \
			echo "--------------------------------------------"; \
		fi; \
	done

# === Individual valgrind targets ===
valgrind_door:
	valgrind --leak-check=full $(BUILD_DIR)/Quest_1

valgrind_list:
	valgrind --leak-check=full $(BUILD_DIR)/Quest_2

valgrind_stack:
	valgrind --leak-check=full $(BUILD_DIR)/Quest_3

# === Clean (preserves .gitkeep) ===
clean:
	find $(BUILD_DIR) -type f ! -name ".gitkeep" -delete
	@echo "🧽 Clean complete!"
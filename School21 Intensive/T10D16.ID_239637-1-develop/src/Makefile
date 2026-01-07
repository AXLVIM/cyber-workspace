# === Compiler & Flags ===
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
BUILD_DIR = ../build
TARGETS = Quest_1 Quest_2 Quest_3 Quest_4 Quest_5 Quest_6 Quest_7 Quest_8

# === Phony targets ===
.PHONY: all clean format check strlen_tests strcmp_tests strcpy_tests strcat_tests \
        strchr_tests strstr_tests strtok_tests text_processor valgrind_all

# === Default: run format + build + valgrind ===
all: format $(addprefix $(BUILD_DIR)/,$(TARGETS)) valgrind_all
	@echo "All builds and Valgrind checks completed successfully!"

# === Auto-create build dir ===
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# === Code formatting ===
format:
	@echo "🧹 Running clang-format..."
	@clang-format -i *.c *.h
	@echo "✨ Format check complete!"

# === Individual build rules ===
$(BUILD_DIR)/Quest_1: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRLEN $^ -o $@

$(BUILD_DIR)/Quest_2: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRCMP $^ -o $@

$(BUILD_DIR)/Quest_3: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRCPY $^ -o $@

$(BUILD_DIR)/Quest_4: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRCAT $^ -o $@

$(BUILD_DIR)/Quest_5: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRCHR $^ -o $@

$(BUILD_DIR)/Quest_6: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRSTR $^ -o $@

$(BUILD_DIR)/Quest_7: s21_string_test.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DTEST_STRTOK $^ -o $@

$(BUILD_DIR)/Quest_8: text_processor.c s21_string.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# === Run Valgrind on all builds ===
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

# === Clean everything ===
clean:
	rm -f $(addprefix $(BUILD_DIR)/,$(TARGETS))
	@echo "🧽 Clean complete!"

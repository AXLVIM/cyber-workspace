#!/bin/bash
# src/edit.sh
# Usage: ./src/edit.sh <file_path> <search_string> <replacement_string>

LOG_FILE="src/files.log"

# Function to print errors and exit
error_exit() {
    echo "Error: $1" >&2
    exit 1
}

# --- Validation ---
[ $# -ne 3 ] && error_exit "Usage: $0 <file_path> <search_string> <replacement_string>"

FILE_PATH="$1"
SEARCH="$2"
REPLACE="$3"

# Resolve relative path
ROOT_DIR="$(git rev-parse --show-toplevel 2>/dev/null || echo .)"
TARGET_FILE="$ROOT_DIR/$FILE_PATH"

[ ! -f "$TARGET_FILE" ] && error_exit "File '$FILE_PATH' does not exist."
[ ! -r "$TARGET_FILE" ] && error_exit "File '$FILE_PATH' is not readable."
[ ! -w "$TARGET_FILE" ] && error_exit "File '$FILE_PATH' is not writable."

# --- Do the replacement safely ---
# Escape search and replace strings for sed
ESC_SEARCH=$(printf '%s\n' "$SEARCH" | sed -e 's/[\/&]/\\&/g')
ESC_REPLACE=$(printf '%s\n' "$REPLACE" | sed -e 's/[\/&]/\\&/g')

# Make a temp copy to detect changes
TMP_FILE=$(mktemp)
cp "$TARGET_FILE" "$TMP_FILE"

# Perform the replacement (global)
sed -i "s/${ESC_SEARCH}/${ESC_REPLACE}/g" "$TARGET_FILE"

# --- Logging ---
# Check if a change was actually made
if ! cmp -s "$TMP_FILE" "$TARGET_FILE"; then
    TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')
    mkdir -p "$(dirname "$LOG_FILE")"
    echo "$TIMESTAMP | $FILE_PATH | '$SEARCH' -> '$REPLACE'" >> "$LOG_FILE"
else
    echo "No occurrences of '$SEARCH' found in $FILE_PATH."
fi

rm -f "$TMP_FILE"
exit 0

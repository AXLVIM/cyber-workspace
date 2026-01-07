#!/bin/bash
# src/log_analyzer.sh
# Usage: ./src/log_analyzer.sh <path_to_log_file>

error_exit() {
    echo "Error: $1" >&2
    exit 1
}

# --- Validation ---
[ $# -ne 1 ] && error_exit "Usage: $0 <path_to_log_file>"

FILE_PATH="$1"
ROOT_DIR="$(git rev-parse --show-toplevel 2>/dev/null || echo .)"
LOG_FILE="$ROOT_DIR/$FILE_PATH"

[ ! -f "$LOG_FILE" ] && error_exit "File '$FILE_PATH' does not exist."
[ ! -r "$LOG_FILE" ] && error_exit "File '$FILE_PATH' is not readable."

# --- Initialize counters ---
total=0
declare -A last_hash
declare -A hash_changes

# --- Parse log file ---
while IFS='-' read -r path size date hash alg rest; do
    # Skip invalid or empty lines
    [[ -z "$path" || -z "$hash" ]] && continue

    ((total++))

    # Trim whitespace
    path=$(echo "$path" | xargs)
    hash=$(echo "$hash" | xargs)

    # Check for hash change
    if [[ -n "${last_hash[$path]}" && "${last_hash[$path]}" != "$hash" ]]; then
        ((hash_changes[$path]++))
    fi
    last_hash[$path]="$hash"
done < "$LOG_FILE"

# --- Calculate results ---
unique_files=${#last_hash[@]}

# Sum up all hash changes
changes=0
for f in "${!hash_changes[@]}"; do
    ((changes += hash_changes[$f]))
done

# --- Output ---
echo "$total $unique_files $changes"
exit 0
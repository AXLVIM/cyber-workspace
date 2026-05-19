# File Testing

> [!info] **Purpose**  
> This note explains how to test file attributes (existence, type, permissions, age) using Bash conditional expressions. File tests are essential for writing robust scripts that handle files safely.

---

## Table of Contents

- [[#What are File Tests?]]
- [[#Basic File Tests]]
- [[#Permission Tests]]
- [[#Special File Tests]]
- [[#Comparison Tests (age, links)]]
- [[#Using File Tests in Conditionals]]
- [[#Common Patterns]]
- [[#Portability Notes]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What are File Tests?

File tests are unary or binary operators used inside `[ ]` or `[[ ]]` to check properties of files and directories. They allow your script to answer questions like:

- Does this file exist?
- Is it a regular file or a directory?
- Can I read it? Write to it? Execute it?
- Which file is newer?

> [!tip] Always use file tests before attempting to access a file. They prevent errors and make scripts robust.

---

## Basic File Tests

These tests check existence and file type.

| Operator | Meaning | Example |
|----------|---------|---------|
| `-e file` | File exists (any type) | `[[ -e /etc/passwd ]]` |
| `-f file` | File exists and is a regular file (not directory, device, etc.) | `[[ -f config.txt ]]` |
| `-d file` | File exists and is a directory | `[[ -d /home/user ]]` |
| `-s file` | File exists and size is greater than zero (not empty) | `[[ -s logfile ]]` |
| `-L file` | File exists and is a symbolic link | `[[ -L /usr/bin/python ]]` |
| `-h file` | Same as `-L` | |

**Examples:**
```bash
if [[ -e "$filename" ]]; then
    echo "$filename exists"
fi

if [[ -f "$filename" ]]; then
    echo "$filename is a regular file"
elif [[ -d "$filename" ]]; then
    echo "$filename is a directory"
fi

if [[ -s "$logfile" ]]; then
    echo "Log file is not empty"
fi
```

---

## Permission Tests

These tests check access permissions for the **effective user** running the script.

|Operator|Meaning|
|---|---|
|`-r file`|File exists and is readable|
|`-w file`|File exists and is writable|
|`-x file`|File exists and is executable|
|`-O file`|File exists and is owned by the effective user ID|
|`-G file`|File exists and is owned by the effective group ID|

**Examples:**
```bash
if [[ -r "$config" ]]; then
    source "$config"
else
    echo "Cannot read config file" >&2
    exit 1
fi

if [[ -w "$output" ]]; then
    echo "Data" > "$output"
else
    echo "Cannot write to $output" >&2
fi

if [[ -x "$script" ]]; then
    ./"$script"
fi
```

> [!note] Permission tests respect the actual permissions (read/write/execute) of the file, not just the presence of the file.

---

## Special File Tests

These tests detect block devices, character devices, sockets, and pipes (advanced, less common).

|Operator|Meaning|
|---|---|
|`-b file`|Block device (e.g., `/dev/sda`)|
|`-c file`|Character device (e.g., `/dev/tty`)|
|`-p file`|Named pipe (FIFO)|
|`-S file`|Socket|

---

## Comparison Tests (age, links)

These binary operators compare two files.

|Operator|Meaning|
|---|---|
|`file1 -nt file2`|`file1` is newer than `file2` (by modification time)|
|`file1 -ot file2`|`file1` is older than `file2`|
|`file1 -ef file2`|`file1` and `file2` refer to the same inode (hard links)|

**Examples:**
```bash
if [[ "$source" -nt "$destination" ]]; then
    echo "Source is newer, copying..."
    cp "$source" "$destination"
fi

if [[ "$file1" -ef "$file2" ]]; then
    echo "Both files are the same (hard links)"
fi
```

---
## Using File Tests in Conditionals

File tests are most commonly used in `if` statements, but they can also be used with `&&`, `||`, and `test` command.

**With `if`:**
```bash
if [[ -d "$dir" && -w "$dir" ]]; then
    echo "Directory exists and is writable"
fi
```

**With `&&` and `||` (short‑circuit):**
```bash
[[ -f "$file" ]] && echo "File exists" || echo "File missing"
```

**With `test` command (equivalent to `[ ]`):**
```bash
test -f "$file" && echo "File exists"
```

---
## Common Patterns

### Safe file copy (overwrite confirmation)

```bash
if [[ -f "$dest" ]]; then
    read -p "Destination exists. Overwrite? (y/n) " answer
    if [[ $answer != [Yy] ]]; then
        echo "Aborted"
        exit 1
    fi
fi
cp "$src" "$dest"
```

### Create directory if it doesn’t exist

```bash
if [[ ! -d "$dirname" ]]; then
    mkdir -p "$dirname"
fi
# Shorter: mkdir -p "$dirname"
```

### Wait for a file to appear (with timeout)

```bash
timeout=30
elapsed=0
while [[ ! -f "$file" && $elapsed -lt $timeout ]]; do
    sleep 1
    ((elapsed++))
done
if [[ -f "$file" ]]; then
    echo "File appeared"
else
    echo "Timeout waiting for $file"
fi
```

### Backup existing file before overwriting

```bash
if [[ -f "$target" ]]; then
    backup="${target}.$(date +%Y%m%d_%H%M%S)"
    cp "$target" "$backup"
    echo "Backed up to $backup"
fi
```

---
## Portability Notes

- The `[[ ]]` construct is Bash‑specific. For POSIX `sh` scripts, use `[ ]` instead.
    
- All file test operators listed above work in `[ ]` as well (except some Bash extensions).
    
- `-nt`, `-ot`, `-ef` are POSIX (but some older shells may lack them). For maximum portability, use `find` or `stat` instead.


**POSIX‑compliant version:**
```bash
if [ -f "$file" ]; then
    echo "File exists"
fi
```

---
## Best Practices

1. **Test before you act** – always check existence before reading/writing.
    
2. **Use `-f` for regular files**, not just `-e` (unless you explicitly accept directories or devices).
    
3. **Check permissions** (`-r`, `-w`, `-x`) before attempting operations.
    
4. **Quote variables** – `[[ -f "$file" ]]` (safe even if `$file` is empty or has spaces).
    
5. **Use `-s` to detect empty files** – avoids processing empty logs or configs.
    
6. **Combine tests with `&&` and `||`** inside `[[ ]]` for clarity.


---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`if [ -f $file ]`|Unquoted variable splits or expands globs|`if [[ -f "$file" ]]`|
|Using `-e` when you need `-f`|Directories also pass `-e`, leading to wrong assumptions|`-f` for regular files|
|Forgetting `-r` before reading a file|File may exist but be unreadable (permissions)|Check `-r`|
|Using `-s` to test existence|Empty file exists but `-s` returns false|Use `-e` or `-f` for existence|
|Testing a symlink with `-f`|Follows symlink; `-f` on broken symlink returns false|Use `-L` to test symlink itself|

---

## Next Steps

You can practice by writing a script that:

- Recursively finds all empty files in a directory (`-s`).
    
- Checks if a configuration file is readable before sourcing it.
    
- Compares two directories and reports which files are newer.


> [!tip] **Link this note**  
> Add `- [ ] [[File Testing]]` to your [[Bash Scripting]] MOC under "Advanced Techniques".

---

**End of note.**  
This is your complete reference for testing file attributes in Bash. Use these operators to write defensive, reliable scripts.
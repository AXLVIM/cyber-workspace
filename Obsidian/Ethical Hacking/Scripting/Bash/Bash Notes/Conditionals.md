# Conditionals

> [!info] **Purpose**  
> This note explains how to make decisions in Bash scripts using conditional statements. Conditionals allow your script to execute different commands based on whether a condition is true or false.

---

## Table of Contents

- [[#What are Conditionals?]]
- [[#The `if` Statement]]
- [[#Test Constructs: `[ ]` vs `[[ ]]`]]
- [[#Numeric Comparisons]]
- [[#String Comparisons]]
- [[#File Testing]]
- [[#Logical Operators (AND, OR, NOT)]]
- [[#The `case` Statement]]
- [[#Conditional Execution (&& and ||)]]
- [[#Exit Status as Condition]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What are Conditionals?

Conditionals allow a script to choose different paths of execution based on data, user input, file properties, or command results.

**Basic idea:**

if something is true  
do this  
else  
do that

```text
**Real‑world example:**
```bash
if [ -f "/etc/config" ]; then
    source /etc/config
else
    echo "Config missing, using defaults"
fi
```

---
## The `if` Statement

### Syntax

```bash
if condition; then
    commands
fi
```

With `else`:
```bash
if condition; then
    commands
else
    other commands
fi
```

With `elif` (else if):
```bash
if condition1; then
    commands1
elif condition2; then
    commands2
else
    commands3
fi
```

>[!note] The semicolon before `then` is required if `then` is on the same line. You can also put `then` on the next line:
```bash
if condition
then
    commands
fi
```

### Example

```bash
read -p "Enter a number: " num
if [ "$num" -gt 10 ]; then
    echo "Greater than 10"
elif [ "$num" -eq 10 ]; then
    echo "Equal to 10"
else
    echo "Less than 10"
fi
```

---
## Test Constructs: `[ ]` vs `[[ ]]`

Bash provides two ways to write conditions:

|Construct|POSIX‑compatible|Bash‑specific|Features|
|---|---|---|---|
|`[ condition ]`|Yes|No (but works in Bash)|Must quote variables, no regex, no `&&`/`\|` inside (use `-a`/`-o`)|
|`[[ condition ]]`|No|Yes (Bash/Zsh/Ksh)|No quoting needed, `&&`/`\|` inside, regex `=~`, pattern matching|

> [!tip] **Recommendation**  
> Use `[[ ]]` in Bash scripts – it's safer and more readable. Use `[ ]` only if you need POSIX `sh` compatibility.

**Comparison:**
```bash
# With [ ] – quoting required
if [ "$name" = "Alice" ]; then ...

# With [[ ]] – quoting optional (but harmless)
if [[ $name == Alice ]]; then ...
```

---
## Numeric Comparisons

Inside `[ ]` or `[[ ]]`, use these operators for numbers:

|Operator|Meaning|Example (`[[ ]]`)|
|---|---|---|
|`-eq`|equal|`[[ $a -eq $b ]]`|
|`-ne`|not equal|`[[ $a -ne $b ]]`|
|`-gt`|greater than|`[[ $a -gt $b ]]`|
|`-lt`|less than|`[[ $a -lt $b ]]`|
|`-ge`|greater or equal|`[[ $a -ge $b ]]`|
|`-le`|less or equal|`[[ $a -le $b ]]`|

**Example:**
```bash
age=25
if [[ $age -ge 18 ]] && [[ $age -lt 65 ]]; then
    echo "Working age"
fi
```

> [!warning] Do not use `<` or `>` inside `[ ]` for numbers – they compare lexicographically as strings. Use `-lt` and `-gt`.

---

## String Comparisons

|Operator|Meaning|Example (`[[ ]]`)|
|---|---|---|
|`==` or `=`|equal|`[[ $str1 == $str2 ]]`|
|`!=`|not equal|`[[ $str1 != $str2 ]]`|
|`<`|lexicographically less|`[[ $str1 < $str2 ]]`|
|`>`|lexicographically greater|`[[ $str1 > $str2 ]]`|
|`-z`|string is empty (zero length)|`[[ -z $str ]]`|
|`-n`|string is not empty|`[[ -n $str ]]`|

**Examples:**
```bash
name="Alice"
if [[ $name == "Alice" ]]; then
    echo "Hi Alice"
fi

if [[ -z $name ]]; then
    echo "Name is empty"
fi

# Pattern matching (glob)
if [[ $name == A* ]]; then
    echo "Starts with A"
fi

# Regex matching (Bash 3.0+)
if [[ $name =~ ^A.*e$ ]]; then
    echo "Starts with A, ends with e"
fi
```

> [!tip] Always quote strings when using `[ ]`, but in `[[ ]]` quoting is optional. Use `[[ $str == "literal" ]]` for safety.

---

## File Testing

File test operators check properties of files and directories. See also [[File Testing]] for full reference.

Common operators:

|Operator|True if|
|---|---|
|`-e file`|file exists|
|`-f file`|exists and is a regular file|
|`-d file`|exists and is a directory|
|`-r file`|readable|
|`-w file`|writable|
|`-x file`|executable|
|`-s file`|exists and size > 0|
|`-L file`|exists and is symbolic link|

**Examples:**
```bash
if [[ -f "$config_file" ]]; then
    source "$config_file"
elif [[ -d "/etc/default" ]]; then
    echo "Directory exists"
fi

if [[ ! -r "$log" ]]; then
    echo "Cannot read log file" >&2
    exit 1
fi
```

---
## Logical Operators (AND, OR, NOT)

### Inside `[[ ]]` (preferred)

|Operator|Meaning|Example|
|---|---|---|
|`&&`|AND|`[[ $age -gt 18 && $age -lt 65 ]]`|
|`\|`|OR|`[[ $day == Sat \| $day == Sun ]]`|
|`!`|NOT|`[[ ! -f $file ]]`|

### Inside `[ ]` (POSIX)

|Operator|Meaning|Example|
|---|---|---|
|`-a`|AND|`[ $age -gt 18 -a $age -lt 65 ]`|
|`-o`|OR|`[ $day = Sat -o $day = Sun ]`|
|`!`|NOT|`[ ! -f $file ]`|

### Outside any test construct

You can combine entire `[[ ]]` expressions with `&&` and `||`:
```bash
if [[ $age -gt 18 ]] && [[ $age -lt 65 ]]; then
    echo "Working age"
fi
```

> [!tip] Use `&&` and `||` outside `[[ ]]` for clarity. Avoid `-a` and `-o` inside `[ ]` (they are unreliable with some shells).

---

## The `case` Statement

`case` is cleaner than multiple `elif` statements when comparing a single value against many patterns.

### Syntax

```bash
case expression in
    pattern1)
        commands
        ;;
    pattern2|pattern3)
        commands
        ;;
    *)
        default commands
        ;;
esac
```

### Patterns

- `*` – any string (wildcard)
    
- `?` – any single character
    
- `[abc]` – character class
    
- `pattern1|pattern2` – alternation

### Examples

**Simple menu:**
```bash
read -p "Choose (start/stop/restart): " action
case $action in
    start|START|Start)
        echo "Starting service..."
        ;;
    stop)
        echo "Stopping service..."
        ;;
    restart)
        echo "Restarting service..."
        ;;
    *)
        echo "Invalid choice"
        ;;
esac
```

**Matching file extensions:**
```bash
filename="image.jpg"
case $filename in
    *.jpg|*.jpeg|*.png)
        echo "Image file"
        ;;
    *.txt|*.md)
        echo "Text file"
        ;;
    *)
        echo "Unknown type"
        ;;
esac
```

**Checking command output:**
```bash
case $(uname) in
    Linux) echo "Linux system" ;;
    Darwin) echo "macOS system" ;;
    CYGWIN*|MINGW*) echo "Windows with Cygwin/MinGW" ;;
    *) echo "Unknown OS" ;;
esac
```

> [!note] `case` does not perform regular expression matching – only glob patterns. Use `[[ =~ ]]` for regex.

---

## Conditional Execution (&& and ||)

You can use `&&` (AND) and `||` (OR) as short‑circuit conditional operators outside `if`.

- `command1 && command2` – run `command2` only if `command1` succeeds (exit 0).
    
- `command1 || command2` – run `command2` only if `command1` fails (non‑zero exit).
    

**Examples:**
```bash
# Create directory only if it doesn't exist
mkdir -p "$dir" || echo "Failed to create $dir"

# Copy and then remove if copy succeeded
cp file backup/ && rm file

# Set default value
[[ -z $name ]] && name="Anonymous"
```

This pattern is common for concise error handling and defaults.

---
## Exit Status as Condition

In Bash, any command can be used as a condition. The command is considered "true" if it exits with status 0, and "false" otherwise.
```bash
if grep -q "error" logfile.txt; then
    echo "Errors found"
fi

if cd /some/directory; then
    echo "Changed directory successfully"
else
    echo "Cannot change directory"
fi
```

You can also use `!` to invert the exit status:
```bash
if ! grep -q "success" logfile.txt; then
    echo "No success message found"
fi
```

---
## Best Practices

1. **Prefer `[[ ]]` over `[ ]`** for Bash scripts – it's safer and supports more features.
    
2. **Quote variables in `[ ]`** – `[ "$var" = "value" ]`. In `[[ ]]` quoting is optional but harmless.
    
3. **Use `case` for multiple pattern matching** – more readable than long `if-elif` chains.
    
4. **Use `(( ))` for arithmetic conditions** – `if (( a > b )); then` (clearer than `-gt`).
    
5. **Combine conditions with `&&` and `||` outside `[[ ]]`** for readability.
    
6. **Test for empty strings explicitly** with `-z` or `-n`.
    
7. **Use `-f` before reading files**, `-d` before `cd`, `-x` before executing.


---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`if [ $age > 18 ]`|`>` is output redirection, not comparison|`if [[ $age -gt 18 ]]`|
|Missing spaces: `[ "$a"="$b" ]`|No space around `=` → single string|`[ "$a" = "$b" ]`|
|Using `=` with `[[ ]]` for pattern match? Actually `=` works but `==` is clearer|–|`[[ $name == A* ]]`|
|Forgetting `then`|Syntax error|Add `then` after condition|
|Using `-a` inside `[ ]` with empty variables|Can break; use `&&` instead|`[ -n "$var1" ] && [ -n "$var2" ]`|
|`if [ "$var" ]`|Checks if string non‑empty, but not explicit|Use `if [[ -n $var ]]` or `if [[ $var != "" ]]`|

---

## Next Steps

You can practice by writing a script that:

- Asks for a number and tells if it's positive, negative, or zero.
    
- Checks if a file exists; if not, creates it.
    
- Uses `case` to handle user menu choices.


> [!tip] **Link this note**  
> Add `- [ ] [[Conditionals]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for conditionals in Bash. Use it to make your scripts intelligent and responsive.
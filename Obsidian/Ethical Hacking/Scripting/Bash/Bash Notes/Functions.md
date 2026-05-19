# Functions

> [!info] **Purpose**  
> This note explains how to define and use functions in Bash scripts. Functions allow you to group commands into reusable blocks, avoid code duplication, and structure your scripts more clearly.

---

## Table of Contents

- [[#What are Functions?]]
- [[#Defining Functions]]
- [[#Calling Functions]]
- [[#Function Arguments]]
- [[#Return Values]]
- [[#Variable Scope (local vs global)]]
- [[#Exit Status and `return`]]
- [[#Recursion]]
- [[#Functions in Scripts vs Interactive Shell]]
- [[#Exporting Functions]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What are Functions?

A **function** is a named block of code that can be called multiple times from different places in a script. Functions help you:

- **Avoid repetition** – write a block once, use it many times.
- **Organize logic** – group related commands under a descriptive name.
- **Simplify debugging** – test and fix a function independently.
- **Reuse code** – across different scripts (by sourcing).

---

## Defining Functions

Bash supports two syntaxes for defining functions:

### Syntax 1: POSIX‑compatible (preferred)
```bash
name() {
    commands
}
```

### Syntax 2: with `function` keyword (Bash extension)

```bash
function name {
    commands
}
```

```bash
function name() {   # works but mixes styles – avoid
    commands
}
```

> [!tip] **Recommendation**  
> Use the POSIX style `name() { ... }` – it’s portable and clean. The `function` keyword adds no real benefit.

**Example:**
```bash
greet() {
    echo "Hello, world!"
}
```

---
## Calling Functions

Call a function by using its name as a command. No parentheses needed.
```bash
greet
```

**Example with multiple calls:**
```bash
#!/bin/bash
show_date() {
    echo "Today is $(date +%A)"
}

show_date
echo "Doing some work..."
show_date
```

---
## Function Arguments

Inside a function, `$1`, `$2`, … refer to the function’s arguments, **not** the script’s arguments. `$#`, `$@`, and `$*` also refer to the function’s arguments.
```bash
greet_person() {
    echo "Hello, $1! You are argument number 1."
    echo "All arguments: $@"
}

greet_person "Alice" "Bob" "Charlie"
```

**Output:**
```text
Hello, Alice! You are argument number 1.
All arguments: Alice Bob Charlie
```

**Accessing arguments beyond 9:** Use curly braces, e.g., `${10}`.
```bash
many_args() {
    echo "Tenth argument: ${10}"
}
many_args a b c d e f g h i j k
# Output: Tenth argument: j
```

**Using `$#` to check argument count:**
```bash
safe_greet() {
    if [ $# -eq 0 ]; then
        echo "Usage: safe_greet <name>"
        return 1
    fi
    echo "Hello, $1"
}
```

---
## Return Values

Functions can return data in two ways:

### 1. Numeric exit status (`return`)

`return N` exits the function with status `N` (0–255). The caller can check `$?`.

```bash
is_even() {
    local num=$1
    if [ $((num % 2)) -eq 0 ]; then
        return 0   # success (even)
    else
        return 1   # failure (odd)
    fi
}

if is_even 4; then
    echo "4 is even"
else
    echo "4 is odd"
fi
```

> [!warning] `return` can only return integers from 0 to 255. Larger values wrap modulo 256. For arbitrary data, use `echo`.

### 2. Output capture (`echo` + command substitution)

The function prints its result using `echo` (or `printf`), and the caller captures it with `$(...)`.

```bash
add() {
    echo $(( $1 + $2 ))
}

sum=$(add 5 3)
echo "Sum is $sum"   # Sum is 8
```

**Multiple return values:** Print each on a separate line and capture into an array.
```bash

get_user_info() {
    echo "Alice"
    echo "30"
    echo "Engineer"
}

readarray -t info < <(get_user_info)
name="${info[0]}"
age="${info[1]}"
job="${info[2]}"
```

---
## Variable Scope (local vs global)

By default, all variables in Bash are **global** – they exist everywhere in the script. Inside a function, any assignment modifies the global variable unless you declare it as `local`.

```bash
global_var="outside"

test_scope() {
    local local_var="inside"
    global_var="changed inside"
    echo "Inside: local_var=$local_var, global_var=$global_var"
}

test_scope
echo "Outside: global_var=$global_var"
# echo "local_var=$local_var"  # Error: local_var not accessible
```

**Output:**
```text
Inside: local_var=inside, global_var=changed inside
Outside: global_var=changed inside
```

> [!tip] **Always use `local`** inside functions for temporary variables. It prevents accidental side effects.
```bash
compute() {
    local result=$(( $1 * $2 ))
    echo $result
}
```

---
## Exit Status and `return`

If you do not explicitly `return`, the function’s exit status is the exit status of the last command executed in the function.

```bash
check_file() {
    ls "$1"   # if this fails, the function returns non‑zero
}

check_file /etc/passwd
echo $?   # 0 (success)

check_file /nonexistent
echo $?   # 2 (ls error code)
```

**Explicit return for clarity:**
```bash
check_file() {
    if [ -f "$1" ]; then
        echo "File exists"
        return 0
    else
        echo "File missing"
        return 1
    fi
}
```

---
## Recursion

Bash functions can call themselves (recursion). However, Bash has no built‑in recursion limit; deep recursion may cause stack overflow or performance issues.

**Factorial example:**
```bash
factorial() {
    local n=$1
    if [ $n -le 1 ]; then
        echo 1
    else
        local prev=$(factorial $((n-1)))
        echo $((n * prev))
    fi
}

result=$(factorial 5)
echo "5! = $result"   # 120
```

> [!warning] Recursion in Bash is slow and limited. For deep recursion (hundreds of levels), use an iterative approach or another language.

---

## Functions in Scripts vs Interactive Shell

- **In a script:** Functions must be defined before they are called. The script reads top‑to‑bottom.
    
- **In the interactive shell:** You can define functions on the command line. They persist until the shell exits (or you `unset -f`).
    

**Example in terminal:**
```bash
$ greet() { echo "Hello $1"; }
$ greet "World"
Hello World
```

**To remove a function:**
```bash
unset -f greet
```

---
## Exporting Functions

Exported functions are inherited by child processes (subshells, scripts called from your script). This is rarely needed but can be useful.

```bash
myfunc() { echo "Hello"; }
export -f myfunc
bash -c 'myfunc'   # outputs "Hello"
```

---
## Best Practices

1. **Use descriptive names** – `calculate_average`, `check_disk_space`, not `f1`, `do_it`.
    
2. **Declare local variables with `local`** – prevents side effects.
    
3. **Keep functions short** – one screen (20‑30 lines) maximum. If longer, break into smaller functions.
    
4. **Use `return` for success/failure status** (0/1), and `echo` for data output.
    
5. **Document functions** – add a comment describing purpose, arguments, and return values.
    
6. **Validate arguments** – check `$#` and argument values at the beginning of the function.
    
7. **Avoid `cd` in functions** – it changes the caller’s current directory. Use `pushd`/`popd` or subshells.


**Well‑documented function:**
```bash
# Usage: backup_file <source> <dest_dir>
# Backups a file with timestamp. Returns 0 on success, non‑zero on failure.
backup_file() {
    local src="$1"
    local dest_dir="$2"
    local timestamp=$(date +%Y%m%d_%H%M%S)
    local base=$(basename "$src")
    local dest="$dest_dir/${base}.$timestamp"

    if [ ! -f "$src" ]; then
        echo "Error: source file '$src' not found" >&2
        return 1
    fi
    cp "$src" "$dest"
    echo "Backup created: $dest"
}
```

---
## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|Forgetting `local`|Function modifies global variable accidentally|`local var=value`|
|Using `$1` inside function but expecting script argument|`$1` inside function is function’s argument|Pass script arguments as parameters: `myfunc "$1"`|
|Using parentheses to call: `greet()`|Bash interprets `greet()` as a function definition|`greet` alone|
|Returning a string with `return`|`return` expects integer 0‑255|Use `echo` and capture|
|Defining function after calling it|Bash parses top‑to‑bottom; undefined function causes error|Define before use|
|Not quoting arguments inside function|Word splitting or globbing|`"$1"`, `"$@"`|

---

## Next Steps

You can practice by writing:

- A function `is_prime` that checks if a number is prime.
    
- A function `log_message` that writes timestamped messages to a log file.
    
- A script that uses functions to manage a simple todo list.


> [!tip] **Link this note**  
> Add `- [ ] [[Functions]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for Bash functions. Use them to write clean, reusable, and maintainable scripts.
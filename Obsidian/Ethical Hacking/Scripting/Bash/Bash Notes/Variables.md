# Variables

> [!info] **Purpose**  
> This note explains how to store, reference, and manipulate data using Bash variables. It includes regular variables, special shell parameters, and parameter expansion (default values, substring, etc.).

---

## Table of Contents

- [[#What is a Variable?]]
- [[#Variable Naming Rules]]
- [[#Assignment and Referencing]]
- [[#Quoting Variables]]
- [[#Special Shell Variables]]
- [[#Parameter Expansion Modifiers]]
- [[#Read‑Only and Unset]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What is a Variable?

A **variable** is a named storage location that holds a value (string or number). In Bash, variables are **untyped** – they store everything as strings, but arithmetic operations can treat them as numbers.

**Analogy:** Variables are like labeled boxes. You put a value in the box, then you can look at it or change it later.

---

## Variable Naming Rules

- Can contain letters (`a-z`, `A-Z`), numbers (`0-9`), and underscores (`_`).
- Must start with a letter or underscore (not a number).
- Case‑sensitive: `name`, `Name`, and `NAME` are different.
- Convention: use lowercase for local variables, uppercase for environment variables (e.g., `PATH`, `HOME`).

**Valid:**
```bash
name="Alice"
_count=5
var123="ok"
MY_CONFIG="/etc/config"
```

**Invalid:**
```bash
123var="wrong"      # starts with number
my-var="wrong"      # hyphen not allowed
my var="wrong"      # space not allowed
```

---
## Assignment and Referencing

### Assignment

Syntax: `variable_name=value` – **no spaces** around `=`.

```bash
name="John Doe"
age=30
pi=3.14159
empty=
```

> [!warning] Spaces break assignment  
> `name = "John"` tries to run a command named `name` with arguments `=` and `"John"`. Always write `name="John"`.

### Referencing

Use `$` before the variable name. Braces `{}` are optional but help avoid ambiguity.
```bash
echo $name        # John Doe
echo "$name"      # John Doe (quoted)
echo ${name}      # John Doe
echo "${name}"    # John Doe
```

**Why braces?** They separate the variable name from surrounding text:
```bash
prefix="file"
echo "$prefix_001"   # Looks for variable `prefix_001`, which doesn't exist
echo "${prefix}_001" # file_001
```

### Assigning command output

Use command substitution:
```bash
current_date=$(date)
files=$(ls | wc -l)
```

### Assigning arithmetic result

Use `$(( ))`:
```bash
sum=$((5 + 3))
((age++))   # increments age by 1 (no $ needed inside (( )))
```

---
## Quoting Variables

Quoting affects how the variable's value is interpreted.

|Quote type|Behavior|Example|
|---|---|---|
|**None**|Word splitting and pathname expansion (globbing) occur.|`$var` – if value has spaces, it splits into multiple arguments.|
|**Double quotes `" "`**|Prevents word splitting and globbing, but allows variable expansion (`$var`) and command substitution (`$(cmd)`).|`"$var"` – safest default.|
|**Single quotes `' '`**|Everything literal – no expansion.|`'$var'` prints literal `$var`.|

**Demonstration:**
```bash
files="one two three"
for f in $files; do      # splits into three words
    echo "$f"
done

for f in "$files"; do    # one iteration, value "one two three"
    echo "$f"
done
```

> [!tip] **Golden rule**  
> Always double‑quote variables unless you explicitly need word splitting or globbing. Use `"$var"` almost everywhere.

---

## Special Shell Variables

Bash provides read‑only special variables.

|Variable|Description|Example|
|---|---|---|
|`$0`|Script name|`./myscript.sh`|
|`$1` … `$9`|Positional parameters (script arguments). Use `${10}` for beyond 9.|`./script arg1 arg2` → `$1=arg1`|
|`$#`|Number of positional parameters|`2` for `./script a b`|
|`$@`|All parameters as separate quoted words. Use `"$@"` to preserve each argument.|`"$1" "$2" ...`|
|`$*`|All parameters as a single string (first character of IFS as separator).|`"$1 $2 ..."`|
|`$?`|Exit status of last command (0 = success)|`ls /tmp; echo $?`|
|`$$`|Process ID (PID) of the current shell|`echo $$`|
|`$!`|PID of the most recent background command|`sleep 10 & echo $!`|
|`$-`|Current shell options (e.g., `hB` for `-h -B`)|`echo $-`|
|`$_`|Last argument of previous command|`ls /etc; echo $_`|

**Example using arguments:**
```bash
#!/bin/bash
echo "Script: $0"
echo "First argument: $1"
echo "Second argument: $2"
echo "Total arguments: $#"
echo "All arguments: $@"
```

Run: `./args.sh hello world 42`  
Output:

```text
Script: ./args.sh
First argument: hello
Second argument: world
Total arguments: 3
All arguments: hello world 42
```

> [!tip] **`"$@"` is magical**  
> Always use `"$@"` (quoted) to pass all arguments to another command. It preserves spaces and empty arguments correctly.

---

## Parameter Expansion Modifiers

These modify the value of a variable without changing the original (unless you reassign).

### Default values

|Expression|Effect|
|---|---|
|`${var:-word}`|If `var` is unset or empty, use `word`; otherwise use `var`. Does not change `var`.|
|`${var:=word}`|If `var` is unset or empty, assign `word` to `var`, then use that value.|
|`${var:?word}`|If `var` is unset or empty, print `word` to stderr and exit (or abort if not in script).|
|`${var:+word}`|If `var` is set and non‑empty, use `word`; otherwise use nothing.|

**Examples:**
```bash
unset name
echo "${name:-Anonymous}"   # prints "Anonymous" (name still unset)
echo "${name:=Anonymous}"   # assigns "Anonymous" to name, then prints it
echo "$name"                # now prints "Anonymous"

# With empty variable
var=""
echo "${var:-default}"      # default (empty triggers default)
echo "${var-default}"       # empty string (no colon, only unset triggers default)

# Error message
: "${config_file:?Config file not set}"
```

### Length and substring

|Expression|Effect|
|---|---|
|`${#var}`|Length of the string in `var`.|
|`${var:offset}`|Substring from `offset` (0‑based) to end.|
|`${var:offset:length}`|Substring of `length` characters from `offset`.|
|Negative offset: `${var: -5}` (space before `-`)|Last 5 characters.|

**Examples:**
```bash
str="Hello World"
echo "${#str}"          # 11
echo "${str:6}"         # "World"
echo "${str:0:5}"       # "Hello"
echo "${str: -5}"       # "World" (note space)
```

### Remove matching patterns

|Expression|Effect|
|---|---|
|`${var#pattern}`|Remove shortest leading pattern.|
|`${var##pattern}`|Remove longest leading pattern.|
|`${var%pattern}`|Remove shortest trailing pattern.|
|`${var%%pattern}`|Remove longest trailing pattern.|

**Examples:**
```bash
path="/home/user/file.txt"
echo "${path#*/}"    # "home/user/file.txt" (shortest)
echo "${path##*/}"   # "file.txt" (longest – strips everything up to last slash)
echo "${path%/*}"    # "/home/user" (shortest trailing)
echo "${path%%/*}"   # "" (longest trailing – strips from first slash)

file="archive.tar.gz"
echo "${file%.*}"    # "archive.tar" (shortest suffix)
echo "${file%%.*}"   # "archive" (longest suffix)
```

### Search and replace

|Expression|Effect|
|---|---|
|`${var/pattern/replacement}`|Replace first occurrence.|
|`${var//pattern/replacement}`|Replace all occurrences.|
|`${var/#pattern/replacement}`|Replace only if pattern matches beginning.|
|`${var/%pattern/replacement}`|Replace only if pattern matches end.|

**Examples:**
```bash
text="Hello world, hello universe"
echo "${text/hello/Hi}"     # "Hi world, hello universe"
echo "${text//hello/Hi}"    # "Hi world, Hi universe"
echo "${text/#Hello/Hi}"    # "Hi world, hello universe"
echo "${text/%universe/everything}"  # "Hello world, hello everything"
```

### Case conversion

|Expression|Effect|
|---|---|
|`${var^}`|First character uppercase.|
|`${var^^}`|All characters uppercase.|
|`${var,}`|First character lowercase.|
|`${var,,}`|All characters lowercase.|

**Examples:**

```bash
str="hello WORLD"
echo "${str^}"    # "Hello WORLD"
echo "${str^^}"   # "HELLO WORLD"
echo "${str,}"    # "hello WORLD" (first char already lower)
echo "${str,,}"   # "hello world"
```

## Read‑Only and Unset

**Read‑only variables** – cannot be changed later:
```bash
readonly CONFIG_PATH="/etc/myapp"
CONFIG_PATH="/new"   # Error: readonly variable
```

**Unset** – delete a variable:
```bash
unset temp_var
echo "$temp_var"     # prints nothing (empty)
```

## Best Practices

1. **Always double‑quote variable expansions** – `"$var"` not `$var`, unless you need word splitting.
    
2. **Use lowercase names** for local script variables; uppercase for environment variables.
    
3. **Use braces** when concatenating with other characters: `"${prefix}_suffix"`.
    
4. **Initialize variables** before use to avoid unintended behavior with `set -u`.
    
5. **Use `readonly`** for constants.
    
6. **Prefer `"$@"` over `$*`** for passing arguments.
    
7. **Use `:-` for default values** to avoid unset variable errors.    

---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`name = "John"`|Spaces around `=` → tries to run command `name`|`name="John"`|
|`echo $name` without quotes|Word splitting if value has spaces|`echo "$name"`|
|`$name_001`|Underscore is part of variable name|`"${name}_001"`|
|Forgetting `$` in arithmetic|`((sum = a + b))` is fine, but `echo a+b` prints `a+b`|`echo $((a+b))`|
|Using `$@` without quotes|Loses argument boundaries|`"$@"`|

---

## Next Steps

You can also practice by writing a script that:

- Asks for your name and age (using `read`).
    
- Stores them in variables.
    
- Prints a greeting that includes your name and age after 10 years.


> [!tip] **Link this note**  
> Add `- [ ] [[Variables]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for Bash variables. Return here when you need to recall syntax for parameter expansion or special variables.
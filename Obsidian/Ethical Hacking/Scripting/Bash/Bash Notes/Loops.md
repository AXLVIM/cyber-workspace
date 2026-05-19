# Loops

> [!info] **Purpose**  
> This note explains how to repeat commands multiple times using loops. Loops are essential for automating repetitive tasks such as processing many files, reading lines from a file, or retrying operations until success.

---

## Table of Contents

- [[#What are Loops?]]
- [[#The `for` Loop]]
  - [[#Iterating over a list]]
  - [[#Brace expansion `{start..end}`]]
  - [[#C‑style `for` loop]]
  - [[#Iterating over files (globbing)]]
- [[#The `while` Loop]]
- [[#The `until` Loop]]
- [[#Loop Control: `break` and `continue`]]
- [[#Infinite Loops]]
- [[#Reading Lines from a File]]
- [[#Iterating Over Command Output]]
- [[#Nested Loops]]
- [[#Performance Considerations]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What are Loops?

Loops allow you to execute a block of commands repeatedly. Bash supports three types of loops:

| Loop | Behavior |
|------|----------|
| `for` | Iterates over a list of items (words, numbers, files, etc.) |
| `while` | Repeats as long as a condition is true |
| `until` | Repeats as long as a condition is false (opposite of `while`) |

All loops can be nested and controlled with `break` and `continue`.

---

## The `for` Loop

### Iterating over a list

The simplest form loops over a space‑separated list of words.

```bash
for color in red green blue; do
    echo "Color: $color"
done
```

**Output:**
```bash
Color: red
Color: green
Color: blue
```

### Brace expansion `{start..end}`

Brace expansion generates sequences. It is evaluated before the loop runs.
```bash
for i in {1..5}; do
    echo "Number: $i"
done
```

With step: `{start..end..step}`
```bash
for i in {0..10..2}; do
    echo "Even: $i"
done
```

> [!note] Brace expansion works only with literal numbers or letters. For variables, use C‑style `for` or `seq`.

### C‑style `for` loop

Similar to C, Java, or JavaScript `for` loops.
```bash
for ((i=1; i<=5; i++)); do
    echo "Count: $i"
done
```

You can use multiple variables:
```bash
for ((i=0, j=10; i<=10; i++, j--)); do
    echo "$i + $j = $((i + j))"
done
```

> [!tip] Use C‑style `for` when you need arithmetic progression with variables or complex increment logic.

### Iterating over files (globbing)

```bash
for file in *.txt; do
    echo "Processing $file"
    wc -l "$file"
done
```

To handle files with spaces, always quote `"$file"` inside the loop.

**Process all directories in current folder:**
```bash
for dir in */; do
    echo "Directory: $dir"
    ls -la "$dir"
done
```

---
## The `while` Loop

The `while` loop repeats as long as the condition is true (exit status 0).

**Syntax:**
```bash
while condition; do
    commands
done
```

**Simple counter:**
```bash
counter=1
while [ $counter -le 5 ]; do
    echo "Counter: $counter"
    ((counter++))
done
```

**Reading a file line by line:**
```bash
while IFS= read -r line; do
    echo "Line: $line"
done < input.txt
```

**Waiting for a file to appear:**
```bash
while [ ! -f "/tmp/ready.txt" ]; do
    echo "Waiting for ready.txt..."
    sleep 2
done
echo "File found!"
```

---
## The `until` Loop

The `until` loop is the opposite of `while`: it repeats as long as the condition is false (non‑zero exit status). It stops when the condition becomes true.

**Syntax:**
```bash
until condition; do
    commands
done
```

**Countdown:**
```bash
counter=5
until [ $counter -lt 1 ]; do
    echo "Countdown: $counter"
    ((counter--))
    sleep 1
done
echo "Blast off!"
```

**Until a command succeeds:**
```bash
until ping -c 1 google.com &>/dev/null; do
    echo "No internet. Retrying in 5 seconds..."
    sleep 5
done
echo "Internet is up!"
```

> [!tip] Choose `while` for "as long as condition is true", `until` for "until condition becomes true".

---

## Loop Control: `break` and `continue`

- `break` – exit the loop immediately.
    
- `continue` – skip the rest of the current iteration and go to the next one.
    

Both accept an optional numeric argument to break/continue from multiple nested loops: `break 2` exits two levels.

**Examples:**
```bash
# break when i equals 5
for i in {1..10}; do
    if [ $i -eq 5 ]; then
        break
    fi
    echo $i
done
# Output: 1 2 3 4
```

```bash
# continue (skip 5)
for i in {1..10}; do
    if [ $i -eq 5 ]; then
        continue
    fi
    echo $i
done
# Output: 1 2 3 4 6 7 8 9 10
```

**Breaking out of nested loops:**
```bash
for i in {1..3}; do
    for j in {a..c}; do
        if [ $i -eq 2 ] && [ $j == "b" ]; then
            break 2   # exits both loops
        fi
        echo "$i$j"
    done
done
# Output: 1a 1b 1c 2a  (then stops)
```

---
## Infinite Loops

Sometimes you need a loop that runs forever (until interrupted or a condition is met inside).

**Common patterns:**
```bash
while true; do
    echo "Running... (Ctrl+C to stop)"
    sleep 1
done
```

```bash
until false; do
    # same as while true
    date
    sleep 5
done
```

```bash
for ((;;)); do
    echo "Also infinite"
    sleep 1
done
```

**Useful infinite loop with exit condition inside:**
```bash
while true; do
    read -p "Enter number (0 to quit): " num
    if [ $num -eq 0 ]; then
        break
    fi
    echo "You entered $num"
done
```

---
## Reading Lines from a File

The standard pattern for reading a file line‑by‑line is:
```bash
while IFS= read -r line; do
    echo "Line: $line"
done < filename.txt
```

**Explanation:**

- `IFS=` – prevents stripping leading/trailing whitespace.
    
- `read -r` – prevents backslash interpretation.
    
- `< filename.txt` – redirects file content into the loop.


**Reading `/etc/passwd` and extracting usernames:**
```bash
while IFS=: read -r username _ uid gid comment home shell; do
    echo "User: $username, UID: $uid, Home: $home"
done < /etc/passwd
```

---
## Iterating Over Command Output

You can loop over the output of a command, but be careful with spaces and special characters.

**Simple but fragile (breaks on spaces):**
```bash
for file in $(ls); do
    echo "$file"
done
```

**Better: use a `while read` loop with process substitution:**
```bash
while IFS= read -r file; do
    echo "$file"
done < <(ls)
```

**Safe way to iterate over files: use globbing (not `ls`):**
```bash
for file in *; do
    echo "$file"
done
```

**Iterating over lines of a command output:**
```bash
while IFS= read -r line; do
    echo "Line: $line"
done < <(grep "error" logfile.txt)
```

---
## Nested Loops

Loops can be placed inside other loops.
```bash
for i in {1..3}; do
    for j in {a..c}; do
        echo "$i$j"
    done
done
```

**Multiplication table:**
```bash
for i in {1..5}; do
    for j in {1..5}; do
        printf "%3d " $((i * j))
    done
    echo
done
```

---
## Performance Considerations

- **Use globbing** instead of `$(ls)` – it's faster and safer.
    
- **Avoid expensive commands inside loops** – compute once before the loop if possible.
    
- **For large files, `while read` is efficient** – it reads one line at a time without loading the whole file.
    
- **Use `printf` instead of `echo`** for formatting many lines (slightly faster).


**Pre‑computing outside loop:**
```bash
# Inefficient
for file in *.txt; do
    count=$(wc -l < "$file")   # runs wc for each file
    echo "$file: $count"
done

# Better: wc can handle multiple files
wc -l *.txt | while read -r count file; do
    echo "$file: $count"
done
```

---
## Best Practices

1. **Quote variables inside loops** – `"$file"`, `"$line"`.
    
2. **Use `while IFS= read -r`** for reading files line by line.
    
3. **Prefer globbing over `ls`** for file iteration.
    
4. **Use `break` and `continue` sparingly** – they can make logic harder to follow.
    
5. **Add a `sleep` in infinite loops** to avoid CPU exhaustion.
    
6. **Use `(( ))` for arithmetic conditions** inside C‑style loops.


---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`for i in $(cat file)`|Splits on spaces, globs|`while read` loop|
|Not quoting `$file` in loop|Filenames with spaces break|`"$file"`|
|`for i in {1..$n}`|Brace expansion happens before variable expansion|Use C‑style `for ((i=1; i<=n; i++))` or `seq`|
|`while read line` (no `-r`)|Backslashes are interpreted|`read -r line`|
|Missing `IFS=`|Leading/trailing whitespace stripped|`IFS= read -r line`|
|Infinite loop without `sleep`|Consumes 100% CPU|Add `sleep 1`|

---

## Next Steps

You can practice by writing scripts that:

- Rename all `.jpg` files to `photo_001.jpg`, `photo_002.jpg`, etc.
    
- Read a CSV file and calculate the sum of a column.
    
- Wait until a specific process is no longer running.


> [!tip] **Link this note**  
> Add `- [ ] [[Loops]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for loops in Bash. Use them to automate repetitive tasks efficiently.
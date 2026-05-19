# Command Substitution

> [!info] **Purpose**  
> This note explains command substitution – a powerful feature that allows you to capture the output of a command and use it as a value (e.g., assign to a variable, use as argument, or embed in a string).

---

## Table of Contents

- [[#What is Command Substitution?]]
- [[#Syntax: `$(command)` vs. Backticks]]
- [[#Basic Examples]]
- [[#Nested Command Substitution]]
- [[#Using with Other Commands]]
- [[#Common Use Cases]]
- [[#Performance Considerations]]
- [[#Security Notes]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What is Command Substitution?

**Command substitution** allows you to run a command and replace the command itself with its standard output (stdout). The output is captured as a string and can be:

- Assigned to a variable
- Used as an argument to another command
- Embedded in a string (with double quotes)

**Without command substitution** – you get the literal text `$(date)`:
```bash
echo "Today is $(date)"   # Wrong if you forget $?
```

**With command substitution** – `date` runs, and its output replaces `$(date)`:
```bash
echo "Today is $(date)"   # Today is Mon Apr 13 10:30:00 UTC 2026
```

---
## Syntax: `$(command)` vs. Backticks

There are two syntaxes:

|Syntax|Style|Recommendation|
|---|---|---|
|`$(command)`|Modern (POSIX)|**Preferred** – easier to read, nests cleanly|
|`` `command` ``|Legacy (backticks)|**Avoid** – nesting is messy, escaping is confusing|

**Comparison:**
```bash
# Modern (good)
files=$(ls)
today=$(date +%F)

# Legacy (bad – avoid)
files=`ls`
today=`date +%F`
```

> [!warning] Backticks are deprecated. Use `$( )` for all new scripts.

---

## Basic Examples

### Assign to a variable

```bash
current_date=$(date)
echo "Today is $current_date"

hostname=$(hostname)
echo "This machine is called $hostname"
```
### Use directly in a command argument

```bash
echo "The current directory has $(ls | wc -l) files"
mkdir "backup_$(date +%Y%m%d)"
```

### Embed in a string (double quotes required)

```bash
message="System uptime: $(uptime -p)"
echo "$message"
```

### Capture multi‑line output

```bash
files_list=$(ls -l)
echo "$files_list"   # Preserves newlines (if quoted)
```

---
## Nested Command Substitution

`$( )` can be nested arbitrarily. The inner `$( )` is executed first.

**Example: Get the size of the largest file in a directory**
```bash
largest_file=$(ls -S | head -1)
size=$(stat -c %s "$(find . -name "$largest_file" -type f)")
```

**More readable with line breaks:**
```bash
largest=$(ls -S | head -1)
size=$(stat -c %s "$(find . -name "$largest" -type f)")
```

**Nesting with backticks (horrible, avoid):**
```bash
# Avoid this!
size=`stat -c %s \`find . -name "$largest" -type f\``
```

> [!tip] Nesting with `$( )` is clean and reliable.

---

## Using with Other Commands

Command substitution is often combined with pipes, conditionals, and loops.

### In `if` conditions

```bash
if [ "$(whoami)" = "root" ]; then
    echo "You are root"
fi

if grep -q "error" "$(find . -name "*.log" | head -1)"; then
    echo "Error found"
fi
```

### In `for` loops

```bash
for file in $(ls *.txt); do
    echo "Processing $file"
done
```

> [!warning] Looping over `$(ls)` breaks with filenames containing spaces. Use `for file in *.txt` or `find` instead.

### In arithmetic

```bash
count=$(ls | wc -l)
echo "There are $((count * 2)) items if doubled"
```

### In `case` statements

```bash
case "$(uname)" in
    Linux) echo "Linux system" ;;
    Darwin) echo "macOS system" ;;
    *) echo "Other OS" ;;
esac
```

## Common Use Cases

|Task|Example|
|---|---|
|**Timestamped filenames**|`backup_$(date +%Y%m%d).tar.gz`|
|**Counting files**|`count=$(find . -type f \| wc -l)`|
|**Getting command output**|`ip=$(hostname -I \| awk '{print $1}')`|
|**Dynamic variable names (eval)**|`value=$(eval echo \$$var_name)` – use with caution|
|**Creating temporary files**|`tmpfile="/tmp/mytemp.$$.$(date +%s)"`|
|**Checking command success**|`if [ "$(curl -s -o /dev/null -w '%{http_code}' https://example.com)" -eq 200 ]; then`|

---

## Performance Considerations

- Each `$( )` forks a subshell to execute the command. For many iterations, this can be slow.
    
- **Efficient alternative for reading lines:** Use a `while read` loop instead of `for` over `$(cat file)`.
    
- **For large output:** Assign to a variable and reuse, rather than invoking the same command multiple times.
    

**Inefficient (calls `date` three times):**
```bash
echo "Today is $(date)"
echo "Tomorrow is $(date -d tomorrow)"
echo "Yesterday was $(date -d yesterday)"
```

**Better (call once, reuse):**
```bash
today=$(date)
echo "Today is $today"
echo "Tomorrow is $(date -d tomorrow)"
```

**Even better for repeated fields:** reuse the variable where possible.

---
## Security Notes

- Command substitution **does not** automatically quote the output. If the output contains spaces or special characters, you must double‑quote the substitution.
    
- **Never** use command substitution without quotes in contexts where word splitting could cause harm (e.g., `rm $(find ...)` – dangerous if filenames have spaces).
    
- **Avoid** injecting unsanitized user input into `$( )` – it can lead to arbitrary command execution.
    

**Safe:**
```bash
file="my file.txt"
rm "$(echo "$file")"   # Quotes around substitution
```

**Dangerous:**
```bash
rm $(echo "$file")     # Tries to remove "my" and "file.txt" separately
```

> [!warning] Always quote command substitution when it might produce spaces or special characters: `"$(command)"`.

---

## Best Practices

1. **Use `$(command)`** – never backticks.
    
2. **Quote the substitution** – `"$(command)"` unless you specifically need word splitting.
    
3. **Avoid unnecessary nesting** – assign intermediate results to variables for readability.
    
4. **Do not parse `ls`** – use globbing or `find` instead.
    
5. **Prefer built‑ins** – for simple tasks like `$(pwd)`, use `$PWD` (variable) which is faster.
    
6. **Use `$()` inside double quotes** – `"Hello $(whoami)"` works fine.

---

## Common Mistakes

| Mistake                                                     | Why it fails                    | Correct                                                     |
| ----------------------------------------------------------- | ------------------------------- | ----------------------------------------------------------- |
| `files = $(ls)`                                             | Spaces around `=`               | `files=$(ls)`                                               |
| `echo "Date: $(date)"` missing `$` in `$()`? Actually fine. | –                               | –                                                           |
| Not quoting: `rm $(find . -name "*.tmp")`                   | Breaks on filenames with spaces | `rm "$(find . -name "*.tmp")"` (but better: `find -delete`) |
| Using backticks inside backticks                            | Escaping nightmare              | Use `$( )`                                                  |
| Capturing binary output                                     | May corrupt terminal            | Avoid; use files or `base64`                                |
| Using `$()` inside single quotes                            | No expansion                    | Use double quotes                                           |

---

## Next Steps

You can also practice by writing a script that:

- Stores the output of `uptime` in a variable.
    
- Prints the load average values separately (using `cut` or `awk` inside `$()`).
    
- Creates a directory named `backup_YYYY-MM-DD` using `$(date +%F)`.


> [!tip] **Link this note**  
> Add `- [ ] [[Command Substitution]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for command substitution. Use it whenever you need to capture or use command output dynamically.
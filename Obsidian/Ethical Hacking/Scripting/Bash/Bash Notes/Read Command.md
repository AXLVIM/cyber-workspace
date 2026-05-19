# Read Command

> [!info] **Purpose**  
> This note explains how to accept user input from the keyboard (or other input sources) using the `read` builtin command. It covers options, IFS field splitting, and safe input handling.

---

## Table of Contents

- [[#What is `read`?]]
- [[#Basic Syntax]]
- [[#Common Options]]
- [[#Reading into Multiple Variables]]
- [[#IFS and Field Splitting]]
- [[#Reading from Files and Here‑Strings]]
- [[#Reading Passwords Securely]]
- [[#Timeouts and Character Limits]]
- [[#Exit Status]]
- [[#Common Use Cases]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What is `read`?

`read` is a Bash builtin that reads one line from standard input (or a file descriptor) and splits it into words, assigning each word to a variable. By default, it reads from the keyboard, but you can also redirect input from files or pipes.

**Simplest example:**
```bash
read name
echo "Hello, $name"
```

The script pauses, waits for the user to type something and press Enter, then stores the typed text in the variable `name`.

---
## Basic Syntax

```bash
read [options] variable1 [variable2 ...]
```

- If only one variable is given, the entire line is stored in that variable.
    
- If multiple variables are given, the line is split into words (using IFS), and words are assigned to variables in order. Any remaining words go to the last variable.

**Example with one variable:**
```bash
read color
echo "Your favorite color is $color"
```

**Example with multiple variables:**
```bash
read first last age
echo "First: $first, Last: $last, Age: $age"
```

User input: `John Doe 30` → `first=John`, `last=Doe`, `age=30`

If user types more than expected: `John Doe 30 Engineer` → `first=John`, `last=Doe`, `age=30 Engineer` (the rest go to the last variable).

---

## Common Options

|Option|Description|Example|
|---|---|---|
|`-p prompt`|Display `prompt` before reading (no newline).|`read -p "Enter name: " name`|
|`-s`|Silent mode – do not echo input (for passwords).|`read -sp "Password: " pass`|
|`-t seconds`|Timeout after `seconds`. Returns failure if input not received.|`read -t 5 -p "Quick: " var`|
|`-n nchars`|Return after reading exactly `nchars` characters (does not wait for Enter).|`read -n 1 -p "Press any key" key`|
|`-N nchars`|Return after reading exactly `nchars` characters, even if delimiter is reached earlier.|`read -N 5 data`|
|`-r`|Raw mode – do not interpret backslashes as escape characters.|`read -r line`|
|`-a array`|Split the input into words and assign to array `array`.|`read -a words`|
|`-d delim`|Use `delim` as the line delimiter instead of newline.|`read -d ':' field`|
|`-e`|Use Readline to obtain the line (provides line editing).|`read -e -p "Search: " term`|

> [!tip] **Always use `-r`** when reading lines from files or when you want literal backslashes. Without `-r`, backslashes act as escape characters.

---

## Reading into Multiple Variables

`read` automatically splits the input line using the characters in the `IFS` (Internal Field Separator) variable (default: space, tab, newline).

```bash
read first second third <<< "apple banana cherry"
echo "$first"   # apple
echo "$second"  # banana
echo "$third"   # cherry
```

If there are more words than variables, the last variable gets the remainder:
```bash
read a b <<< "one two three four"
echo "$a"   # one
echo "$b"   # two three four
```

If there are fewer words, the remaining variables become empty:
```bash
read a b c <<< "only one"
echo "$a"   # only one
echo "$b"   # (empty)
echo "$c"   # (empty)
```

---
## IFS and Field Splitting

`IFS` (Internal Field Separator) controls how `read` splits the input. The default value is space, tab, newline (three characters). You can change IFS to parse custom formats.

**Parsing CSV with comma separator:**
```bash
old_IFS="$IFS"
IFS=,
read field1 field2 field3 <<< "value1,value2,value3"
IFS="$old_IFS"
```

**Preserving leading/trailing whitespace:** Set IFS to empty string:
```bash
IFS= read -r line   # Does not trim whitespace
```

>[!note] **Common pattern**  
To read a file line‑by‑line exactly as written (preserving spaces and backslashes):
```bash
while IFS= read -r line; do
    echo "$line"
done < file.txt
```

---
## Reading from Files and Here‑Strings

`read` can read from any file or string, not just the keyboard.

### From a file (using redirection)

```bash
while IFS= read -r line; do
    echo "Line: $line"
done < /etc/passwd
```

### From a here‑string (`<<<`)

```bash
read a b c <<< "hello world from here"
```

### From a pipe

```bash
echo "John Doe" | read first last
```

But note: pipelines create subshells; variables set in a pipeline are lost after the pipeline ends. Use a here‑string or `<<<` instead.

---
## Reading Passwords Securely

The `-s` option prevents echoing. Always follow with a newline manually.
```bash
read -sp "Enter your password: " password
echo   # Add newline because -s suppresses it
echo "Password entered (but we won't show it)."
```

> [!warning] **Security note**  
> The password is still stored in the variable (in memory) and can be seen in process lists if the script is inspected. For extremely sensitive data, consider more secure methods.

---

## Timeouts and Character Limits

### Timeout (`-t` seconds)

If the user does not respond within the specified time, `read` returns a non‑zero exit status.
```bash
read -t 5 -p "You have 5 seconds: " answer
if [ $? -ne 0 ]; then
    echo "Timed out!"
else
    echo "You answered: $answer"
fi
```

### Character limit (`-n nchars`)

Returns immediately after reading `nchars` characters (without waiting for Enter). Useful for menu selections.
```bash
read -n 1 -p "Continue? (y/n) " answer
echo
if [[ "$answer" == [Yy] ]]; then
    echo "Continuing..."
else
    echo "Aborted."
fi
```

### Reading exactly N characters (`-N nchars`)

Similar to `-n`, but does not stop at delimiter (e.g., newline). It reads exactly `nchars` characters.

---

## Exit Status

`read` returns:

- `0` – success (input was read)
    
- Non‑zero – failure (EOF, timeout, or other error)

**Example:**
```bash
if read -t 5 -p "Enter something: " data; then
    echo "You entered: $data"
else
    echo "No input or timeout."
fi
```

---
## Common Use Cases

|Use Case|Example|
|---|---|
|**Yes/No confirmation**|`read -n 1 -p "Proceed? (y/n) " ans`|
|**Reading configuration files**|`while IFS== read key value; do ...`|
|**Parsing CSV**|`IFS=, read col1 col2 col3`|
|**Password input**|`read -sp "Password: " pass`|
|**Timeout for user response**|`read -t 10 -p "Auto‑continue in 10s..."`|
|**Menu selection**|`read -n 1 -p "Choose [1-3]: " choice`|
|**Reading entire lines (preserving spaces)**|`IFS= read -r line`|

---

## Best Practices

1. **Always use `-r`** to prevent backslash interpretation.
    
2. **Set `IFS=`** when reading lines to preserve leading/trailing whitespace.
    
3. **Quote variables** when echoing the input (to preserve spaces).
    
4. **Use meaningful variable names** (e.g., `user_name` not `a`).
    
5. **Provide clear prompts** using `-p`.
    
6. **Check exit status** when using timeouts or optional input.
    
7. **Avoid `read` in pipelines** (subshell issue). Use here‑strings or process substitution.


**Robust line‑reading pattern:**
```bash
while IFS= read -r line; do
    process "$line"
done < input.txt
```

---
## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|Forgetting `-r`|Backslashes in input are interpreted as escapes|`read -r line`|
|Not setting `IFS=`|Leading/trailing whitespace is stripped|`IFS= read -r line`|
|Using `read` in a pipeline|Variables lost because of subshell|`<<< "$var"` or process substitution|
|No prompt for `-s`|User does not know what to type|`read -sp "Password: " pass`|
|Expecting `read` to split on commas without changing IFS|Default IFS does not include comma|`IFS=, read a b c`|
|Not quoting the variable after read|Word splitting may occur|`echo "$name"`|

---

## Next Steps

You can practice by writing a script that:

- Asks for name and age.
    
- Validates that age is a number.
    
- Asks for confirmation before proceeding.


> [!tip] **Link this note**  
> Add `- [ ] [[Read Command]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for the `read` command. Use it whenever you need to accept interactive or non‑interactive input.
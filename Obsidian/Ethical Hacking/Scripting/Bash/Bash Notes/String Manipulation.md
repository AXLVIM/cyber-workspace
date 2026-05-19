# String Manipulation

> [!info] **Purpose**  
> This note explains how to manipulate strings in Bash using built‑in parameter expansions. These operations allow you to extract substrings, remove patterns, replace text, and change case without calling external programs.

---

## Table of Contents

- [[#String Basics]]
- [[#String Length]]
- [[#Substring Extraction]]
- [[#Removing Prefixes and Suffixes]]
- [[#Search and Replace]]
- [[#Case Conversion]]
- [[#Checking if String Contains a Substring]]
- [[#Default Values and Conditionals]]
- [[#Using External Tools (sed, awk, cut)]]
- [[#Performance Considerations]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## String Basics

In Bash, everything is a string by default. Quoting preserves literal characters.

**Assigning strings:**
```bash
str="Hello World"
empty=""
```

**No difference between single and double quotes except expansion:**

- Double quotes: expand variables (`$var`) and command substitution (`$(cmd)`).
    
- Single quotes: everything literal.
```bash
name="Alice"
echo "Hello $name"   # Hello Alice
echo 'Hello $name'   # Hello $name
```

---
## String Length

Use `${#var}` to get the length (number of characters) of a string.

```bash
str="Hello"
echo ${#str}        # 5

empty=""
echo ${#empty}      # 0
```

---
## Substring Extraction

Syntax: `${var:offset}` or `${var:offset:length}`

- `offset` is 0‑based (first character is 0).
    
- If `length` is omitted, extract to the end.
    
- Negative offset counts from the end of the string (requires a space before `-` or parentheses).


**Examples:**
```bash
str="Hello World"

echo "${str:0:5}"    # Hello (first 5 chars)
echo "${str:6}"      # World (from index 6 to end)
echo "${str:6:3}"    # Wor (3 chars from index 6)
echo "${str: -5}"    # World (last 5 chars; note the space before -)
echo "${str:(-5)}"   # World (alternative syntax without space)
```

> [!warning] Negative offset needs a space before `-` inside braces: `${str: -5}`. Without space, it means something else (default value). Use `${var: -n}` or `${var:(-n)}`.

---

## Removing Prefixes and Suffixes

These operations remove matching patterns from the beginning or end of the string. They are **non‑destructive** (the original variable is unchanged unless reassigned).

|Operator|Action|
|---|---|
|`${var#pattern}`|Remove shortest leading pattern|
|`${var##pattern}`|Remove longest leading pattern|
|`${var%pattern}`|Remove shortest trailing pattern|
|`${var%%pattern}`|Remove longest trailing pattern|

**Patterns** use the same globbing rules as filename expansion (`*` = any characters, `?` = one character, `[abc]` = character class).

**Examples:**
```bash
path="/home/user/Documents/report.txt"

# Remove everything up to first slash (shortest)
echo "${path#*/}"      # home/user/Documents/report.txt

# Remove everything up to last slash (longest)
echo "${path##*/}"     # report.txt (filename only)

# Remove from last slash to end (shortest trailing)
echo "${path%/*}"      # /home/user/Documents

# Remove from first slash to end (longest trailing)
echo "${path%%/*}"     # (empty, because first character is /)

# Practical: extract extension
file="archive.tar.gz"
echo "${file#*.}"      # tar.gz (shortest prefix up to first dot)
echo "${file##*.}"     # gz (extension after last dot)

# Extract basename without extension
echo "${file%.*}"      # archive.tar (remove shortest suffix .*)
echo "${file%%.*}"     # archive (remove longest suffix .*)
```

**Removing a known prefix:**
```bash
url="https://example.com/page"
echo "${url#https://}"   # example.com/page
```

---
## Search and Replace

Replace parts of a string using patterns.

|Operator|Action|
|---|---|
|`${var/pattern/replacement}`|Replace first occurrence|
|`${var//pattern/replacement}`|Replace all occurrences|
|`${var/#pattern/replacement}`|Replace only if pattern matches at beginning|
|`${var/%pattern/replacement}`|Replace only if pattern matches at end|

**Examples:**
```bash
text="The quick brown fox jumps over the lazy dog"

# Replace first 'the' with 'a'
echo "${text/the/a}"      # "a quick brown fox jumps over the lazy dog"

# Replace all 'the' with 'a'
echo "${text//the/a}"     # "a quick brown fox jumps over a lazy dog"

# Replace only at beginning
echo "${text/#The/A}"     # "A quick brown fox jumps over the lazy dog"

# Replace only at end
echo "${text/%dog/cat}"   # "The quick brown fox jumps over the lazy cat"

# Remove all spaces (replace with empty)
no_spaces="${text// /}"
echo "$no_spaces"
```

**Using variables as replacement:**
```bash
search="fox"
replace="wolf"
echo "${text//$search/$replace}"
```

---
## Case Conversion

Change uppercase/lowercase (Bash 4.0+).

|Operator|Action|
|---|---|
|`${var^}`|First character uppercase|
|`${var^^}`|All characters uppercase|
|`${var,}`|First character lowercase|
|`${var,,}`|All characters lowercase|

**Examples:**
```bash
str="hello WORLD"

echo "${str^}"    # Hello WORLD (first char uppercase)
echo "${str^^}"   # HELLO WORLD (all uppercase)
echo "${str,}"    # hello WORLD (first char lowercase – already lower)
echo "${str,,}"   # hello world (all lowercase)

# Capitalize first letter of each word (requires loop)
words="hello world"
capitalized=""
for w in $words; do
    capitalized+="${w^} "
done
echo "$capitalized"   # Hello World
```

For older Bash (pre‑4.0), use `tr` or `sed`:
```bash
echo "hello" | tr '[:lower:]' '[:upper:]'   # HELLO
```

---
## Checking if String Contains a Substring

Bash does not have a built‑in `contains` operator, but several workarounds exist.

**Using pattern matching in `[[ ]]`:**
```bash
if [[ "$string" == *"substring"* ]]; then
    echo "Found"
fi
```

**Using `case`:**
```bash
case "$string" in
    *substring*) echo "Found" ;;
esac
```

**Using `grep` (external):**
```bash
if echo "$string" | grep -q "substring"; then
    echo "Found"
fi
```

**Using `=` with pattern (inside `[[ ]]`):**
```bash
[[ "$string" = *"substring"* ]] && echo "Found"
```

---
## Default Values and Conditionals

These are often used with strings to provide defaults or test emptiness.

|Expression|Meaning|
|---|---|
|`${var:-default}`|Use `default` if `var` is unset or empty|
|`${var:=default}`|Assign `default` to `var` if unset/empty, then use it|
|`${var:?error}`|Print `error` and exit if `var` unset/empty|
|`${var:+value}`|Use `value` if `var` is set and non‑empty, else nothing|

**Examples:**
```bash
name=""
echo "${name:-Anonymous}"   # Anonymous (name unchanged)
echo "${name:=Anonymous}"   # Anonymous (now name=Anonymous)
echo "$name"                # Anonymous

config_file="${1:?Usage: $0 <config>}"
```

**Testing for non‑empty strings:**
```bash
if [[ -n "$var" ]]; then
    echo "var is not empty"
fi

if [[ -z "$var" ]]; then
    echo "var is empty"
fi
```

---
## Using External Tools (sed, awk, cut)

For complex manipulations not covered by built‑in expansions, use external tools.

|Tool|Typical use|
|---|---|
|`sed`|Search/replace with regular expressions, stream editing|
|`awk`|Field splitting, advanced formatting|
|`cut`|Extract fixed columns or fields by delimiter|
|`tr`|Character translation (e.g., case, delete chars)|
|`grep`|Extract lines matching pattern|

**Examples:**
```bash
# Replace all digits with X using sed
echo "abc123def" | sed 's/[0-9]/X/g'   # abcXXXdef

# Extract second field (comma‑separated) using cut
echo "a,b,c" | cut -d',' -f2            # b

# Convert to uppercase using tr
echo "hello" | tr 'a-z' 'A-Z'           # HELLO

# Extract IP address from ifconfig using awk
ifconfig eth0 | awk '/inet / {print $2}'
```

> [!note] External tools are slower than built‑in expansions. Use Bash expansions when possible; use external tools for complex regex or when portability to older Bash is needed.

---

## Performance Considerations

- **Built‑in parameter expansions** (`${#var}`, `${var#pattern}`, etc.) are very fast – they run inside the shell without forking.
    
- **External tools** (`sed`, `awk`, `grep`) fork a new process, which is slower, especially inside loops.
    
- **Prefer Bash expansions** for simple substring and pattern removal.
    
- **For heavy text processing on large files**, external tools (like `awk`) are actually faster because they are optimized.
    

**Inefficient loop:**
```bash
while read line; do
    result=$(echo "$line" | sed 's/foo/bar/')  # forks sed for each line
done < bigfile.txt
```

**Better: use Bash expansion:**
```bash
while read line; do
    result="${line//foo/bar}"   # no fork
done < bigfile.txt
```

**Best: let `sed` process the whole file:**
```bash
sed 's/foo/bar/g' bigfile.txt > output.txt
```

---
## Best Practices

1. **Prefer built‑in expansions** over external tools for simple operations.
    
2. **Quote variables** when using them in expansions: `"${var}"`.
    
3. **Use `[[ ]]` for pattern matching** – it's cleaner than external `grep`.
    
4. **Remember that removals and replacements are non‑destructive** – assign the result back to the variable if needed: `var="${var#prefix}"`.
    
5. **Use `-n` and `-z`** to test string emptiness rather than comparing to `""`.
    
6. **Be careful with whitespace** – trimming leading/trailing spaces requires pattern removal or external tools.


**Trim leading/trailing whitespace (using pattern removal):**
```bash
trim() {
    local var="$1"
    var="${var#"${var%%[![:space:]]*}"}"   # trim leading
    var="${var%"${var##*[![:space:]]}"}"   # trim trailing
    echo "$var"
}
```

---
## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`${str: -5}` missing space|Interpreted as default value|`${str: -5}` (space) or `${str:(-5)}`|
|`${#arr}` instead of `${#arr[@]}`|Gives length of first element, not array|`${#arr[@]}`|
|Using `=` instead of `==` in `[[ ]]` for pattern matching? Actually `=` works, but `==` is clearer|–|`[[ $str == *sub* ]]`|
|Forgetting quotes in `${var#pattern}`|Not usually a problem, but pattern may contain spaces|`"${var#pattern}"`|
|Using `sed` inside a loop|Very slow|Use Bash expansion or process whole file|
|Expecting `${var/pattern/replace}` to change `var`|It returns the result; `var` unchanged|`var="${var/pattern/replace}"`|

---

## Next Steps

You can practice by writing a script that:

- Extracts the domain from an email address (`user@example.com` → `example.com`).
    
- Renames all `.txt` files to `.bak` using string replacement.
    
- Converts a given string to camelCase or snake_case.


> [!tip] **Link this note**  
> Add `- [ ] [[String Manipulation]]` to your [[Bash Scripting]] MOC under "Advanced Techniques".

---

**End of note.**  
This is your complete reference for string manipulation in Bash. Use these built‑in expansions to process text efficiently without external tools.
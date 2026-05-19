# Arrays

> [!info] **Purpose**  
> This note explains how to store multiple values in a single variable using arrays. Bash supports one‑dimensional indexed arrays (available in all versions) and associative arrays (key‑value maps, Bash 4.0+).

---

## Table of Contents

- [[#What are Arrays?]]
- [[#Indexed Arrays]]
  - [[#Declaration and Assignment]]
  - [[#Accessing Elements]]
  - [[#Adding Elements]]
  - [[#Removing Elements]]
  - [[#Array Length]]
  - [[#Slicing]]
  - [[#Looping Over Indexed Arrays]]
- [[#Associative Arrays (Bash 4.0+)]]
  - [[#Declaration]]
  - [[#Accessing Values]]
  - [[#Adding and Removing]]
  - [[#Looping Over Keys and Values]]
- [[#Passing Arrays to Functions]]
- [[#Reading Arrays from Files]]
- [[#Common Use Cases]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What are Arrays?

An **array** is a variable that holds multiple values, each identified by an index or key.

- **Indexed array** – values are stored at integer indices (starting from 0).
- **Associative array** – values are stored at string keys (like a dictionary or hash map). Requires Bash 4.0 or later.

**Why use arrays?**  
Instead of creating separate variables (`file1`, `file2`, `file3`…), use one array to hold all related values.

---

## Indexed Arrays

### Declaration and Assignment

**Empty array:**
```bash
my_array=()
```

**With initial values:**
```bash
fruits=("apple" "banana" "cherry")
```

**Assign by index:**
```bash
colors[0]="red"
colors[1]="green"
colors[2]="blue"
```

**Mixed assignment (some indices omitted):**
```bash
data=([0]="zero" [3]="three" [5]="five")
```

### Accessing Elements

Use `${array[index]}`. Indices start at 0.

```bash
fruits=("apple" "banana" "cherry")
echo "${fruits[0]}"   # apple
echo "${fruits[1]}"   # banana
echo "${fruits[2]}"   # cherry
```

**All elements:**
```bash
echo "${fruits[@]}"   # apple banana cherry
```

**All elements as a single word (joins with first character of IFS):**
```bash
echo "${fruits[*]}"   # "apple banana cherry" (space‑separated by default)
```

### Adding Elements

**Append using `+=` (Bash 3.1+):**

```bash
fruits+=("orange")
```

**Assign to next available index (explicit):**
```bash
fruits[${#fruits[@]}]="grape"
```

### Removing Elements

**Remove a single element (leaves a hole, index still exists but value is unset):**

```bash
unset fruits[1]   # removes 'banana'
```

**Re‑index after removal (to close holes):**
```bash
fruits=("${fruits[@]}")   # renumbers indices contiguously
```

**Remove entire array:**
```bash
unset fruits
```

### Array Length

Number of elements (including holes? No – `#` counts set elements):
```bash
echo "${#fruits[@]}"   # length
```

### Slicing

Extract a subarray: `${array[@]:start:length}`
```bash
arr=(a b c d e)
slice=("${arr[@]:1:3}")   # b c d
echo "${slice[@]}"
```

If `length` is omitted, slices to the end:
```bash
tail=("${arr[@]:2}")      # c d e
```

### Looping Over Indexed Arrays

**Loop over values:**
```bash
for fruit in "${fruits[@]}"; do
    echo "Fruit: $fruit"
done
```

**Loop over indices:**
```bash
for i in "${!fruits[@]}"; do
    echo "$i: ${fruits[$i]}"
done
```

**C‑style for loop with indices:**
```bash
for ((i=0; i<${#fruits[@]}; i++)); do
    echo "$i: ${fruits[$i]}"
done
```

---
## Associative Arrays (Bash 4.0+)

Associative arrays use string keys instead of numeric indices. They are like dictionaries in other languages.

### Declaration

**Requires `declare -A`:**
```bash
declare -A colors
```

**Initialize with values:**
```bash
declare -A colors=(
    ["red"]="#FF0000"
    ["green"]="#00FF00"
    ["blue"]="#0000FF"
)
```

### Accessing Values

```bash
echo "${colors["red"]}"   # #FF0000
```

**All values:**
```bash
echo "${colors[@]}"       # #FF0000 #00FF00 #0000FF
```

**All keys:**
```bash
echo "${!colors[@]}"      # red green blue
```

### Adding and Removing

**Add or update:**
```bash
colors["yellow"]="#FFFF00"
```

**Remove a key:**
```bash
unset colors["green"]
```

### Looping Over Keys and Values

**Loop over keys:**
```bash
for key in "${!colors[@]}"; do
    echo "Key: $key"
done
```

**Loop over values:**
```bash
for value in "${colors[@]}"; do
    echo "Value: $value"
done
```


**Loop over key‑value pairs:**
```bash
for key in "${!colors[@]}"; do
    echo "$key -> ${colors[$key]}"
done
```

---
## Passing Arrays to Functions

You cannot pass an array directly as an argument. Instead, pass the array elements and reconstruct inside the function.

**Passing indexed array:**
```bash
print_array() {
    local arr=("$@")
    for item in "${arr[@]}"; do
        echo "$item"
    done
}

my_array=("a" "b" "c")
print_array "${my_array[@]}"
```

**Returning an array from a function:** Use `echo` and capture with `mapfile` or array assignment.
```bash
get_files() {
    echo "file1.txt"
    echo "file2.txt"
    echo "file3.txt"
}

mapfile -t files < <(get_files)
# or
files=($(get_files))   # but this splits on spaces
```

---
## Reading Arrays from Files

**Read lines into an indexed array (one line per element):**
```bash
mapfile -t lines < file.txt
```

**Read words from a line into an array:**
```bash
read -a words <<< "apple banana cherry"
```

**Read CSV line into array (custom IFS):**
```bash
IFS=, read -a fields <<< "value1,value2,value3"
```

---
## Common Use Cases

|Use Case|Example|
|---|---|
|**List of files**|`files=(*.txt)`|
|**Command line arguments**|`args=("$@")`|
|**Menu options**|`options=("Start" "Stop" "Restart" "Exit")`|
|**Configuration from file**|`mapfile -t config < config.txt`|
|**Parsing CSV**|`IFS=, read -a row`|
|**Lookup tables (associative)**|`declare -A dict=(["key"]="value")`|

---

## Best Practices

1. **Always quote expansions** – `"${array[@]}"` not `${array[@]}`.
    
2. **Use `[@]` for separate elements**, `[*]` only when you need a single string.
    
3. **Use `local -a` for local indexed arrays** inside functions: `local -a myarr`.
    
4. **Use `local -A` for local associative arrays** (Bash 4.0+).
    
5. **Check Bash version before using associative arrays**:

```bash
if [ "${BASH_VERSINFO[0]}" -lt 4 ]; then
    echo "Associative arrays require Bash 4.0+" >&2
    exit 1
fi
```

6. **Use `mapfile` for reading files into arrays** (Bash 4.0+). For older Bash, use a `while read` loop.

---
## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`${array}` without index|Expands to first element only|`${array[0]}` or `"${array[@]}"`|
|`$array[@]` missing braces|`$array` expands, then `[@]` is literal|`"${array[@]}"`|
|`for i in ${array[@]}` without quotes|Splits elements containing spaces|`for i in "${array[@]}"`|
|`unset array` instead of `unset array[1]`|Deletes entire array|`unset 'array[1]'` (quotes prevent globbing)|
|Using associative array without `declare -A`|Treated as indexed array (silent failure)|`declare -A assoc`|
|`echo ${#array}`|Returns length of first element (string length)|`echo ${#array[@]}`|
|`array=` instead of `array=()`|Assigns empty string, not empty array|`array=()`|

---

## Next Steps

You can practice by writing a script that:

- Stores a list of filenames in an array, then processes each.
    
- Uses an associative array to count occurrences of words in a file.
    
- Implements a simple todo list manager with add, list, and remove operations.


> [!tip] **Link this note**  
> Add `- [ ] [[Arrays]]` to your [[Bash Scripting]] MOC under "Core Concepts".

---

**End of note.**  
This is your complete reference for Bash arrays. Use them to manage collections of data efficiently.
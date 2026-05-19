# Error Handling

> [!info] **Purpose**  
> This note explains how to make Bash scripts robust by detecting, reporting, and recovering from errors. Proper error handling prevents silent failures and ensures your script behaves predictably.

---

## Table of Contents

- [[#Exit Codes]]
- [[#Checking Command Success]]
- [[#The `set` Builtin (Robust Script Header)]]
- [[#The `trap` Command (Cleanup and Interrupts)]]
- [[#Custom Error Function]]
- [[#Error Logging]]
- [[#Subshells and Error Propagation]]
- [[#Common Patterns]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## Exit Codes

Every command in Bash returns an **exit status** (also called return code or exit code) – an integer between 0 and 255.

- **0** – success (command executed without error).
- **Non‑zero** – failure (1–255, each command may have its own meanings).

After a command finishes, the exit code is stored in the special variable `$?`.

```bash
ls /etc/passwd
echo $?   # 0 (success)

ls /nonexistent
echo $?   # 2 (typically "no such file or directory")
```

**Common exit codes used by Bash itself:**

|Code|Meaning|
|---|---|
|0|Success|
|1|Catchall for general errors|
|2|Misuse of shell builtins (e.g., missing keyword)|
|126|Command invoked cannot execute (permission problem)|
|127|Command not found|
|128+n|Fatal error signal n (e.g., 130 = Ctrl+C)|

> [!tip] You can define your own exit codes in scripts. Use `exit 0` for success, and any non‑zero for different error conditions (e.g., `exit 1` for missing argument, `exit 2` for file not found).

---

## Checking Command Success

You can check `$?` directly, or use the command itself as a condition.

**Explicit check:**
```bash
mkdir /tmp/mydir
if [ $? -ne 0 ]; then
    echo "Failed to create directory" >&2
    exit 1
fi
```

**Better – use command as condition:**
```bash
if mkdir /tmp/mydir; then
    echo "Directory created successfully"
else
    echo "Failed to create directory" >&2
    exit 1
fi
```

**Short‑circuit `&&` and `||`:**
```bash
mkdir /tmp/mydir || { echo "Failed" >&2; exit 1; }
```

---
## The `set` Builtin (Robust Script Header)

`set` changes shell behavior. Add these options at the top of every production script:

```bash
#!/bin/bash
set -euo pipefail
```

|Option|Effect|
|---|---|
|`set -e` (or `set -o errexit`)|Exit immediately if a command exits with non‑zero status (except in conditions, pipelines, etc. – see notes).|
|`set -u` (or `set -o nounset`)|Treat unset variables as an error when expanding.|
|`set -o pipefail`|In a pipeline, the exit status is that of the last command that failed (or 0 if all succeed). Without this, only the last command’s status matters.|

**Combined effect:**

- `-e` – stops script on error.
    
- `-u` – prevents silent use of undefined variables.
    
- `pipefail` – catches failures in any part of a pipeline.


> [!warning] `set -e` has surprising behaviors (e.g., commands in `if` conditions or `&&`/`||` lists do not trigger exit). For complete safety, combine with `trap ERR`.

**Example without `set -e`:**
```bash
#!/bin/bash
cd /nonexistent      # fails, but script continues
rm important_file    # dangerous: runs anyway
```

**With `set -e`:**
```bash
#!/bin/bash
set -e
cd /nonexistent      # script exits here
rm important_file    # never reached
```

---
## The `trap` Command (Cleanup and Interrupts)

`trap` allows you to execute commands when the script receives signals or exits.

**Syntax:**
```bash
trap 'commands' SIGNAL
```

**Common signals:**

- `EXIT` – runs when script exits normally (or via `exit`).
    
- `ERR` – runs when a command returns non‑zero (if `set -e` is enabled).
    
- `INT` – interrupt (Ctrl+C).
    
- `TERM` – termination signal.
    
- `HUP` – hangup.

**Cleanup temporary files on exit:**
```bash
#!/bin/bash
tempfile=$(mktemp)

cleanup() {
    rm -f "$tempfile"
    echo "Cleaned up"
}
trap cleanup EXIT

# script continues...
```

**Handle Ctrl+C gracefully:**
```bash
trap 'echo "Interrupted, exiting..."; exit 1' INT TERM
```

**Print line number on error (for debugging):**
```bash
error_report() {
    echo "Error on line $1" >&2
}
trap 'error_report $LINENO' ERR
```

>[!tip] Always quote commands in `trap` if they contain variables or multiple statements. Use single quotes to delay expansion until the trap is triggered.

---
## Custom Error Function

Define a function to standardize error messages and exit.
```bash
die() {
    echo "ERROR: $*" >&2
    exit 1
}

# Usage:
[ -f "$config" ] || die "Config file $config not found"
```

**With optional exit code:**
```bash
die() {
    local exit_code=$1
    shift
    echo "ERROR: $*" >&2
    exit "$exit_code"
}

# Usage: die 2 "Invalid argument"
```

---
## Error Logging

Send errors to both stderr and a log file.
```bash
log_error() {
    local msg="[$(date '+%Y-%m-%d %H:%M:%S')] ERROR: $*"
    echo "$msg" >&2
    echo "$msg" >> /var/log/myscript.log
}
```

**Redirect all stderr to a log file:**
```bash
exec 2>> /var/log/myscript.log
```

**Log both stdout and stderr:**
```bash
exec > >(tee -a /var/log/myscript.log) 2>&1
```

---
## Subshells and Error Propagation

Commands inside subshells (parentheses `(...)`) or pipelines may not trigger `set -e` as expected.

**Subshell example:**
```bash
set -e
(cd /nonexistent; echo "inside")   # error inside subshell, but script continues!
echo "This still runs"
```

**Fix: use `set -e` inside subshell as well:**
```bash
(set -e; cd /nonexistent; echo "inside")
```

**Or use `||` to propagate error:**
```bash
(cd /nonexistent) || exit 1
```

For pipelines, `set -o pipefail` helps, but still test `$?` if needed.

---
## Common Patterns

### Check required tools

```bash
for cmd in curl jq grep; do
    if ! command -v "$cmd" &>/dev/null; then
        echo "Error: $cmd not found. Please install it." >&2
        exit 1
    fi
done
```

### Safe file operations

```bash
cp "$src" "$dest" || { echo "Copy failed" >&2; exit 1; }
```

### Retry logic with error handling

```bash
max_retries=3
count=0
until [ $count -ge $max_retries ]; do
    if wget "$url"; then
        break
    fi
    ((count++))
    echo "Retry $count/$max_retries..."
    sleep 2
done
if [ $count -eq $max_retries ]; then
    echo "Failed after $max_retries attempts" >&2
    exit 1
fi
```

### Validate input

```bash
if [[ ! "$1" =~ ^[0-9]+$ ]]; then
    echo "Error: Argument must be a number" >&2
    exit 1
fi
```

---
## Best Practices

1. **Start every script with `set -euo pipefail`** (and possibly `IFS=$'\n\t'`).
    
2. **Use `trap` to clean up temporary files** on exit or interrupt.
    
3. **Provide meaningful error messages** – include context (filename, line number, etc.).
    
4. **Send errors to stderr** (`>&2`) – so they don’t mix with normal output.
    
5. **Use custom `die` function** to reduce repetition.
    
6. **Check exit status of critical commands** – don't assume they succeed.
    
7. **Validate arguments and file existence** before using them.
    
8. **Avoid `set -e` in interactive scripts** – it can close your shell unexpectedly.


---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`set -e` but no `trap ERR`|Some errors (e.g., in `if` conditions) are ignored|Use `trap ... ERR` or explicit checks|
|Not quoting `$?`|Not needed, but forgetting `$`? Actually `$?` is fine|–|
|`command` without checking exit|Script continues even after failure|Check with `if command; then` or `command \| exit`|
|Using `exit` without a code|Exits with previous command’s status (may be 0)|`exit 1` for failure|
|Not sending errors to stderr|Errors appear in normal output, hard to separate|`echo "msg" >&2`|
|`trap` with double quotes|Variables expand at definition time, not trap time|Use single quotes: `trap 'rm "$file"' EXIT`|

---

## Next Steps

You can practice by:

- Adding robust error handling to the backup script (check source, destination, tar success).
    
- Writing a script that retries a network operation with exponential backoff.
    
- Implementing a logging function that writes to syslog using `logger`.


> [!tip] **Link this note**  
> Add `- [ ] [[Error Handling]]` to your [[Bash Scripting]] MOC under "Advanced Techniques".

---

**End of note.**  
This is your complete reference for error handling in Bash. Use these techniques to write scripts that fail safely and report problems clearly.
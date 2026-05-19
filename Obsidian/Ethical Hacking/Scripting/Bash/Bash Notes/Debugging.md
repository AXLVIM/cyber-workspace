# Debugging

> [!info] **Purpose**  
> This note explains techniques for finding and fixing errors in Bash scripts. Debugging is the process of understanding what your script is actually doing versus what you intended it to do.

---

## Table of Contents

- [[#Debugging Mindset]]
- [[#Syntax Checking (`bash -n`)]]
- [[#Execution Tracing (`set -x`)]]
- [[#Customizing the Trace Prompt (`PS4`)]]
- [[#Verbose Mode (`set -v`)]]
- [[#Checking for Unset Variables (`set -u`)]]
- [[#Debugging with `trap`]]
- [[#Static Analysis with `shellcheck`]]
- [[#Logging and `logger`]]
- [[#Debugging Subshells and Pipelines]]
- [[#Common Bug Patterns]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## Debugging Mindset

When a script misbehaves, follow this systematic approach:

1. **Reproduce the error** – run the script under the same conditions.
2. **Isolate the problem** – narrow down which section or line causes the issue.
3. **Examine variables** – print values at critical points.
4. **Check exit codes** – `echo $?` after suspicious commands.
5. **Simplify** – comment out parts to find minimal failing case.
6. **Use debugging tools** – `bash -x`, `shellcheck`, `trap`.

> [!tip] The best debugging tool is often `set -x`. Use it liberally.

---

## Syntax Checking (`bash -n`)

Before running a script, check for syntax errors without executing it.

```bash
bash -n script.sh
```

- Exits with 0 if syntax is valid.
    
- Prints error messages for missing quotes, unclosed blocks, etc.

**Example:**
```bash
$ bash -n broken.sh
broken.sh: line 5: unexpected EOF while looking for matching `"'
broken.sh: line 6: syntax error: unexpected end of file
```

> [!warning] `bash -n` does **not** catch runtime errors (e.g., using an unset variable, file not found). It only checks grammar.

---

## Execution Tracing (`set -x`)

`set -x` prints every command (after expansion) to stderr before executing it. This is the most powerful debugging tool.

**Enable tracing:**
```bash
set -x
```

**Disable tracing:**
```bash
set +x
```

**Example:**
```bash
#!/bin/bash
name="Alice"
set -x
echo "Hello $name"
set +x
echo "Done"
```

**Output**
```text
+ echo 'Hello Alice'
Hello Alice
+ set +x
Done
```

**Run entire script with tracing from the command line:**
```bash
bash -x script.sh
```

> [!tip] Use `set -x` around suspicious sections, not the whole script, to avoid overwhelming output.

---

## Customizing the Trace Prompt (`PS4`)

The `PS4` variable controls the prefix printed before each traced line. Default is `+`.

**Customize to show line numbers and function names:**
```bash
export PS4='+ ${BASH_SOURCE}:${LINENO}: ${FUNCNAME[0]:+${FUNCNAME[0]}(): }'
set -x
```

**Example output:**
```text
+ ./script.sh:5: main(): name="Alice"
+ ./script.sh:6: main(): echo 'Hello Alice'
Hello Alice
```

**Set PS4 permanently for debugging sessions:** add to `~/.bashrc` (commented out normally).

---

## Verbose Mode (`set -v`)

`set -v` prints each line of the script as it is read (before expansion). It shows comments and blank lines, unlike `-x`.

```bash
set -v
```

**Combined tracing (`-xv`):**
```bash
bash -xv script.sh
```

This shows both the raw input line and the expanded command.

---

## Checking for Unset Variables (`set -u`)

`set -u` (or `set -o nounset`) makes the script exit when an unset variable is expanded. This catches typos and missing assignments.

```bash
#!/bin/bash
set -u
echo "$undefined_var"   # script exits with error
```

**Error message:**
```text
script.sh: line 3: undefined_var: unbound variable
```

> [!tip] Use `set -eu` in development. For production, handle missing variables explicitly with `${var:-default}`.

---

## Debugging with `trap`

`trap` can execute commands on errors or at specific points.

**Print line number when an error occurs**
```bash
#!/bin/bash
error_report() {
    echo "Error on line $1" >&2
}
trap 'error_report $LINENO' ERR
```

**Run a command before each line (using `DEBUG` pseudo‑signal):**
```bash
trap 'echo "About to execute line $LINENO"' DEBUG
```

**Show variable values on exit:**
```bash
trap 'echo "At exit: var=$var"' EXIT
```

> [!note] `DEBUG` trap is Bash‑specific and can slow down scripts significantly. Use sparingly.

---

## Static Analysis with `shellcheck`

`shellcheck` is a static analysis tool that finds common bugs, style issues, and portability problems.

**Install:**
```bash
# Debian/Ubuntu
sudo apt install shellcheck

# macOS
brew install shellcheck

# Other: https://www.shellcheck.net/
```

**Run on a script:**
```bash
shellcheck script.sh
```

**Example output:**
```text
In script.sh line 3:
if [ $name = "Alice" ]
     ^-- SC2086: Double quote to prevent globbing and word splitting.
```

**Common `shellcheck` warnings:**

|Code|Meaning|
|---|---|
|SC2086|Unquoted variable|
|SC2046|Quote command substitution|
|SC2006|Use `$(...)` instead of backticks|
|SC2034|Variable assigned but not used|
|SC2154|Variable referenced but not assigned|

> [!tip] Integrate `shellcheck` into your editor (VS Code plugin, vim‑syntastic) or pre‑commit hooks.

---

## Logging and `logger`

Insert logging statements to track script flow without interactive debugging.

**Simple `echo` statements:**
```bash
echo "DEBUG: Entering function foo" >&2
echo "DEBUG: value of var is $var" >&2
```

**Use `logger` to send messages to system log (`/var/log/syslog`):**
```bash
logger -t myscript "Started backup"
logger -t myscript -p user.err "Backup failed"
```

**View logs:**
```bash
tail -f /var/log/syslog | grep myscript
```

---
## Debugging Subshells and Pipelines

Commands in subshells (parentheses `(...)`) or pipelines (`|`) can make debugging harder.

**Problem: variables set in a subshell are lost:**
```bash
echo "hello" | read var   # var is empty after pipeline
echo "$var"
```

**Fix: use process substitution or here‑string:**
```bash
read var <<< "hello"
```

**Debugging inside subshells:** enable `set -x` inside the subshell as well:
```bash
(set -x; cd /tmp; ls)
```

**Check pipeline exit status with `PIPESTATUS` array:**
```bash
false | true
echo "${PIPESTATUS[0]} ${PIPESTATUS[1]}"   # 1 0
```

---
## Common Bug Patterns

|Bug|Example|Detection|
|---|---|---|
|Unquoted variable|`rm $file`|`shellcheck` SC2086|
|Missing `$` in variable|`var=5; echo var` prints "var"|`set -u` won't catch; visual inspection|
|Forgetting spaces in `[ ]`|`[ "$a"="$b" ]`|`bash -n` catches syntax error|
|Using `=` for numeric comparison|`[ $a = $b ]` works but compares strings|Use `-eq` for numbers|
|Wrong redirection order|`command 2>&1 > file` (stderr still to terminal)|Order: `command > file 2>&1`|
|Missing `then` or `fi`|`if [ true ]; echo`|`bash -n`|
|Using `$@` unquoted|`for i in $@`|Use `"$@"`|

---

## Best Practices

1. **Always run `shellcheck`** on every script before committing.
    
2. **Use `set -euo pipefail`** at the top of production scripts.
    
3. **Start debugging with `bash -n`** to catch syntax errors first.
    
4. **Use `set -x` on minimal sections** – not the whole script.
    
5. **Customize `PS4`** to show line numbers.
    
6. **Add debug functions** that can be enabled with an environment variable.

**Example debug function:**
```bash
DEBUG=${DEBUG:-0}
debug() {
    if [ "$DEBUG" -eq 1 ]; then
        echo "[DEBUG] $*" >&2
    fi
}
debug "Starting loop"
```

Run with `DEBUG=1 ./script.sh` to see debug output.

7. **Log errors, not just print them** – use `logger` or write to a file.
    
8. **Test edge cases** – empty strings, spaces in filenames, missing files.
    

---

## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`set -x` without turning off later|Huge output, hard to read|Use `set +x` after the suspect block|
|Forgetting `set -u`|Unset variables become empty strings, causing silent errors|Add `set -u` or use `${var:-}`|
|Debugging with `echo` that changes output|`echo` can be captured or interfere|Print to stderr: `echo >&2`|
|Not quoting variables in `set -x` output|`set -x` already shows quotes, but unquoted in script leads to bugs|Quote variables in script|
|Ignoring `shellcheck` warnings|Many real bugs|Fix all warnings, or add `# shellcheck disable=SCxxxx` comments|

---

## Next Steps

You can practice by:

- Introducing a bug into a working script and using `bash -x` to find it.
    
- Running `shellcheck` on your existing scripts and fixing all warnings.
    
- Writing a script that deliberately fails and using `trap ERR` to log the error.

> [!tip] **Link this note**  
> Add `- [ ] [[Debugging]]` to your [[Bash Scripting]] MOC under "Advanced Techniques".

---

**End of note.**  
This is your complete reference for debugging Bash scripts. Use these tools and techniques to find and fix errors quickly.
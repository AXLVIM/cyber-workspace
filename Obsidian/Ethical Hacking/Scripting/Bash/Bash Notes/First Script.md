# First Script

> [!info] **Purpose**  
> This note teaches you how to create, make executable, and run your first Bash script. It also explains the shebang line, permissions, and common pitfalls.

---

## Table of Contents

- [[#What is a Script?]]
- [[#The Shebang (`#!`)]]
- [[#Step‑by‑Step: Your First Script]]
- [[#Running a Script]]
- [[#Understanding Permissions (chmod)]]
- [[#Common Mistakes and Fixes]]
- [[#Portability Notes]]
- [[#Next Steps]]

---

## What is a Script?

A **script** is a plain text file containing a sequence of commands. When you execute the script, the shell reads each line and runs it as if you had typed it manually.

**Script vs. interactive commands:**

| Aspect | Interactive | Script |
|--------|-------------|--------|
| Input | Type each command | Commands read from file |
| Repetition | Must retype | Run once, repeat any time |
| Sharing | Copy‑paste | Single file to share |
| Documentation | None (unless you write notes) | The file itself is documentation |

> [!tip] Any command you can type in the terminal can go into a script.

---

## The Shebang (`#!`)

The **shebang** (from "sharp bang") is the first line of a script. It tells the operating system which interpreter to use.

**Syntax:**
```bash
#!interpreter_path
```

**For Bash scripts:**
```bash
#!/bin/bash
```

**How it works:**

1. The system reads the first two bytes `#!`.
    
2. It extracts the path to the interpreter (`/bin/bash`).
    
3. It runs the script using that interpreter.
    

> [!warning] The shebang **must** be the first line of the file. No spaces, no blank lines above it.

**Common shebangs:**

|Shebang|Interpreter|
|---|---|
|`#!/bin/bash`|Bash|
|`#!/bin/sh`|Bourne/POSIX shell|
|`#!/usr/bin/env bash`|Finds `bash` in `$PATH` (more portable)|
|`#!/usr/bin/python3`|Python 3|
|`#!/bin/awk -f`|AWK|

> [!note] **`/usr/bin/env` trick**  
> Using `#!/usr/bin/env bash` is more portable because it locates `bash` via the environment's `PATH`. However, it can be slightly slower and less predictable in highly controlled environments. For most users, it is fine.

---

## Step‑by‑Step: Your First Script

### Step 1 – Create a file

Use any text editor. In the terminal:
```bash
nano hello.sh
```

(You can also use `vim`, `code`, `gedit`, etc.)

### Step 2 – Write the script
```bash
#!/bin/bash
# This is a comment. It is ignored by the shell.
echo "Hello, world!"
echo "Today is $(date)"
echo "Your current directory is: $PWD"
```

**Explanation:**

- `#!/bin/bash` – shebang.
    
- `# This is a comment` – ignored, but useful for documentation.
    
- `echo` – prints text to the terminal.
    
- `$(date)` – command substitution (runs `date` and inserts its output).
    
- `$PWD` – environment variable containing current directory.

### Step 3 – Save and exit

- In `nano`: `Ctrl+O`, `Enter`, `Ctrl+X`.
    
- In `vim`: `Esc`, `:wq`, `Enter`.
    
- In a GUI editor: just save.

### Step 4 – Make the script executable

By default, a new file does not have execute permission. You must add it:
```bash
chmod +x hello.sh
```

### Step 5 – Run the script
```bash
./hello.sh
```

**Expected output:**
```bash
Hello, world!
Today is Sun Apr 12 14:30:00 UTC 2026
Your current directory is: /home/yourname
```

---
## Running a Script

You can run a Bash script in several ways:

|Method|Command|Notes|
|---|---|---|
|Direct (requires execute permission)|`./script.sh`|Uses shebang interpreter. `./` means "current directory".|
|Explicit interpreter|`bash script.sh`|Ignores shebang. No execute permission needed.|
|Source (run in current shell)|`source script.sh` or `. script.sh`|Variables and functions persist after script ends.|
|With absolute path|`/home/user/script.sh`|Works from any directory.|

> [!warning] **Why `./`?**  
> For security, the current directory (`.`) is usually not in `$PATH`. Without `./`, Bash looks for `script.sh` in system directories (e.g., `/usr/bin`) and will not find it.

---

## Understanding Permissions (chmod)

Every file has three sets of permissions: **owner**, **group**, and **others**. Each set has three flags: **read (r)**, **write (w)**, **execute (x)**.

**View permissions:**
```bash
ls -l hello.sh
```

Output example:
```bash
-rwxr-xr-- 1 alice staff 42 Apr 12 14:30 hello.sh
```

- `-` (first char) = regular file ( `d` = directory, `l` = link)
    
- `rwx` = owner can read, write, execute
    
- `r-x` = group can read, execute (not write)
    
- `r--` = others can read only

**Change permissions with `chmod`:**

- `chmod +x file` – add execute for all (owner, group, others).
    
- `chmod u+x file` – add execute for user (owner) only.
    
- `chmod 755 file` – numeric mode: owner=7 (rwx), group=5 (r-x), others=5 (r-x).
    
- `chmod -x file` – remove execute permission.


> [!tip] **Minimum for a script**  
> `chmod u+x script.sh` (only you can execute). For shared scripts, `chmod 755 script.sh`.

---

## Common Mistakes and Fixes

|Mistake|Error message|Fix|
|---|---|---|
|No shebang|`command not found` or runs with wrong shell (e.g., `sh` instead of `bash`)|Add `#!/bin/bash` as first line.|
|Missing execute permission|`Permission denied`|Run `chmod +x script.sh`.|
|Forgetting `./`|`command not found`|Use `./script.sh` or `bash script.sh`.|
|Windows line endings (`\r\n`)|`$'\r': command not found`|Convert with `dos2unix script.sh` or in VS Code: change line endings to LF.|
|Spaces around `=` in variable|`command not found` (e.g., `name = John`)|Remove spaces: `name="John"`.|
|Using `#! /bin/bash` with a space|`bad interpreter: No such file or directory`|Remove space: `#!/bin/bash`.|
|Script not in `$PATH`|`command not found`|Use `./` or add directory to `PATH` (not recommended for beginners).|

> [!warning] **Windows line endings** are the most common hidden issue. If you edit a script on Windows and transfer it to Linux/macOS, run `dos2unix script.sh` before executing.

---

## Portability Notes

- **`#!/bin/bash`** works on most Linux systems, but not on some BSD systems or minimal containers where Bash is not installed.
    
- **`#!/usr/bin/env bash`** is more portable because it finds `bash` via `PATH`. Use this if you distribute scripts.
    
- Avoid Bash‑isms (like `[[ ]]`, arrays, `+=` on strings) if you need to run under `#!/bin/sh`. For your own scripts, using Bash features is fine.
    

**Example of a portable shebang:**
```bash
#!/usr/bin/env bash
```

## Next Steps

You can also modify your `hello.sh` script:

- Add a variable: `name="World"` and `echo "Hello $name"`.
    
- Ask for user input: `read -p "Enter your name: " name`.
    
- Show the current date in a different format: `date +%A` (prints day of week).


> [!tip] **Link this note**  
> Add `- [ ] [[First Script]]` to your [[Bash Scripting]] MOC under "Foundations".

---

**End of note.**  
This is your complete guide to creating and running your first Bash script. Practice by writing a script that prints your username, current directory, and a greeting.
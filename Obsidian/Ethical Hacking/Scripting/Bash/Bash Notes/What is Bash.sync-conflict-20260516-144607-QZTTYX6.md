# What is Bash?

> [!info] **Scope**  
> This note explains the terminal, the shell, and Bash specifically. It is intended for absolute beginners and serves as a foundation for scripting.

---

## Table of Contents

- [[#Terminal vs Shell vs Bash]]
- [[#A Brief History of Bash]]
- [[#How to Access Bash]]
- [[#Basic Bash Commands (First 10)]]
- [[#Bash Configuration Files]]
- [[#Bash vs Other Shells]]
- [[#Common Misconceptions]]
- [[#Next Steps]]

---

## Terminal vs Shell vs Bash

These three terms are often used interchangeably, but they mean different things.

| Term | Definition | Analogy |
|------|------------|---------|
| **Terminal** (or terminal emulator) | A program that provides a text‑based window to interact with a shell. Examples: GNOME Terminal, iTerm2, Windows Terminal, Konsole. | The **physical screen** and keyboard. |
| **Shell** | A command‑line interpreter that reads your commands, executes them, and shows output. It is a program running inside the terminal. | The **person** who understands your commands. |
| **Bash** | A specific shell (Bourne Again SHell). It is the default shell on most Linux distributions and older macOS versions. | One specific **language** that person speaks (like English). |

**How they work together:**  
You open a **terminal** emulator → it launches a **shell** (by default, Bash) → you type commands → the shell executes them.

> [!tip] Check your current shell
> ```bash
> echo $SHELL          # prints the path of your login shell
> ps -p $$             # shows the process name of your current shell
> ```

---

## A Brief History of Bash

- **1971** – Unix introduced the Thompson shell (`sh`).
- **1977** – Bourne shell (`sh`) became the standard Unix shell (still the basis for POSIX shell scripts).
- **1989** – Brian Fox wrote **Bash** (Bourne Again SHell) for the GNU Project as a free replacement for the Bourne shell.
- **1990s‑present** – Bash becomes the default shell on Linux and macOS (until macOS Catalina switched to `zsh`).

**Why Bash succeeded:**
- Free software (GPL license)
- Backward‑compatible with Bourne shell (`sh`)
- Added interactive features: command history, job control, aliases, tab completion
- Powerful scripting features: arrays, associative arrays, advanced string manipulation

---

## How to Access Bash

### Linux
- Already installed. Open a terminal (Ctrl+Alt+T usually).
- If another shell is default, type `bash` to switch.

### macOS
- **Older versions (before Catalina)** – default shell is Bash.
- **Catalina and later** – default is `zsh`. You can still use Bash:
```bash
  bash               # start Bash
  chsh -s /bin/bash  # change default shell to Bash (permanent)
```

### Windows

- **WSL (Windows Subsystem for Linux)** – install a Linux distribution (Ubuntu, Debian) from Microsoft Store.
    
- **Git Bash** – comes with Git for Windows; lightweight Bash emulation.
    
- **Cygwin** – larger POSIX compatibility layer.
    
- **Windows Terminal** – can host WSL or Git Bash.
    

### Online (no installation)

- **Replit**, **CodeSandbox**, **JSLinux** – browser‑based Linux terminals.
    

---

## Basic Bash Commands (First 10)

Master these before scripting. Each command is a small program.

|Command|Example|What it does|
|---|---|---|
|`pwd`|`pwd`|Print Working Directory – shows where you are.|
|`ls`|`ls -la`|List files and directories (`-l` = long format, `-a` = all including hidden).|
|`cd`|`cd /home`|Change Directory. `cd ..` goes up, `cd` alone goes home.|
|`mkdir`|`mkdir newfolder`|Make a new directory.|
|`rmdir`|`rmdir emptyfolder`|Remove an empty directory.|
|`rm`|`rm file.txt`|Remove files. `rm -rf folder` removes folder and contents (dangerous!).|
|`cp`|`cp source dest`|Copy files or directories (`-r` for recursive).|
|`mv`|`mv old new`|Move or rename files/directories.|
|`cat`|`cat file.txt`|Concatenate and display file content.|
|`echo`|`echo "Hello"`|Print text to the terminal.|

> [!warning] **`rm -rf`** is irreversible. Always double‑check the path.

### Pipes and Redirections

- `|` (pipe) – sends output of left command as input to right command:  
    `ls -l | grep ".txt"`
    
- `>` – redirect output to a file (overwrites):  
    `echo "Hello" > greeting.txt`
    
- `>>` – append to a file:  
    `echo "World" >> greeting.txt`
    
- `<` – read input from a file:  
    `sort < unsorted.txt`
    

---

## Bash Configuration Files

When Bash starts as an **interactive login shell**, it reads these files in order:

1. `/etc/profile` (system‑wide)
    
2. `~/.bash_profile` (user‑specific) – if exists, otherwise `~/.bash_login` or `~/.profile`
    

For **interactive non‑login shells** (e.g., opening a terminal inside a GUI), it reads `~/.bashrc`.

**Typical practice:**

- Put **aliases**, **functions**, **prompt customizations** in `~/.bashrc`.
    
- From `~/.bash_profile`, source `~/.bashrc`:
```bash
if [ -f ~/.bashrc ]; then
    source ~/.bashrc
fi
```

**Reload configuration without logging out:**
```bash
source ~/.bashrc
# or
. ~/.bashrc
```

>[!example] Common customizations
>```bash
># ~/.bashrc
alias ll='ls -alF'
export PS1='\u@\h:\w\$ '
export PATH="$HOME/bin:$PATH"
>```

## Bash vs Other Shells

|Shell|Description|Pros|Cons|
|---|---|---|---|
|**sh** (Bourne)|Original Unix shell|POSIX standard, very lightweight|No interactive features (history, completion)|
|**bash**|Bourne Again SHell|Most common, huge user base, feature‑rich|Slightly slower startup, not fully POSIX (but mostly)|
|**zsh**|Z shell|Highly customizable, Oh‑My‑Zsh framework, better auto‑completion|More complex configuration|
|**fish**|Friendly Interactive SHell|Great defaults, syntax highlighting, auto‑suggestions|Not POSIX‑compatible (scripts may break)|
|**dash**|Debian Almquist shell|Very fast, used as `/bin/sh` on Debian/Ubuntu|Fewer features, not for interactive use|

**For scripting:** Bash is the safest choice for portability across Linux and macOS.  
**For interactive use:** zsh or fish may be more pleasant, but Bash is perfectly fine.

---

## Common Misconceptions

|Myth|Reality|
|---|---|
|"Terminal and shell are the same."|No – terminal is the window, shell is the program inside.|
|"Bash is only for Linux."|Bash runs on macOS, Windows (WSL/Git Bash), BSD, and even Android (Termux).|
|"Commands are part of Bash."|Most commands (`ls`, `cp`, `grep`) are external programs. Bash just calls them.|
|"You must learn Bash to use Linux."|Not true – modern Linux has graphical interfaces. But Bash gives you power.|
|"Scripts must have a `.sh` extension."|No – extension is optional. The shebang `#!/bin/bash` determines the interpreter.|

---

## Next Steps

You can also practice the basic commands daily. A good exercise:

- Create a folder `bash_practice`
    
- Inside, create three text files with `echo`
    
- List them, rename one, delete one.


> [!tip] **Pro tip for Obsidian**  
> Link this note from your [[Bash Scripting]] MOC under the "Foundations" section. Add a progress checkbox: `- [ ] [[What is Bash]]`.

---

**End of note.**  
This is everything you need to know about Bash and the terminal as a beginner. Return here when you need to refresh concepts.
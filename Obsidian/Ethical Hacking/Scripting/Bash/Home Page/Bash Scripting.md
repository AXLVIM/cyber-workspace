# 🐚 Bash Scripting – Home

> [!info] **Map of Content**  
> This is your central hub for all Bash scripting knowledge. Click any link to open a detailed note. Collapsible sections keep the overview clean.

## 📚 Table of Contents

- [[#Foundations]] – first steps, shebang, basic script structure
- [[#Core Concepts]] – variables, conditionals, loops, functions, arrays
- [[#Advanced Techniques]] – file tests, string manipulation, error handling, cron, debugging
- [[#Projects]] – ready‑to‑use scripts
- [[#Resources]] – cheat sheets, external links

---

## Foundations

> [!note]- **1.1 What is Bash?** – [[What is Bash]]
> 
> Definition, history, version check, and comparison with other shells (sh, zsh).  
> *Key takeaway: Bash is the default Linux/macOS shell; scripts start with `#!/bin/bash`.*  
> 🔗 [[What is Bash]]

> [!note]- **1.2 Why Script?** – [[Why Script]]
> 
> Automation, repeatability, conditional logic, and real‑world use cases (backups, monitoring, data pipelines).  
> 🔗 [[Why Script]]

> [!note]- **1.3 First Script** – [[First Script]]
> 
> Step‑by‑step: shebang, permissions (`chmod +x`), execution (`./script.sh`). Common pitfalls (Windows line endings, missing shebang).  
> 🔗 [[First Script]]

---

## Core Concepts

> [!note]- **2.1 Variables & Parameter Expansion** – [[Variables]]
> 
> Assignment (`name=value`), referencing (`$name` or `${name}`), special parameters (`$0`, `$#`, `$@`), default values (`${var:-default}`).  
> 🔗 [[Variables]]

> [!note]- **2.2 Command Substitution & Arithmetic** – [[Command Substitution]]
> 
> `$(command)` vs backticks, `$((arithmetic))`, operators, and precedence.  
> 🔗 [[Command Substitution]]

> [!note]- **2.3 User Input (`read`)** – [[Read Command]]
> 
> Options: `-p` (prompt), `-s` (silent), `-t` (timeout), `-n` (character limit). Exit status handling.  
> 🔗 [[Read Command]]

> [!note]- **2.4 Conditionals** – [[Conditionals]]
> 
> `if`, `elif`, `else`, `case`. Numeric (`-eq`, `-gt`), string (`=`, `!=`, `-z`), file tests (`-f`, `-d`). Using `[[ ]]` vs `[ ]`.  
> 🔗 [[Conditionals]]

> [!note]- **2.5 Loops** – [[Loops]]
> 
> `for` (list, brace expansion, C‑style), `while`, `until`, `break`, `continue`.  
> 🔗 [[Loops]]

> [!note]- **2.6 Functions** – [[Functions]]
> 
> Definition syntax, arguments (`$1`, `$@`), `local` variables, return values (status vs `echo`).  
> 🔗 [[Functions]]

> [!note]- **2.7 Arrays** – [[Arrays]]
> 
> Indexed (`arr=(a b c)`), associative (`declare -A`), appending, slicing, looping over keys/values.  
> 🔗 [[Arrays]]

> [!note]- **2.8 Learning Projects** – [[Learning Projects]]
> 
> Five beginner projects with estimated time and concepts covered.  
> 🔗 [[Learning Projects]]
---

## Advanced Techniques

> [!note]- **3.1 File Testing** – [[File Testing]]
> 
> Complete list of operators (`-e`, `-f`, `-d`, `-r`, `-w`, `-x`, `-nt`, `-ot`, `-ef`). Examples for safe file operations.  
> 🔗 [[File Testing]]

> [!note]- **3.2 String Manipulation** – [[String Manipulation]]
> 
> Length, substring, prefix/suffix removal, search/replace, case conversion. All using parameter expansion.  
> 🔗 [[String Manipulation]]

> [!note]- **3.3 Error Handling** – [[Error Handling]]
> 
> Exit codes, `set -euo pipefail`, `trap`, custom error function (`die`).  
> 🔗 [[Error Handling]]

> [!note]- **3.4 Cron Scheduling** – [[Cron Scheduling]]
> 
> Crontab syntax, special strings (`@daily`), environment, logging output, viewing jobs.  
> 🔗 [[Cron Scheduling]]

> [!note]- **3.5 Debugging** – [[Debugging]]
> 
> `set -x`, `PS4`, `bash -n`, `shellcheck`, `trap DEBUG`.  
> 🔗 [[Debugging]]

---

## Projects

> [!note]- **4.1 Backup Script** – [[Backup Script]]
> 
> Full production script: timestamped tarball, retention policy, error checking.  
> 🔗 [[Backup Script]]

> [!note]- **4.2 System Monitor** – [[System Monitor]]
> 
> Real‑time resource monitor with color coding and refresh loop.  
> 🔗 [[System Monitor]]

> [!note]- **4.3 Log Analyzer** – [[Log Analyzer]]
> 
> HTML report generation, top errors, email alert on critical threshold.  
> 🔗 [[Log Analyzer]]

---

## Resources

> [!note]- **Quick Reference** – [[Bash Cheat Sheet]]
> 
> One‑page summary of syntax, operators, and common patterns.  
> 🔗 [[Bash Cheat Sheet]]

> [!note]- **External Links**
> 
> - [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
> - [ShellCheck](https://www.shellcheck.net/)
> - [Bash Hackers Wiki](https://wiki.bash-hackers.org/)
# Why Script?

> [!info] **Purpose**  
> This note explains why you should write Bash scripts instead of typing commands manually. It covers automation, repeatability, conditional logic, and typical use cases.

---

## Table of Contents

- [[#Manual vs Scripted – A Concrete Example]]
- [[#Benefits of Scripting]]
- [[#When to Script (and When Not To)]]
- [[#Real‑World Use Cases]]
- [[#Scripting vs Programming]]
- [[#Return on Investment]]
- [[#Next Steps]]

---

## Manual vs Scripted – A Concrete Example

Imagine you need to **organize your Downloads folder** every week:

**Manual process (15 commands, repeated weekly):**
```bash
cd ~/Downloads
mkdir -p pdfs images docs
mv *.pdf pdfs/
mv *.jpg *.png images/
mv *.doc *.docx docs/
zip -r organized_$(date +%Y%m%d).zip pdfs images docs
rm -rf pdfs images docs
echo "Done"
```

**Scripted (write once, then run with one command):**

Create `organize.sh`:
```bash
#!/bin/bash
cd ~/Downloads || exit
mkdir -p pdfs images docs
mv *.pdf pdfs/ 2>/dev/null
mv *.jpg *.png images/ 2>/dev/null
mv *.doc *.docx docs/ 2>/dev/null
zip -r "organized_$(date +%Y%m%d).zip" pdfs images docs
rm -rf pdfs images docs
echo "Done"
```

Now every week: `./organize.sh`
**Savings:** 15 commands → 1 command. Zero typing errors. Consistent results.

## Benefits of Scripting

|Benefit|Explanation|
|---|---|
|**Automation**|Run repetitive tasks without human intervention. Schedule with cron (e.g., backup at 2 AM).|
|**Repeatability**|Same steps, same order, every time. No forgotten commands or typos.|
|**Documentation**|The script itself is executable documentation of your process.|
|**Conditional logic**|"If disk is more than 90% full, send an alert." Scripts can make decisions.|
|**Looping**|Perform the same action on hundreds of files with three lines of code.|
|**Error handling**|Detect failures (e.g., missing source directory) and take corrective action.|
|**Composability**|Combine small Unix tools (`grep`, `awk`, `curl`, `jq`) into powerful pipelines.|
|**Portability**|A well‑written Bash script runs on any Unix‑like system (Linux, macOS, WSL).|
|**Sharing**|Give your script to colleagues; they can run it without retyping commands.|

> [!tip] **First law of scripting**  
> If you have done a task more than once, script it.

---

## When to Script (and When Not To)

### ✅ Good candidates for scripting

- **Backups** – copy important directories, compress, date‑stamp.
    
- **File organization** – sort downloads, rename photos in bulk.
    
- **System monitoring** – check disk space, memory usage, running services.
    
- **Log analysis** – count errors, extract patterns, generate reports.
    
- **Batch processing** – convert all `.png` images to `.jpg`, resize videos.
    
- **Deployment** – build, test, and deploy a web application.
    
- **User management** – create 50 users from a CSV file.
    
- **Data pipeline** – download data → transform → load into database.
    

### ❌ Poor candidates for scripting

- **Complex data processing** (use Python, R, or SQL instead).
    
- **High‑performance numerical computing** (use C, Fortran, or Julia).
    
- **Graphical user interfaces** (Bash can do simple dialogs with `zenity`, but it’s limited).
    
- **Web applications** (use JavaScript/Node, Python/Django, etc.).
    
- **When the task is truly one‑off** – e.g., renaming a single file manually is faster.
    

> [!note] **Rule of thumb**  
> If the task takes more than 5 minutes of manual work or will be repeated more than twice, script it.

## Real‑World Use Cases

Here are concrete examples from different roles:

### System Administrator

- **User onboarding** – create home directories, set permissions, send welcome email.
    
- **Log rotation** – compress old logs, delete logs older than 90 days.
    
- **Backup validation** – verify backup integrity and report failures.
    
- **Security scans** – check for failed login attempts, block suspicious IPs.
    

### Developer

- **Build automation** – compile code, run tests, package artifacts.
    
- **Git hooks** – run linters before commit, format code after pull.
    
- **Environment setup** – install dependencies, configure environment variables.
    
- **Deployment** – upload to server, restart services, rollback on failure.
    

### Data Scientist

- **Data ingestion** – download datasets from APIs (using `curl` or `wget`).
    
- **Preprocessing** – clean CSVs with `awk`, `sed`, and `cut`.
    
- **Pipeline orchestration** – run Python/R scripts in sequence.
    
- **Scheduled reports** – generate and email daily summary.
    

### Normal User

- **Photo organizer** – sort by date taken, rename to `YYYY-MM-DD_HHMMSS.jpg`.
    
- **Music downloader** – batch download playlists from YouTube (with `youtube-dl`).
    
- **Disk cleanup** – remove old cache files, empty trash, show space saved.
    
- **Morning routine** – open all work applications, fetch calendar, show weather.

## Scripting vs Programming

Bash scripting is **programming**, but with constraints:

|Aspect|Bash Scripting|General Programming (Python, C, etc.)|
|---|---|---|
|**Primary purpose**|Gluing system commands together|Building applications from scratch|
|**Data structures**|Strings, arrays (associative arrays in Bash 4+)|Full set (lists, dicts, sets, objects)|
|**Performance**|Slow for heavy computation|Fast (compiled) or moderately fast (Python)|
|**Portability**|High (any Unix‑like system)|Depends on runtime (Python requires interpreter)|
|**Learning curve**|Low for basic automation|Moderate to high|
|**Error handling**|Basic (exit codes, traps)|Advanced (exceptions, try/catch)|

> [!quote] **Bash is glue**  
> "Bash is the duct tape of the Unix world. It's not pretty, but it holds things together."

Use Bash when you need to **orchestrate existing tools**. Use Python, Ruby, or Go when you need **complex logic, data structures, or performance**.

---

## Return on Investment

Investing time to learn Bash scripting pays off quickly.

|Time invested|Benefit|
|---|---|
|1 hour|Automate a daily 5‑minute task → save 30 hours per year.|
|1 day|Write a deployment script used by 10 engineers → save 100+ hours annually.|
|1 week|Build a monitoring framework that catches issues before customers → priceless.|

**Personal example:** A sysadmin wrote a 10‑line script to clean up old logs. That script ran every night for 5 years, saving 2 minutes of manual work per day → **over 60 hours saved**.

> [!success] **The 80/20 rule**  
> 20% of scripting knowledge (variables, loops, conditionals, `grep`, `find`) covers 80% of real‑world automation needs.

---

## Next Steps

You can also explore the [[#Real‑World Use Cases]] section above and pick one that interests you. Try to sketch out a script for that use case.

> [!tip] **Link this note**  
> Add `- [ ] [[Why Script]]` to your [[Bash Scripting]] MOC under "Foundations".

---

**End of note.**  
This is your complete reference for the value of Bash scripting. Return here to remind yourself why you are learning these skills.
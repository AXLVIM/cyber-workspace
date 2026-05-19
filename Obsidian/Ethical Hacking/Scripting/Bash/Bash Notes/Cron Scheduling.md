# Cron Scheduling

> [!info] **Purpose**  
> This note explains how to schedule Bash scripts to run automatically at specified times using cron, the time‑based job scheduler on Unix‑like systems.

---

## Table of Contents

- [[#What is Cron?]]
- [[#Crontab Basics]]
- [[#Cron Syntax]]
- [[#Special Strings]]
- [[#Scheduling Examples]]
- [[#Cron Environment]]
- [[#Redirecting Output]]
- [[#Managing Crontabs]]
- [[#System Cron vs User Cron]]
- [[#Anacron and Other Alternatives]]
- [[#Troubleshooting]]
- [[#Best Practices]]
- [[#Common Mistakes]]
- [[#Next Steps]]

---

## What is Cron?

**Cron** is a daemon (background process) that runs scheduled commands at fixed times, dates, or intervals. It is used for automating repetitive tasks such as:

- Daily backups
- Log rotation
- System monitoring
- Database maintenance
- Sending periodic reports

Each user (including system users) can have their own **crontab** (cron table) – a file that lists commands and their schedules.

---

## Crontab Basics

**Edit your crontab:**
```bash
crontab -e
```

This opens the current user’s crontab in your default editor (usually `vi`, but can be changed with `export EDITOR=nano`).

**List your crontab entries:**
```bash
crontab -l
```

**Remove all scheduled jobs:**
```bash
crontab -r
```

**Edit another user’s crontab (root only):**
```bash
sudo crontab -u username -e
```

---
## Cron Syntax

Each line in a crontab has six fields:
```text
* * * * * command_to_execute
│ │ │ │ │
│ │ │ │ └─── Day of week (0 - 7) (0 or 7 = Sunday, also names: sun, mon, ...)
│ │ │ └───── Month (1 - 12) (or names: jan, feb, ...)
│ │ └─────── Day of month (1 - 31)
│ └───────── Hour (0 - 23)
└─────────── Minute (0 - 59)
```

**Special characters:**

|Character|Meaning|Example|
|---|---|---|
|`*`|Any value (every minute, hour, etc.)|`* * * * *` = every minute|
|`,`|List separator|`1,15,30 * * * *` = at minutes 1, 15, 30|
|`-`|Range|`1-5 * * * *` = minutes 1 through 5|
|`/`|Step|`*/15 * * * *` = every 15 minutes|

---

## Special Strings

These are shortcuts for common schedules:

|String|Equivalent|Meaning|
|---|---|---|
|`@reboot`|(no equivalent)|Run once at system startup|
|`@yearly` or `@annually`|`0 0 1 1 *`|At 00:00 on Jan 1|
|`@monthly`|`0 0 1 * *`|At 00:00 on day 1 of each month|
|`@weekly`|`0 0 * * 0`|At 00:00 on Sunday|
|`@daily` or `@midnight`|`0 0 * * *`|At 00:00 every day|
|`@hourly`|`0 * * * *`|At minute 0 of every hour|

**Example:**
```cron
@daily /home/user/backup.sh
@reboot /home/user/start_service.sh
```

---
## Scheduling Examples

|Schedule|Cron Expression|
|---|---|
|Run every minute|`* * * * *`|
|Run every hour at minute 0|`0 * * * *`|
|Run every day at 2:30 AM|`30 2 * * *`|
|Run every Monday at 5 PM|`0 17 * * 1`|
|Run at 9 AM on weekdays (Mon-Fri)|`0 9 * * 1-5`|
|Run on the 1st of each month at midnight|`0 0 1 * *`|
|Run every 15 minutes|`*/15 * * * *`|
|Run at 2 AM every Sunday|`0 2 * * 0`|
|Run at 10 PM on the last day of the month|`0 22 28-31 * *` (cron does not detect last day easily – better to use a script check)|
|Run every 5 minutes between 9 AM and 5 PM on weekdays|`*/5 9-17 * * 1-5`|

---

## Cron Environment

Cron runs commands with a **minimal environment**, not the same as your interactive shell.

**Default cron environment (typical):**
```bash
HOME=/home/username
LOGNAME=username
PATH=/usr/bin:/bin
SHELL=/bin/sh
```

> [!warning] `PATH` is limited (often only `/usr/bin:/bin`). Always use **absolute paths** to commands and files in cron jobs.

**Incorrect:**
```cron
0 * * * * backup.sh          # backup.sh not found
```

**Correct:**
```cron
0 * * * * /home/user/bin/backup.sh
```

**Or set PATH in the crontab:**
```cron
PATH=/usr/local/bin:/usr/bin:/bin:/home/user/bin
0 * * * * backup.sh
```

**Also set other variables as needed:**
```cron
MAILTO=admin@example.com
SHELL=/bin/bash
```

---
## Redirecting Output

By default, cron sends any output (stdout or stderr) from the job to the user’s local mail. To avoid filling up mail, redirect output.

**Discard all output:**
```cron
0 2 * * * /home/user/backup.sh > /dev/null 2>&1
```

**Append to a log file:**
```cron
0 2 * * * /home/user/backup.sh >> /var/log/backup.log 2>&1
```

**Separate stdout and stderr:**
```cron
0 2 * * * /home/user/backup.sh >> /var/log/backup.log 2>> /var/log/backup.err
```

---
## Managing Crontabs

**Backup your crontab:**
```bash
crontab -l > my_crontab.backup
```

**Restore from backup:**
```bash
crontab my_crontab.backup
```

**Edit with a different editor:**
```bash
export EDITOR=nano
crontab -e
```

**Disable all cron jobs for a user (empty crontab):**
```bash
crontab -r
```

---
## System Cron vs User Cron

- **User crontabs** – `crontab -e` – stored in `/var/spool/cron/crontabs/`. Each user has their own.
    
- **System crontab** – `/etc/crontab` – includes an extra field for the user to run the command as.
    
- **Cron directories** – `/etc/cron.d/`, `/etc/cron.hourly/`, `/etc/cron.daily/`, `/etc/cron.weekly/`, `/etc/cron.monthly/` – scripts placed here are run automatically at those intervals.

**Example system crontab line (`/etc/crontab`):**
```cron
0 2 * * * root /usr/local/bin/backup.sh
```

The extra field (here `root`) specifies the user to execute the command.

---
## Anacron and Other Alternatives

- **Anacron** – Runs scheduled jobs even if the system was powered down at the scheduled time. It runs daily, weekly, monthly (no minute/hour granularity). Often used on laptops and desktops.
    
- **systemd timers** – Modern replacement for cron on systemd‑based Linux distributions. More flexible but more complex.
    
- **at** – Run a command once at a specified time (one‑time scheduling).

**Example `at` usage:**
```bash
echo "backup.sh" | at 02:00 tomorrow
```

---
## Troubleshooting

### Cron job not running

1. **Check syntax** – `crontab -e` may reject malformed lines.
    
2. **Verify PATH** – use absolute paths.
    
3. **Check permissions** – script must be executable (`chmod +x`).
    
4. **Check script dependencies** – does it require environment variables or a specific working directory? Set them in the crontab or inside the script.
    
5. **Look at logs** – cron logs are usually in `/var/log/syslog` or `/var/log/cron`. Look for lines containing `CRON`.


**Example log entry:**
```cron
Apr 13 02:30:01 hostname CRON[12345]: (user) CMD (/home/user/backup.sh)
Apr 13 02:30:02 hostname CRON[12345]: (user) MAIL (mailed 1 byte of output)
```

### Debugging

Redirect output to a file and examine it:
```cron
0 2 * * * /home/user/backup.sh >> /tmp/cron_debug.log 2>&1
```

Capture error messages:
```cron
0 2 * * * /home/user/backup.sh 2>> /tmp/cron_errors.log
```

### Common error messages

|Error|Likely cause|
|---|---|
|`command not found`|Command not in PATH; use absolute path|
|`Permission denied`|Script not executable or wrong ownership|
|`No such file or directory`|Incorrect path to script or files|
|`(CRON) info (No MTA installed)`|Output being sent to mail but no mail server; redirect output to /dev/null|

---

## Best Practices

1. **Use absolute paths** for all commands and files.
    
2. **Set `PATH` at the top of your crontab** to avoid repetition.
    
3. **Redirect output** to log files, not to mail.
    
4. **Test your script manually** before adding to cron.
    
5. **Include error handling** in your script (check exit codes, log failures).
    
6. **Use `flock` or lock files** to prevent overlapping runs for long‑running jobs.
    
7. **Document your crontab** with comments (lines starting with `#`).
    
8. **Backup your crontab** before making large changes.


**Example well‑commented crontab:**
```cron
# Backup database every day at 2 AM
0 2 * * * /usr/local/bin/backup_db.sh >> /var/log/db_backup.log 2>&1

# Check disk usage every hour, send alert if >90%
0 * * * * /usr/local/bin/disk_check.sh

# Reboot tasks
@reboot /home/user/start_services.sh
```

---
## Common Mistakes

|Mistake|Why it fails|Correct|
|---|---|---|
|`./script.sh` in cron|Relative path depends on working directory|Use absolute path: `/home/user/script.sh`|
|Forgetting `#!/bin/bash` in script|May run with `/bin/sh`, causing errors|Add shebang|
|No execute permission|`Permission denied`|`chmod +x script.sh`|
|Redirecting output with single `>` inside cron|Overwrites log each run, losing history|Use `>>` to append|
|Not setting `PATH`|Commands like `mysqldump` not found|Set `PATH` or use absolute paths|
|Assuming cron uses your shell environment|Missing environment variables|Set variables in crontab or script|
|Running a GUI application|No display variable set|Use `export DISPLAY=:0` (rarely works well)|

---

## Next Steps

You can practice by:

- Scheduling a script to write "Hello" to a file every minute (for testing).
    
- Setting up a daily backup cron job.
    
- Using `@reboot` to start a custom service.


> [!tip] **Link this note**  
> Add `- [ ] [[Cron Scheduling]]` to your [[Bash Scripting]] MOC under "Advanced Techniques".

---

**End of note.**  
This is your complete reference for scheduling Bash scripts with cron. Use it to automate periodic tasks reliably.
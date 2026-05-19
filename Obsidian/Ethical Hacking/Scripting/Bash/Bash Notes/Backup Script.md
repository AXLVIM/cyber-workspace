# Backup Script

> [!info] **Purpose**  
> This note provides a complete, production‑ready backup script. It creates timestamped compressed archives of a source directory, deletes backups older than a specified number of days, and includes comprehensive error handling and logging.

---

## Table of Contents

- [[#Overview]]
- [[#The Script]]
- [[#How It Works]]
- [[#Usage]]
- [[#Customization Options]]
- [[#Scheduling with Cron]]
- [[#Testing the Script]]
- [[#Variations]]
- [[#Best Practices]]
- [[#Common Issues]]
- [[#Next Steps]]

---

## Overview

This backup script solves a common need: regularly backing up a directory without filling up disk space with old backups.

**Features:**
- Creates a compressed tarball (`.tar.gz`) with a timestamp in the filename.
- Allows specifying source and destination directories as arguments.
- Automatically creates the destination directory if it does not exist.
- Removes backups older than a configurable number of days (`RETENTION_DAYS`).
- Logs all actions with timestamps.
- Handles errors gracefully (exits with non‑zero code on failure).
- Uses `set -euo pipefail` for robust error detection.

---

## The Script

Save the following as `backup.sh`:

```bash
#!/usr/bin/env bash
# backup.sh – Create timestamped backup of a directory with rotation.
# Usage: ./backup.sh <source_directory> [destination_directory]

set -euo pipefail

# Configuration
RETENTION_DAYS=7
LOG_FILE="${HOME}/backup.log"

# Function: print usage and exit
usage() {
    cat <<EOF
Usage: $0 <source_directory> [destination_directory]

Backup a directory with timestamp and automatic rotation.

Arguments:
  source_directory      Directory to back up (must exist).
  destination_directory Target directory for backups (default: /backups).

Environment variables:
  RETENTION_DAYS        Number of days to keep backups (default: 7).
  LOG_FILE              Path to log file (default: ~/backup.log).

Example:
  $0 /home/user/Documents /mnt/backup
EOF
    exit 1
}

# Function: log message with timestamp
log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*" | tee -a "$LOG_FILE"
}

# Function: error message and exit
die() {
    log "ERROR: $*"
    exit 1
}

# Parse arguments
SOURCE="${1:-}"
DEST="${2:-/backups}"

if [ -z "$SOURCE" ]; then
    usage
fi

# Validate source directory
if [ ! -d "$SOURCE" ]; then
    die "Source directory '$SOURCE' does not exist or is not a directory."
fi

# Create destination if it doesn't exist
if [ ! -d "$DEST" ]; then
    log "Destination '$DEST' does not exist. Creating it."
    mkdir -p "$DEST" || die "Cannot create destination directory '$DEST'."
fi

# Prepare backup filename
TIMESTAMP=$(date +%Y%m%d_%H%M%S)
BASENAME=$(basename "$SOURCE")
BACKUP_NAME="backup_${BASENAME}_${TIMESTAMP}.tar.gz"
BACKUP_PATH="${DEST}/${BACKUP_NAME}"

log "Starting backup of '$SOURCE' to '$BACKUP_PATH'"

# Create the tarball
# -C changes to the parent directory so paths inside tarball are relative.
tar -czf "$BACKUP_PATH" -C "$(dirname "$SOURCE")" "$BASENAME"

if [ $? -eq 0 ]; then
    SIZE=$(du -h "$BACKUP_PATH" | cut -f1)
    log "Backup successful: $BACKUP_PATH (size $SIZE)"
else
    die "tar command failed. Backup aborted."
fi

# Delete backups older than RETENTION_DAYS
log "Removing backups older than $RETENTION_DAYS days from '$DEST'"
find "$DEST" -name "backup_${BASENAME}_*.tar.gz" -type f -mtime +$RETENTION_DAYS -delete

# Count how many were deleted (optional)
DELETED=$(find "$DEST" -name "backup_${BASENAME}_*.tar.gz" -type f -mtime +$RETENTION_DAYS -print | wc -l)
if [ "$DELETED" -gt 0 ]; then
    log "Deleted $DELETED old backup(s)."
else
    log "No old backups to delete."
fi

log "Backup process completed successfully."
exit 0
```

---

## How It Works

1. **Argument parsing** – The script expects at least one argument (source directory). The second argument (destination) defaults to `/backups`.
    
2. **Validation** – Checks that the source directory exists. Creates the destination if missing.
    
3. **Timestamp** – Uses `date +%Y%m%d_%H%M%S` to create a unique filename (e.g., `backup_Documents_20260413_143022.tar.gz`).
    
4. **Tar creation** – The `-C` flag changes to the parent directory so the tarball contains the folder name, not the full absolute path.
    
5. **Rotation** – `find` locates backups older than `RETENTION_DAYS` (modification time) and deletes them.
    
6. **Logging** – Every important step is logged with a timestamp to both the console and a log file.

---

## Usage

**Basic usage:**
```bash
./backup.sh /home/user/Documents
```

Backup created in `/backups/backup_Documents_20260413_143022.tar.gz`

**Specify destination:**
```bash
./backup.sh /home/user/Documents /mnt/external_drive/backups
```

**Set retention period (override default 7 days):**
```bash
RETENTION_DAYS=30 ./backup.sh /var/www /backups
```

**Custom log file:**
```bash
LOG_FILE=/var/log/mybackup.log ./backup.sh /home/user/Photos
```

**Make executable:**
```bash
chmod +x backup.sh
```

---
## Customization Options

|Variable|Default|Purpose|
|---|---|---|
|`RETENTION_DAYS`|`7`|Number of days to keep backups. Older backups are deleted.|
|`LOG_FILE`|`~/backup.log`|Path where logs are written.|

You can also modify the backup filename pattern by editing the `BACKUP_NAME` variable.

**Example: change naming scheme to include hostname:**
```bash
BACKUP_NAME="backup_${HOSTNAME}_${BASENAME}_${TIMESTAMP}.tar.gz"
```

---
## Scheduling with Cron

To run this backup automatically every day at 2 AM, add a cron job:
```bash
crontab -e
```

Add line:
```cron
0 2 * * * /home/user/bin/backup.sh /home/user/Documents /backups
```

> [!tip] Use absolute paths in cron. The script’s log file will capture output, so you do not need to redirect.

---

## Testing the Script

Before using in production, test with a small directory.

1. **Create a test directory:**
```bash
mkdir -p ~/test_source
echo "test" > ~/test_source/file.txt
```

2. **Run the script:**
```bash
./backup.sh ~/test_source /tmp/backup_test
```

3. **Verify the backup:**
```bash
ls -l /tmp/backup_test
tar -tzf /tmp/backup_test/backup_test_source_*.tar.gz
```

4. **Test retention:**  
   Create an old backup manually (change its modification time):
```bash
touch -t 202001010000 /tmp/backup_test/backup_test_source_old.tar.gz
./backup.sh ~/test_source /tmp/backup_test
```

The old file should be deleted.

---
## Variations

### Incremental Backup (using `rsync`)

Instead of `tar`, use `rsync` for incremental backups (faster for large datasets with few changes).
```bash
BACKUP_DIR="${DEST}/backup_${BASENAME}_${TIMESTAMP}"
rsync -av --delete "$SOURCE/" "$BACKUP_DIR"
ln -sfn "$BACKUP_DIR" "${DEST}/backup_${BASENAME}_latest"
```

### Backup over SSH (remote server)

Use `tar` over SSH:
```bash
tar -czf - -C "$(dirname "$SOURCE")" "$BASENAME" | ssh user@remote "cat > ${DEST}/${BACKUP_NAME}"
```

### Exclude certain files

Add `--exclude` patterns to `tar`:
```bash
tar -czf "$BACKUP_PATH" --exclude="*.tmp" --exclude="cache" -C "$(dirname "$SOURCE")" "$BASENAME"
```

### Compress with parallel gzip (pigz) for speed

Replace `tar -czf` with:
```bash
tar -cf - -C "$(dirname "$SOURCE")" "$BASENAME" | pigz > "$BACKUP_PATH"
```

---
## Best Practices

1. **Always test the script manually** before adding to cron.
    
2. **Store backups on a different device or partition** (e.g., external drive, network share).
    
3. **Monitor disk space** – if backups fill the destination, older deletions may fail.
    
4. **Use `set -euo pipefail`** to catch errors early.
    
5. **Log everything** – you will thank yourself when debugging.
    
6. **Keep the script idempotent** – running it twice should not cause issues.
    
7. **Use absolute paths in cron** to avoid PATH problems.

---

## Common Issues

|Issue|Likely cause|Solution|
|---|---|---|
|`tar: Cannot open: Permission denied`|Source directory not readable|Run with appropriate user or `chmod`|
|`find: missing argument to -mtime`|`RETENTION_DAYS` is empty|Set a default value in script|
|No backups deleted|`mtime` comparison uses modification time, not creation time|That’s correct; if you want creation time, use `-ctime`|
|Backup filename contains spaces|Source directory name has spaces|Script handles this (quoted variables)|
|`tar` excludes dotfiles (`.` files)|Not an issue; `tar` includes all files by default|If you want to exclude dotfiles, use `--exclude='.*'`|

---

## Next Steps

You can also extend the script to:

- Send email alerts on failure.
    
- Encrypt backups with `gpg`.
    
- Upload to cloud storage (e.g., `rclone`).

> [!tip] **Link this note**  
> Add `- [ ] [[Backup Script]]` to your [[Bash Scripting]] MOC under "Projects".

---

**End of note.**  
This is your complete reference for a backup script. Adapt it to your needs and schedule it with cron.
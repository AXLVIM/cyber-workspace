# System Monitor

> [!info] **Purpose**  
> This note provides a real‑time system monitoring script that displays CPU usage, memory usage, disk usage, and top processes. It updates every few seconds and uses color coding to highlight high utilization.

---

## Table of Contents

- [[#Overview]]
- [[#The Script]]
- [[#How It Works]]
- [[#Usage]]
- [[#Customization Options]]
- [[#Running as a Dashboard]]
- [[#Variations]]
- [[#Best Practices]]
- [[#Common Issues]]
- [[#Next Steps]]

---

## Overview

This script creates a live terminal dashboard that shows key system metrics:

- **CPU load** (1‑minute average) and **CPU usage percentage** (user + system).
- **Memory usage** – used, free, and percentage.
- **Swap usage** – if enabled.
- **Disk usage** for the root filesystem (`/`) – configurable.
- **Top 5 processes** by CPU consumption.
- **Timestamp** and **uptime**.

The display refreshes every 3 seconds (configurable) and uses ANSI color codes to show:
- **Green** – normal (< 50% usage)
- **Yellow** – elevated (50‑80%)
- **Red** – critical (> 80%)

---

## The Script

Save the following as `sysmon.sh`:

```bash
#!/usr/bin/env bash
# sysmon.sh – Real‑time system monitor with color coding.
# Press Ctrl+C to exit.

set -euo pipefail

# Configuration
REFRESH_SECONDS=3
ALERT_CPU=80
ALERT_MEM=80
ALERT_DISK=80

# Color codes
RED='\e[31m'
GREEN='\e[32m'
YELLOW='\e[33m'
BLUE='\e[34m'
BOLD='\e[1m'
RESET='\e[0m'

# Function: get CPU usage percentage (user + system)
get_cpu_usage() {
    top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}' | cut -d'%' -f1
}

# Function: get CPU load average (1 minute)
get_load() {
    awk '{print $1}' /proc/loadavg
}

# Function: get memory usage percentage
get_mem_usage() {
    free | awk '/^Mem:/ {printf "%.1f", $3/$2 * 100}'
}

# Function: get swap usage percentage (if any)
get_swap_usage() {
    free | awk '/^Swap:/ {if ($2>0) printf "%.1f", $3/$2 * 100; else print "0"}'
}

# Function: get disk usage percentage for a given mount point (default /)
get_disk_usage() {
    local mount="${1:-/}"
    df "$mount" | awk 'NR==2 {print $5}' | tr -d '%'
}

# Function: print a colored bar
print_bar() {
    local percent=$1
    local width=20
    local filled=$((percent * width / 100))
    local empty=$((width - filled))
    printf "["
    printf "%${filled}s" | tr ' ' '#'
    printf "%${empty}s" | tr ' ' '-'
    printf "]"
}

# Function: choose color based on percentage
get_color() {
    local val=$1
    if (( $(echo "$val >= $ALERT_CPU" | bc -l) )); then
        echo "$RED"
    elif (( $(echo "$val >= 50" | bc -l) )); then
        echo "$YELLOW"
    else
        echo "$GREEN"
    fi
}

# Clear screen and hide cursor on exit
trap 'echo -e "\033[?25h"; exit' INT TERM EXIT
echo -e "\033[?25l"  # hide cursor

# Main loop
while true; do
    # Gather data
    CPU_USAGE=$(get_cpu_usage)
    CPU_LOAD=$(get_load)
    MEM_USAGE=$(get_mem_usage)
    SWAP_USAGE=$(get_swap_usage)
    DISK_USAGE=$(get_disk_usage "/")
    TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')
    UPTIME=$(uptime -p | sed 's/up //')
    
    # Colors
    CPU_COLOR=$(get_color "$CPU_USAGE")
    MEM_COLOR=$(get_color "$MEM_USAGE")
    DISK_COLOR=$(get_color "$DISK_USAGE")
    
    # Clear screen and move cursor to top
    clear
    
    # Header
    echo -e "${BOLD}${BLUE}══════════════════════════════════════════════════════════════${RESET}"
    echo -e "${BOLD}                    SYSTEM MONITOR DASHBOARD${RESET}"
    echo -e "${BOLD}${BLUE}══════════════════════════════════════════════════════════════${RESET}"
    echo -e "Time:     ${BOLD}${TIMESTAMP}${RESET}"
    echo -e "Uptime:   ${BOLD}${UPTIME}${RESET}"
    echo -e "Host:     ${BOLD}$(hostname)${RESET}"
    echo ""
    
    # CPU section
    echo -e "${BOLD}CPU${RESET}"
    echo -e "Load (1m):  ${CPU_LOAD}"
    echo -e "Usage:      ${CPU_COLOR}${CPU_USAGE}%${RESET} $(print_bar "$CPU_USAGE")"
    echo ""
    
    # Memory section
    echo -e "${BOLD}Memory${RESET}"
    free -h | awk '/^Mem:/ {printf "Total: %s, Used: %s, Free: %s, Available: %s\n", $2, $3, $4, $7}'
    echo -e "Usage:      ${MEM_COLOR}${MEM_USAGE}%${RESET} $(print_bar "$MEM_USAGE")"
    echo ""
    
    # Swap section (only if swap exists and is >0)
    if [ "$(free | awk '/^Swap:/ {print $2}')" -gt 0 ]; then
        echo -e "${BOLD}Swap${RESET}"
        free -h | awk '/^Swap:/ {printf "Total: %s, Used: %s, Free: %s\n", $2, $3, $4}'
        echo -e "Usage:      ${SWAP_USAGE}% $(print_bar "$SWAP_USAGE")"
        echo ""
    fi
    
    # Disk section
    echo -e "${BOLD}Disk (/)${RESET}"
    df -h / | awk 'NR==2 {printf "Total: %s, Used: %s, Available: %s\n", $2, $3, $4}'
    echo -e "Usage:      ${DISK_COLOR}${DISK_USAGE}%${RESET} $(print_bar "$DISK_USAGE")"
    echo ""
    
    # Top 5 processes by CPU
    echo -e "${BOLD}Top 5 CPU Processes${RESET}"
    ps aux --sort=-%cpu | head -6 | tail -5 | awk '{printf "%5s%%  %-8s  %s\n", $3, $1, $11}'
    echo ""
    
    # Footer with instructions
    echo -e "${YELLOW}Refreshing every ${REFRESH_SECONDS}s. Press Ctrl+C to exit.${RESET}"
    
    sleep "$REFRESH_SECONDS"
done
```

---
## How It Works

1. **Data collection functions** – Each metric has a dedicated function using standard commands (`top`, `free`, `df`, `ps`, `/proc/loadavg`).
    
2. **Color coding** – `get_color` returns ANSI escape sequences based on thresholds (default: >80% red, >50% yellow, else green).
    
3. **Visual bar** – `print_bar` creates a simple 20‑character progress bar (e.g., `[#######-------------]`).
    
4. **Clear and refresh** – The script clears the screen each iteration, giving a live dashboard effect.
    
5. **Cursor hiding** – Uses `trap` to restore the cursor on exit.
    
6. **Infinite loop** – Runs until interrupted by `Ctrl+C`.

---
## Usage

**Make executable:**
```bash
chmod +x sysmon.sh
```

**Run:**
```bash
./sysmon.sh
```

Press `Ctrl+C` to exit.

**Customize refresh interval (e.g., 5 seconds):**  
Edit the script and change:
```bash
REFRESH_SECONDS=5
```

**Monitor a different disk:**  
Change the mount point in the `get_disk_usage` call:
```bash
DISK_USAGE=$(get_disk_usage "/home")
```

---
## Customization Options

|Variable|Default|Purpose|
|---|---|---|
|`REFRESH_SECONDS`|`3`|How often the display updates (seconds).|
|`ALERT_CPU`|`80`|Threshold for red color (CPU).|
|`ALERT_MEM`|`80`|Threshold for red color (memory).|
|`ALERT_DISK`|`80`|Threshold for red color (disk).|

You can also modify the list of processes shown by changing the `head -6` and `tail -5` values.

**Example: show top 10 processes:**
```bash
ps aux --sort=-%cpu | head -11 | tail -10
```

---
## Running as a Dashboard

### Full‑screen terminal

- Maximize your terminal window.
    
- Adjust font size for better readability.

### Over SSH

The script works over SSH – the color codes are preserved.

### Using `watch` (alternative, less interactive)

If you prefer a simpler approach without a loop, you can use the `watch` command:
```bash
watch -n 3 'top -bn1 | head -20'
```

But the provided script gives a more tailored dashboard.

----
## Variations

### Minimal version (no colors, no bars)

```bash
#!/bin/bash
while true; do
    clear
    date
    uptime
    free -h
    df -h /
    ps aux --sort=-%cpu | head -6
    sleep 3
done
```

### Network monitor addition

Add network traffic stats using `ifstat` or `/proc/net/dev`:

```bash
get_network() {
    rx=$(cat /sys/class/net/eth0/statistics/rx_bytes)
    tx=$(cat /sys/class/net/eth0/statistics/tx_bytes)
    echo "RX: $((rx/1024/1024)) MB, TX: $((tx/1024/1024)) MB"
}
```

### Temperature monitor (requires `sensors`)

```bash
get_temp() {
    sensors | grep "Core 0" | awk '{print $3}'
}
```

### Alert when thresholds are exceeded (using `notify-send` on desktop)

```bash
if (( $(echo "$CPU_USAGE > $ALERT_CPU" | bc -l) )); then
    notify-send "High CPU usage" "CPU at ${CPU_USAGE}%"
fi
```

---
## Best Practices

1. **Run as a normal user** – The script does not require root privileges.
    
2. **Use `bc` for floating point comparisons** – Bash cannot handle decimals natively. The script uses `bc -l`.
    
3. **Hide cursor** – Improves visual cleanliness. The `trap` ensures it is restored.
    
4. **Keep refresh interval reasonable** – 1‑5 seconds is good. Lower than 1 second may consume unnecessary CPU.
    
5. **Test on your system** – Some commands (e.g., `top -bn1` output format) may vary slightly between distributions.

---

## Common Issues

|Issue|Likely cause|Solution|
|---|---|---|
|`bc: command not found`|`bc` not installed|Install it: `sudo apt install bc` (Debian/Ubuntu) or `brew install bc` (macOS)|
|CPU usage always 0%|`top` output format differs|Check `top -bn1 \| grep "Cpu(s)"` output. On some systems, use `top -bn1 \| grep "%Cpu"` and adjust `awk` field.|
|Colors not showing|Terminal does not support ANSI|Use a modern terminal (GNOME Terminal, iTerm2, Windows Terminal, etc.)|
|High CPU usage from the monitor itself|Refresh rate too low (<1s)|Increase `REFRESH_SECONDS` to 3 or more.|
|`free` output differs on macOS|macOS `free` not available|On macOS, use `vm_stat` and `top`. Alternatively, install GNU coreutils.|

**Fix for older `top` (e.g., macOS):**
```bash
get_cpu_usage() {
    top -l 1 | grep "CPU usage" | awk '{print $3}' | tr -d '%'
}
```

---
## Next Steps

You can extend the script to:

- Log metrics to a CSV file for historical analysis.
    
- Send alerts via email or desktop notification.
    
- Monitor multiple remote hosts via SSH.

> [!tip] **Link this note**  
> Add `- [ ] [[System Monitor]]` to your [[Bash Scripting]] MOC under "Projects".

---

**End of note.**  
This is your complete reference for a real‑time system monitor. Use it to keep an eye on system health.
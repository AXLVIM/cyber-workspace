#!/bin/bash

# get_all_info.sh - Collect system info and pack into OS_RESULT.tar

# Ensure running as root
if [[ $EUID -ne 0 ]]; then
   echo "This script must be run as root" >&2
   exit 1
fi

# Function to detect package manager and install cowsay & sl
install_packages() {
    if command -v apt &>/dev/null; then
        apt update && apt install -y cowsay sl
    elif command -v yum &>/dev/null; then
        yum install -y cowsay sl
    elif command -v dnf &>/dev/null; then
        dnf install -y cowsay sl
    elif command -v pacman &>/dev/null; then
        pacman -Sy --noconfirm cowsay sl
    elif command -v zypper &>/dev/null; then
        zypper install -y cowsay sl
    else
        echo "No supported package manager found. Please install cowsay and sl manually." >&2
        exit 1
    fi
}

# Install required packages
echo "Installing cowsay and sl..."
install_packages

# Prepare info file
INFO_FILE="info"
> "$INFO_FILE"  # clear or create empty

# Collect installed packages
echo "=== Installed packages ===" >> "$INFO_FILE"
if command -v dpkg &>/dev/null; then
    dpkg -l >> "$INFO_FILE"
elif command -v rpm &>/dev/null; then
    rpm -qa >> "$INFO_FILE"
elif command -v pacman &>/dev/null; then
    pacman -Q >> "$INFO_FILE"
else
    echo "Package list not available via dpkg/rpm/pacman" >> "$INFO_FILE"
fi

# Collect running processes
echo -e "\n=== Running processes ===" >> "$INFO_FILE"
ps aux >> "$INFO_FILE"

# Collect open ports
echo -e "\n=== Open ports (listening) ===" >> "$INFO_FILE"
if command -v ss &>/dev/null; then
    ss -tuln >> "$INFO_FILE"
elif command -v netstat &>/dev/null; then
    netstat -tuln >> "$INFO_FILE"
else
    echo "Neither ss nor netstat found. Install net-tools or iproute2." >> "$INFO_FILE"
fi

# Kernel version
echo -e "\n=== Kernel version ===" >> "$INFO_FILE"
uname -r >> "$INFO_FILE"

# OS version
echo -e "\n=== OS version ===" >> "$INFO_FILE"
if [ -f /etc/os-release ]; then
    cat /etc/os-release >> "$INFO_FILE"
else
    echo "No /etc/os-release found" >> "$INFO_FILE"
fi

# Create tar archive (no compression, as requested)
tar -cf OS_RESULT.tar "$INFO_FILE"

echo "Done. Info saved in $INFO_FILE and archived as OS_RESULT.tar"

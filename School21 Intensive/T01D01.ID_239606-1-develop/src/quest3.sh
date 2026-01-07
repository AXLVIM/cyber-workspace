i#!/bin/bash
# Quest 3: Fix AI door management module

# Rename folder to match script expectation
mv door_management_fi door_management_files

# Create required directories
mkdir -p door_management_files/door_configuration
mkdir -p door_management_files/door_map
mkdir -p door_management_files/door_logs

# Move files to proper folders if needed
mv door_management_files/*.conf door_management_files/door_configuration/
mv door_management_files/*.log door_management_files/door_logs/
mv door_management_files/door_map_* door_management_files/door_map/

# Make control script executable
chmod +x ai_door_control.sh

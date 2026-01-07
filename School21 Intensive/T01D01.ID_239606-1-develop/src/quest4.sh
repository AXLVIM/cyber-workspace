#!/bin/bash
# Quest 4: Stop the AI door control module

# Kill the running module
kill 334890

# Verify it is stopped
ps aux | grep ai_door_control.sh

#!/bin/bash

# Task 2 script — Linux setup (run as root)

# 1. Create user 'user' and group 'default_users' with default permissions
groupadd default_users
useradd -g default_users user

# 2. Create group 'secret_users' and users secret_agent, secret_spy, secret_boss in it
groupadd secret_users
useradd -g secret_users secret_agent
useradd -g secret_users secret_spy
useradd -g secret_users secret_boss

# 3. Users of secret_users group can access each other's home directories, others cannot
#    (Set group ownership to secret_users and give group read/execute permissions)
chgrp secret_users /home/secret_agent /home/secret_spy /home/secret_boss
chmod 750 /home/secret_agent /home/secret_spy /home/secret_boss

# 4. Make /var accessible to any users and any groups
chmod 777 /var

# 5. Install apache2 and check its service status
apt update
apt install -y apache2
systemctl status apache2

# 6. Users of default_users group can run all sudo commands without password
echo "%default_users ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

echo "Setup complete."

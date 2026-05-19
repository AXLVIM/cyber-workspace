# 🧭 Core Navigation Map

Welcome to my central security workspace. This monorepo serves as my integrated laboratory environment, curriculum tracker, and engineering notebook. 

---

## 🏫 School 21 Projects
Practical infrastructure labs, network design blueprints, and traffic analysis.
* **[Networking Basics - Part 1](./School21/CbS1_Networking_basics_Part_1)** → Core IP layout and GNS3 environments.
* **[Networking Basics - Part 2](./School21/CbS2_Networking_basics_Part_2)** → Infrastructure verification (NTP, DNS, DHCP, and Static Routing).
* **[Networking Basics - Part 3](./School21/CbS3_Networking_basics_Part_3)** → Advanced topologies (**HSRP** redundancy, dynamic **OSPF**, and **VLAN Trunking**).
* **[Networking Basics - Part 4](./School21/CbS4_Networking_basics_Part_4)** → Wireshark packet capture (**PCAP**) analysis and python scripts.
* **[Linux Basics](./School21/CbS5_Linux_basics)** → Shell scripting (`sh`), iptables firewalls, cron jobs, and SSH hardening.
* **[Windows Basics](./School21/CbS6_Windows_basics)** → Local security policies and PowerShell (`.ps1`) administration.
* **[Crypto Intro](./School21/CbS7_Crypto_intro)** → Python decoding tools, XOR logic, and foundational ciphers.

## 📓 Obsidian Security Vault
Live conceptual notes and strategic roadmaps synced directly from my knowledge base.
* **[Red Team Roadmap](./Obsidian/Cybersecurity/Red%20Team)** → Active Directory exploitation guides and learning pathways.
* **[Network Enumeration](./Obsidian/Ethical%20Hacking/Network%20Enumeration/Nmap)** → Native tool definitions and `nmap` syntax breakdowns.
* **[Bash Scripting Notebook](./Obsidian/Ethical%20Hacking/Scripting/Bash/Bash%20Notes)** → Syntax, loops, error handling, and automation structures.

## 🎯 Wargames & CTFs
Hands-on capture-the-flag environments, tool tracking, and platform notes.
* **[OverTheWire](./CTF/overthewire)** → Privilege escalation logs for **Bandit** and web exploitation for **Natas**.
* **[Hack The Box](./HTB)** → Structured learning tracking for CJCA and CPTS modules.
* **[OSINT Sandbox](./OSINT)** → Multi-tool tracking including `sherlock`, `shodan`, and `theHarvester`.


# 📂 Repository Architecture

Below is the macro-level structural blueprint of this monorepo, detailing the specific security domains and infrastructure engineering modules contained within.

### 🎯 CTF/ — Capture The Flag & Wargames
Interactive security labs focused on privilege escalation and vulnerability exploitation.
* **overthewire/** — Linux terminal mastery and server-side exploitation.
  * `bandit/` — Linux privilege escalation, permissions, and bash filters.
  * `natas/` — Web application security vulnerabilities and server analysis.
* **Root-Me/** — Real-world network administration and automation capture scenarios.

### 📦 HTB/ — Hack The Box Academy Tracks
Structured professional training pathways logging practical system penetration testing.
* **CJCA/** — Certified Junior Cybersecurity Analyst hands-on exercises.
* **CPTS/** — Certified Penetration Testing Specialist core infrastructure testing blocks.

### 🧠 Obsidian/ — Centralized Security Vault
A live Markdown knowledge base mapping theory to practical tradecraft, synced directly from my second brain.
* **Cybersecurity/** — Strategic planning and defensive architectures.
  * `Blue Team/` — Defensive engineering, log analysis, and infrastructure monitoring.
  * `Red Team/` — Active Directory (AD) mechanics and operational roadmaps.
* **Ethical Hacking/** — Hands-on execution frameworks and command syntax sheets.
  * `Network Enumeration/` — Active footprinting blueprints and raw Nmap syntax.
  * `Reverse Engineering/` — Netcat socket connections, listeners, and payload mechanics.
  * `Scripting/` — Multi-tiered automation modules covering advanced Bash arrays and custom python tools.
* **School21/** — Conceptual study logs and academic project breakdowns.

### 🔍 OSINT/ — Open-Source Intelligence Sandbox
Environment tracking and validation for public data collection utilities.
* **sherlock/** — Username footprinting across federated social web networks.
* **shodan/** — Internet-wide device discovery and perimeter scanning techniques.
* **theHarvester/** — Target domain gathering, including public email lists and subdomains.

### ⚡ School21/ — Core Engineering Portfolio
Production infrastructure configurations, custom scripts, and deep packet forensics.
>[!info] Reminder
>All the project files are located in /src folder

* **CbS1_Networking_basics_Part_1/** — IPv4 subnets, network topologies, and base GNS3 environment routing.
* **CbS2_Networking_basics_Part_2/** — Core services implementation (NTP, DNS, DHCP) and static routing paths.
* **CbS3_Networking_basics_Part_3/** — High-availability gateways (HSRP), dynamic routing protocols (OSPF), and VLAN Trunking (IEEE 802.1q).
* **CbS4_Networking_basics_Part_4/** — Advanced Wireshark PCAP digital forensics, packet parsing, and custom traffic filters.
* **CbS5_Linux_basics/** — System hardening, custom cron automation scripts, and iptables stateful firewall rules.
* **CbS6_Windows_basics/** — Windows security policies and administrative PowerShell (.ps1) scripting.
* **CbS7_Crypto_intro/** — Cryptographic logic implementations, XOR manipulation, and standalone Python decoder scripts.

### 📜 Repository Assets
System files managing repo documentation and usage parameters.
* **LICENSE** — Distribution terms.
* **NAVIGATION.md** — Clickable file routing index.
* **README.md** — Primary workspace landing profile.

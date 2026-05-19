## 🧠 Before you start (Week 0)
- [ ] VS Code + Git + Python 3.11+
- [ ] Create GitHub repo for all scripts
- [ ] Install: VirtualBox, Kali Linux (VM), Windows 10/11 (VM), Ubuntu Server (VM)

---

## 🔹 Months 1–2: IT & Python Core
**Goal:** Solid networking, OS, and Python fundamentals

- [ ] **Week 1** – TCP/IP, subnetting, OSI model | `print()`, variables, data types, f-strings
- [ ] **Week 2** – DNS, HTTP/HTTPS, FTP, ports | `if/else`, `for`/`while`, `break/continue`
- [ ] **Week 3** – Linux basics (files, permissions, grep, awk) | functions, `sys.argv`, error handling
- [ ] **Week 4** – Linux scripting (bash, cron) | file I/O (`open`, `read`, `write`, `json`)
- [ ] **Week 5** – Windows basics (cmd, PS, registry) | `os` module (walk, env, path)
- [ ] **Week 6** – Windows user & permissions (SID, ACLs) | `subprocess` (run commands, capture output)
- [ ] **Week 7** – Virtual networking + lab setup | `try/except/finally`, custom exceptions
- [ ] **Week 8** – **Mini‑project:** multi‑threaded port scanner | `socket`, `threading`, `argparse`

✅ **Outcome:** Script basic network tools, navigate Linux/Windows confidently.

---

## 🔹 Months 3–4: Security Foundations + Python Automation

- [ ] **Week 9** – Nmap (scan types, scripts) | port + service banner grabber
- [ ] **Week 10** – Wireshark & tcpdump | `scapy` – craft & sniff packets
- [ ] **Week 11** – Burp Suite (proxy, repeater) | `requests` – automate form login
- [ ] **Week 12** – OSINT (Google Dorking, theHarvester) | `BeautifulSoup` + `re` – scrape emails/links
- [ ] **Week 13** – Shodan & Censys | Shodan API – query & parse results
- [ ] **Week 14** – Bash automation (`xargs`, `parallel`) | `subprocess` + `asyncio`
- [ ] **Week 15** – PowerShell (event logs, AMSI bypass basics) | `json`, `csv` – parse Windows event logs
- [ ] **Week 16** – **Review:** convert bash script to Python CLI tool | `click` / `argparse`, logging

✅ **Outcome:** Junior Security Analyst – automate recon and analysis.

---

## 🔹 Months 5–6: Web & Network Pentesting

- [ ] **Week 17** – SQLi (error‑based, blind) | boolean‑based blind tester
- [ ] **Week 18** – SQLi advanced (sqlmap) | manual SQLite injection script
- [ ] **Week 19** – XSS (reflected, stored, DOM) | XSS payload generator + encoder
- [ ] **Week 20** – Command injection & LFI/RFI | command injection fuzzer
- [ ] **Week 21** – SMB, FTP, SSH misconfigs | `socket` + `paramiko` – SSH brute forcer
- [ ] **Week 22** – Metasploit (auxiliary, exploit, post) | `msfrpc` – automate an exploit
- [ ] **Week 23** – Linux privilege escalation (SUID, cron, sudo) | SUID checker + enumeration script
- [ ] **Week 24** – Windows privilege escalation (AlwaysInstallElevated, Unquoted paths) | registry + service permission enumerator

✅ **Outcome:** Junior Pentester – find & exploit basic web/network flaws.

---

## 🔹 Months 7–8: Active Directory & Post-Exploitation

- [ ] **Week 25** – AD basics (domain, forest, LDAP) | `ldap3` – query users, groups, computers
- [ ] **Week 26** – BloodHound (SharpHound, custom queries) | `neo4j` – automate data extraction
- [ ] **Week 27** – Kerberos attacks (AS-REP, Kerberoasting) | `impacket` – request & save tickets
- [ ] **Week 28** – Pass‑the‑Hash / Overpass‑the‑Hash | `impacket` – PTH script (like `wmiexec.py`)
- [ ] **Week 29** – Mimikatz (logonpasswords, sekurlsa) | parse LSASS minidump (basic)
- [ ] **Week 30** – C2 basics (custom agent, beaconing) | simple reverse shell with encryption
- [ ] **Week 31** – EDR bypass (API unhooking, AMSI patching) | Python obfuscator (string substitution, base64)
- [ ] **Week 32** – **Review week** – chain 3 AD attacks | full attack simulation script (Kerberoast → PTH → RDP)

✅ **Outcome:** Junior Red Team Operator – move through a Windows domain.

---

## 🔹 Months 9–12: Red Team Tradecraft (MITRE ATT&CK)

- [ ] **Week 33** – Recon (T1595) + OSINT automation | recon orchestrator (Shodan + Censys + DNS)
- [ ] **Week 34** – Initial Access (T1566 – phishing) | send phishing email template via SMTP
- [ ] **Week 35** – Persistence (T1547 – startup folder, registry) | add to Windows startup + scheduled task
- [ ] **Week 36** – Lateral Movement (T1021 – WinRM, SMB, RDP) | Pass‑the‑Hash RDP launcher
- [ ] **Week 37** – C2 (T1071 – DNS, HTTPS) | DNS tunneling client (encode data in subdomains)
- [ ] **Week 38** – Exfiltration (T1041 – HTTP, DNS) | covert file splitter & reassembler over DNS
- [ ] **Week 39** – Defense Evasion (T1070 – clear logs) | log wiper (Windows Event Log + bash history)
- [ ] **Week 40** – **Mini Red Team exercise** (recon → exfil in lab) | single script chaining 5+ MITRE techniques
- [ ] **Week 41** – Purple Team – simulate & detect | detection lab (audit logs + Sigma rules)
- [ ] **Week 42** – Reporting & metrics | generate PDF report (ReportLab) with findings
- [ ] **Week 43** – OSCP / CRTO prep (pivoting, tunneling) | Python SOCKS proxy for pivoting
- [ ] **Week 44** – HackTheBox – adapt Python exploits | rewrite a public exploit to bypass a filter
- [ ] **Week 45** – TryHackMe – Red Team track | enumeration automation for THM labs
- [ ] **Week 46** – Real‑world scenario (AD + phishing + exfil) | attack simulation + full documentation
- [ ] **Week 47** – Team‑based attack (relay attacks) | NTLM relay script wrapper for `ntlmrelayx`
- [ ] **Week 48** – **Final assessment** – breach a lab domain in 6 hours | self‑graded rubric + recorded demo

✅ **Outcome:** Junior Red Team Operator – ready for CRTO, internal assessments, or purple team roles.

---

## 📌 Tips for Obsidian
- Use `Ctrl+Shift+F` to search for weeks or Python topics.
- Create sub‑notes for each week (e.g., `Week 1 – Networking + Python`) and link them using `[[Week 1]]`.
- Turn each checkbox into a task – Obsidian will track progress.

## 🚀 After finishing
- Take CRTO exam (Certified Red Team Operator).
- Build a portfolio of your 48 weekly scripts on GitHub.
- Apply for Junior Red Team or Purple Team roles.
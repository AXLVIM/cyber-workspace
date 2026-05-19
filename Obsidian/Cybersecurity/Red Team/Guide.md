# Complete Guide: From Beginner to Senior Penetration Tester

> Based on real conversations – includes roadmap, certification strategy, HTB Academy plan, and portfolio building.

## Table of Contents
1. [Stage 1: Absolute Beginner (0–6 months)](#stage-1-absolute-beginner-0-6-months)
2. [Stage 2: Junior Pen Tester (6–18 months)](#stage-2-junior-pen-tester-6-18-months)
3. [Stage 3: Mid-Level Pen Tester (1.5–3 years)](#stage-3-mid-level-pen-tester-15-3-years)
4. [Stage 4: Senior Pen Tester (3–6 years)](#stage-4-senior-pen-tester-3-6-years)
5. [Stage 5: Beyond Senior](#stage-5-beyond-senior)
6. [12‑Month Accelerated Plan](#12-month-accelerated-plan)
7. [HTB Student Subscription: What You Get & How to Use It](#htb-student-subscription-what-you-get--how-to-use-it)
8. [Certification Deep Dive: CJCA vs. CPTS vs. Security+](#certification-deep-dive-cjca-vs-cpts-vs-security)
9. [Your Two‑Stage Certification Strategy](#your-two-stage-certification-strategy)
10. [Portfolio Building – Step by Step](#portfolio-building--step-by-step)
11. [4‑Week Sprint to Your First Portfolio Pieces](#4-week-sprint-to-your-first-portfolio-pieces)
12. [Essential Mindset & Resources](#essential-mindset--resources)

---

## Stage 1: Absolute Beginner (0–6 months)
**Goal:** Understand computers, networks, and security mindset.

- **Networking basics:** OSI model, TCP/UDP, DNS, HTTP/HTTPS, Wireshark
- **Linux fundamentals:** filesystem, permissions, bash, processes (use Kali/Ubuntu VM)
- **Windows basics:** Active Directory structure, users, groups, registry, PowerShell
- **Security mindset:** CIA triad, threat types, hashing vs. encryption
- **Practice:** OverTheWire Bandit, VulnHub basic machines

---

## Stage 2: Junior Pen Tester (6–18 months)
**Goal:** Run tools, find common vulns, write basic reports.

- **Recon:** theHarvester, Shodan, Nmap, masscan
- **Web:** OWASP Top 10, Burp Suite, SQLmap, PortSwigger Academy
- **Network:** Metasploit, manual exploits (EternalBlue), John/Hashcat
- **Scripting:** Python for automation (requests, socket, subprocess)
- **Report writing:** Executive summary + methodology + findings + reproduction + remediation
- **Certs (optional):** Security+, eJPT
- **Labs:** TryHackMe (Pre Security & Complete Beginner paths), HTB Starting Point

---

## Stage 3: Mid-Level Pen Tester (1.5–3 years)
**Goal:** Manual exploitation, chaining vulns, client communication.

- **Advanced web:** SSTI, SSRF, deserialization, race conditions
- **Active Directory:** Kerberoasting, Golden Ticket, BloodHound, CrackMapExec
- **Cloud (AWS/Azure):** IAM misconfigs, metadata service attacks
- **Evasion:** bypass WAF/AV, living-off-the-land
- **Privilege escalation:** manual + WinPEAS/LinPEAS
- **Soft skills:** lead small scoping calls, write actionable remediation
- **Certs:** OSCP (gold standard) or PNPT
- **Labs:** HTB (Medium/Hard), Proving Grounds, custom AD lab

---

## Stage 4: Senior Pen Tester (3–6 years)
**Goal:** Lead complex engagements, mentor, strategic risk assessment.

- **Chaining across hybrid environments (cloud + on‑prem + OT)**
- **Zero‑day research:** fuzzing, binary analysis (optional but valuable)
- **Custom tool development:** scanners, C2 frameworks
- **Red teaming:** evasion, persistence, stealth (if you choose that path)
- **Non‑technical:** scope negotiation, risk-based findings (business impact > CVSS)
- **Mentoring juniors** and building team processes
- **Certs (optional):** OSEP, CRTO, GPEN

---

## Stage 5: Beyond Senior
- Build a pentesting practice (hiring, QA, methodology)
- Purple teaming – help blue teams improve detection
- Public research – CVEs, conference talks, open-source tools
- Transition to consulting management or deep specialization (mobile, cloud, ICS)

---

## 12‑Month Accelerated Plan

| Month | Focus |
|-------|-------|
| 1–2 | Linux, networking (Bandit, TryHackMe Pre-Security) |
| 3–4 | Web attacks (PortSwigger + Burp Suite) |
| 5–6 | Network pentesting (Metasploit, Nmap, HTB Starting Point) |
| 7–9 | Active Directory + eJPT or OSCP prep |
| 10–12 | Take OSCP (or PNPT), build report portfolio, apply to junior roles |

---

## HTB Student Subscription: What You Get & How to Use It

You purchased the **$8/month student subscription for HTB Academy**, not the main HTB Labs platform.

### What you have access to:
- **Full HTB Academy** – structured courses, modules, and guided paths.
- **CPTS (Certified Penetration Testing Specialist) path** – all modules included.
- **CBBH (Certified Bug Bounty Hunter) path** – also included.

### How to use it effectively:
1. **Start with the CPTS path** – it begins from zero and builds systematically.
2. **Do not jump directly into live HTB machines** – complete the foundational modules first (intro to pentesting, networking, Linux/Windows basics).
3. **Supplement with free resources** – HackTricks, PayloadsAllTheThings.
4. **After each module, practice on**:
   - Free **Starting Point** machines on main HTB platform
   - Retired machines (if you later buy VIP access) – but not required at first

### Important:
- **Active machines** on the main HTB platform are **free** to hack.
- Your student subscription does **not** include VIP access to retired machines – you don't need it early on.

---

## Certification Deep Dive: CJCA vs. CPTS vs. Security+

| Certification | Focus | Type | Best for |
|---------------|-------|------|-----------|
| **CJCA** (HTB) | Junior analyst – offensive & defensive basics | Practical, hands-on | First job as a SOC analyst or junior pentester |
| **CPTS** (HTB) | Full penetration testing specialist | Practical, exam after CPTS path | Proving advanced hands-on ability (after some experience) |
| **Security+** (CompTIA) | Broad cybersecurity fundamentals | Theory, multiple choice | HR filter (especially US gov & DoD 8570) |

**Your plan is excellent:** Start with **CJCA** to get your first job, then later pursue **CPTS** (or CBBH) to deepen offensive skills.

> *"No cert alone gets you a job – but skills + certs + portfolio do."*

---

## Your Two‑Stage Certification Strategy

### Stage 1 – Junior Role Ready (CJCA)
- **Why:** Hands-on, purple team (offense + defense) – shows you can work in a team.
- **How:** Complete the CJCA learning path on HTB Academy (included in your student sub).
- **Complement:** Build a portfolio (see below) and learn to write reports.

### Stage 2 – Pentesting Specialist (CPTS)
- **Why:** Proves you can hack complex environments independently.
- **When:** After 6–12 months in a junior role or after completing CJCA and HTB modules.
- **Bonus:** CPTS is more respected in technical circles than many theory certs.

> Optional: If you see many job postings asking for **Security+**, add it later – the knowledge from CJCA/CPTS will make it easy.

---

## Portfolio Building – Step by Step

### 1. Create a Hub (free)
- GitHub repository (`cyber-journey` or `pentest-notes`)
- Or Notion / Hashnode blog

### 2. Document every lab like a real pentest report
Each entry should include:

- **Target name & difficulty**
- **Objective**
- **Methodology** (step‑by‑step commands + reasoning)
- **Findings** (vulnerabilities discovered)
- **Proof** (screenshot of flag or shell)
- **Remediation** (how to fix the issue)

### 3. Build three core portfolio projects

| Project | What it shows |
|---------|----------------|
| **Home lab setup** (Active Directory) | Initiative, Windows/AD fundamentals |
| **Walkthrough of a free HTB machine** (e.g., Meow) | Enumeration, exploitation, reporting |
| **Small automation script** (10‑line Python/bash port scanner) | Basic coding & tooling |

### 4. Get feedback
- Share reports in **HTB Discord** or **InfoSec Prep Discord**.
- Iterate based on feedback.

---

## 4‑Week Sprint to Your First Portfolio Pieces

| Week | Tasks |
|------|-------|
| **Week 1** | Set up GitHub/Notion. Complete *Getting Started* module on HTB Academy. Write your first report. |
| **Week 2** | Build a free Active Directory lab (follow *GoAD* project). Write a blog post on how you built it. |
| **Week 3** | Hack and write up **two free HTB machines** from the Starting Point tier (e.g., Meow, Fawn). |
| **Week 4** | Write a tiny automation script (Python or bash). Publish it on GitHub with a README. |

After 4 weeks you will have **4‑5 portfolio pieces** – more than most junior applicants.

---

## Essential Mindset & Resources

### Mindset tips
- **Document everything** – commands, failures, wins.
- **Stay legal** – only test systems you own or have written permission for.
- **Expect rabbit holes** – 90% of pentesting is debugging and enumeration.
- **Community matters** – follow @alh4zr3d, @thedarkside, /r/netsec.

### Free / cheap resources
- **TryHackMe** (free rooms: Pre-Security, Complete Beginner)
- **PortSwigger Web Security Academy** (free)
- **HackTricks** (free wiki)
- **The Cyber Mentor** (YouTube)

### Books
- *The Web Application Hacker’s Handbook* – Stuttard
- *Linux Basics for Hackers* – OccupyTheWeb
- *Penetration Testing: A Hands-On Introduction to Hacking* – Georgia Weidman

---

## Final Words

You already have:
- ✅ The right student subscription (HTB Academy)
- ✅ A clear two‑stage cert plan (CJCA → CPTS)
- ✅ A portfolio strategy and a 4‑week sprint

Now it’s about **execution**. Start with Week 1, stay consistent, and you will be ready to apply for junior roles sooner than you think.

Good luck, and hack the planet! 🚀
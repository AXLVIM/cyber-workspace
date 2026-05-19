# Red Team Operator Roadmap – 1 yil (Enhanced)

> Python bilan toʻliq qurollangan, zamonaviy va amaliy reja.  
> Har bir boʻlimda “Nazariya + Amaliyot + Python Tool” tamoyili asosida qurilgan.

---

## 🔹 1–2-oy: IT asoslari (8 hafta + 1 hafta mustahkamlash)

**Maqsad:** tizim va tarmoqni chuqur tushunish + Python poydevorini qoʻyish.

- **1-hafta:** TCP/IP, OSI modeli, subnetting. Python: `print`, oʻzgaruvchilar, maʼlumot turlari.
- **2-hafta:** DNS, HTTP/HTTPS, FTP protokollari. Python: shart operatorlari (`if`), sikllar (`for`, `while`).
- **3-hafta:** Linux asoslari (terminal, fayl tizimi, ruxsatlar `chmod`, `chown`). Python: funksiyalar.
- **4-hafta:** Linux scripting (bash, cron, systemd). Python: fayl I/O, kontekst menejerlari.
- **5-hafta:** Windows asoslari (cmd, PowerShell, xizmatlar, Registry). Python: `os` moduli.
- **6-hafta:** Windows foydalanuvchi boshqaruvi (AD tushunchasi, lokal hisoblar). Python: `subprocess` moduli.
- **7-hafta:** VirtualBox/VMware’da lab qurish (Kali, Windows, Metasploitable). Python: `try/except` xatoliklar bilan ishlash.
- **8-hafta:** Tarmoq topologiyalari, xususiy va ommaviy IP. Python: `socket` moduliga kirish.

- **🔄 Mustahkamlash haftasi (8+):**
  - Barcha Python mavzularini takrorlash
  - Lab muhitini test qilish
  - Lugʻat (`dict`), roʻyxat (`list`) va JSON bilan ishlashni qoʻshimcha oʻrganish

🎯 **Natija:** Ishlaydigan lab + mustahkam Python asosi.

---

## 🔹 3–4-oy: Kiberxavfsizlik poydevori (8 hafta + 1 hafta mustahkamlash)

**Maqsad:** asosiy xavfsizlik vositalari va Python’ni skanerlash/OSINT ga qoʻllash.

- **9-hafta:** Nmap port skanerlash. Python: oddiy TCP port skaner.
- **10-hafta:** Nmap NSE scriptlari bilan tanishish. Python: xizmat banner grabber.
- **11-hafta:** Wireshark, trafik tahlili asoslari. Python: scapy bilan packet sniffer.
- **12-hafta:** Burp Suite, HTTP soʻrov/response. Python: `requests` yordamida GET/POST.
- **13-hafta:** OSINT (Google Dorking, shodan.io). Python: BeautifulSoup bilan web scraping.
- **14-hafta:** Shodan API bilan ishlash. Python: Shodan soʻrovlarini avtomatlashtirish.
- **15-hafta:** Linux avtomatlashtirish (bash skriptlar). Python: `subprocess` orqali buyruq bajarish.
- **16-hafta:** PowerShell scripting asoslari. Python: JSON va maʼlumotlar seriyalash.

- **🔄 Mustahkamlash haftasi (16+):**
  - Yozilgan tool’larni qayta koʻrib chiqish va takomillashtirish
  - Oddiy skaner va OSINT loyihasini GitHub’ga joylash

🎯 **Natija:** Junior xavfsizlikchi + OSINT + oʻz tool’larini yoza oladi.

---

## 🔹 5–6-oy: Pentesting asoslari (8 hafta + 1 hafta mustahkamlash)

**Maqsad:** web va tarmoq zaifliklarini aniqlash va ekspluatatsiya qilish.

- **17-hafta:** OWASP Top 10 (SQLi, XSS). Python: oddiy SQL injection tester (GET asosida).
- **18-hafta:** sqlmap bilan SQLi ekspluatatsiyasi. Python: SQLite injection script.
- **19-hafta:** XSS amaliyoti (reflected, stored). Python: kontekstga mos XSS payload generator.
- **20-hafta:** Komanda injection (RCE) zaifliklari. Python: command injection exploit.
- **21-hafta:** SMB, FTP hujumlari. Python: SMB brute force tool (Hydra emulyatsiyasi).
- **22-hafta:** Metasploit Framework asoslari (`msfconsole`, modullar). Python: Metasploit RPC API.
- **23-hafta:** Linux privilege escalation (SUID, sudo, cron). Python: SUID fayl topuvchi.
- **24-hafta:** Windows privilege escalation (Registry, xizmat ruxsatlari). Python: Registry enum tool.

- **🔄 Mustahkamlash haftasi (24+):**
  - Bir nechta HTB/TryHackMe mashinalarini yechish
  - OWASP zaifliklarini qayta koʻrib chiqish

🎯 **Natija:** Pentester Junior + Python eksploit yozish koʻnikmasi.

---

## 🔹 7–8-oy: Advanced pentesting & AD (8 hafta)

**Maqsad:** Active Directory va post-exploitation texnikalari.

- **25-hafta:** Active Directory asoslari (domen, DC, OU, GP). Python: LDAP query tool.
- **26-hafta:** BloodHound/SharpHound AD xaritalash. Python: Neo4j bilan bogʻlanish.
- **27-hafta:** Kerberoasting hujumi. Python: ticket dumper (Impacket).
- **28-hafta:** Pass-the-Hash va Pass-the-Ticket. Python: Impacket kutubxonasidan foydalanish.
- **29-hafta:** Mimikatz va LSASS xotira dumperi. Python: dump fayl parser.
- **30-hafta:** Zamonaviy C2 asoslari (Covenant/Mythic talabaga mos). Python: oddiy HTTP C2 agent prototipi.
- **31-hafta:** EDR/XDR va AMSI tushunchasi, erta bypass. Python: string obfuscation script.
- **32-hafta:** Custom payload yozish. Python: oddiy reverse shell (TCP/HTTP).

🎯 **Natija:** AD hujumlari va post-ekspluatatsiya asoslari oʻzlashtirilgan.

---

## 🔹 9–12-oy: Red Team uslubi va real simulyatsiyalar (16 hafta)

**Maqsad:** MITRE ATT&CK boʻyicha yashirin, maqsadga yoʻnaltirilgan hujum zanjirlarini mashq qilish.

### 🔸 33–36-hafta: Boshlangʻich bosqich taktikasi
- **33-hafta:** MITRE ATT&CK strukturasini tushunish. Python: taktika-texnika mapper.
- **34-hafta:** Initial Access (vishing/phishing kontekstida). Python: oddiy phishing e-mail yuboruvchi (SMTP).
- **35-hafta:** Persistence mexanizmlari (startup, WMI event). Python: startup persistence skripti.
- **36-hafta:** Lateral Movement (RDP, SMB, WinRM). Python: Pass-the-Hash orqali lateral movement.

### 🔸 37–40-hafta: C2 va maʼlumot chiqarish
- **37-hafta:** C2 kanallari (DNS/HTTPS tunneling). Python: DNS tunnel (oddiy klient-server).
- **38-hafta:** Data exfiltration texnikalari. Python: yashirin fayl uzatish (ICMP/DNS).
- **39-hafta:** Defense evasion (log tozalash, timestamp oʻzgartirish). Python: log wiper.
- **40-hafta:** Mini Red Team senariy (ichki labda zanjirli hujum): Python: eksploit chaining.

### 🔸 41–44-hafta: Operatsion xavfsizlik va hisobot
- **41-hafta:** Purple Team mashqi – Blue Team bilan hamkorlik simulyatsiyasi. Python: hujum simulyatsiya skripti.
- **42-hafta:** Operatsion xavfsizlik (OPSEC) va footprint minimallashtirish. Python: clean-up skript.
- **43-hafta:** Hujum natijalarini professional hujjatlashtirish. Python: avtomatik report generator (JSON → docx).
- **44-hafta:** Red Team infratuzilmasi asoslari (redirectors, CDN, domen fronting). Python: oddiy redirector tekshiruvi.

### 🔸 45–48-hafta: Real simulyatsiya va sertifikatsiyaga tayyorgarlik
- **45-hafta:** OSCP/CRTO uchun maxsus tayyorgarlik. Python: avtomatlashtirilgan ekspluat skriptlarini qayta koʻrib chiqish.
- **46-hafta:** Real-world ssenariy (AD + phishing + exfil zanjiri). Python: toʻliq zanjir avtomatizatsiyasi.
- **47-hafta:** Team-based hujum mashqlari (rol taqsimoti va xabar almashish). Python: jamoa UIdan foydalanish.
- **48-hafta:** Yakuniy sinov: oʻz skill set’ini baholash, Github portfolio va rezyumeni yangilash.

🎯 **Yakuniy natija:** Mustaqil, Python bilan qurollangan, zamonaviy Red Team Operator.
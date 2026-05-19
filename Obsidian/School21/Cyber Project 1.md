

## About Project

# Networking Basics. Part 1 — "First Experience"
 This project includes an analysis of networking basics, the OSI/TCP/IP model using the GNS3 environment as a working example, as well as the study of IP, ARP, and ICMP protocols.

---
>💡 If this is your first project, fill out this [form](http://opros.so/kAnXy).
>💡 [Click here](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624) to share your feedback on this project with us. It is anonymous and will help our team make learning better. We recommend completing the survey immediately after finishing the project.
## Table of Contents
1. [Chapter I](#chapter-i) \
   1.1. [Project Recommendations](#project-recommendations)
2. [Chapter II](#chapter-ii) \
   2.1. [Computer Network](#computer-network)
3. [Chapter III](#chapter-iii) \
   3.1. [Task 1. Address Calculation](#task-1-address-calculation) \
   3.2. [Task 2. Getting to Know GNS3](#task-2-getting-to-know-gns3) \
   3.3. [Task 3. Multicast Requests](#task-3-multicast-requests) \
   3.4. [Task 4. ARP](#task-4-arp)
### Introduction
>Ulrich's day had been going badly since morning: the local mages had blown up the laboratory, he had injured his shoulder during the last training session, and now it was preventing him from sleeping. On top of that, his mentor forced him to clean up the mess in the ancient runes, which Ulrich had only heard about from senior students.
>
>The young monster hunter got dressed, took his sword, and quickly ran to the dining hall for breakfast. The students called it "The Tower" because the local cooks addressed the students as "sir" and "madam." After breakfast, already in a better mood, Ulrich entered the corner office that everyone thought was vacant. On the table lay a pile of stones with scratched symbols, hinting that he wouldn't be lucky enough to sleep in his own bed today.
## Chapter I
---
### Project Recommendations
How to study at "School 21":
- Throughout the course, you will independently find information. Use all available means of searching for information, for example, Google and GigaChat. Be careful about information sources: check, think, analyze, compare.
- Peer-to-peer learning (P2P) is a process where students exchange knowledge and experience, acting simultaneously as both teachers and students. This approach allows you to learn not only from the instructor but also from each other, which contributes to a deeper understanding of the material.
- Don't hesitate to ask for help: those around you are fellow students who are also going through this path for the first time. Don't be afraid to respond to requests for help. Your experience is valuable and useful, feel free to share it with other participants.
- Don't cheat, and if you use help, always understand completely the why, how, and what for. Otherwise, your learning will be meaningless.
- If you're stuck on something and it seems like you've tried everything, but you still don't know where to go — just take a break! Believe me, this advice has helped many cybersecurity experts in their work. Get some fresh air, reboot your mind, and perhaps next time the right solution will finally come to you!
- Not only the result of learning is important, but also the process itself. You need not just to solve a problem, but to understand HOW to solve it.
- On the path to mastery in the field of cybersecurity, you have the opportunity to be part of a supportive and inspiring community of "School 21" for Cybersecurity. Join the [RocketChat](https://rocketchat-student.21-school.ru/channel/cybersec_21) to receive fresh announcements from the community, and also join [Telegram](https://t.me/+r5wufz8L3mUzOGUy) for communication.
How to work with the project:
- Before completing the project, you need to clone it from GitLab into a repository with the same name.
- All code files must be created in the `src` folder of the cloned repository.
- After cloning the project, you need to create a `develop` branch and do your work in it. Then push the `develop` branch to GitLab as well.
- There should be no other files in your directory other than those specified in the tasks.
Disclaimer:
- For the purpose of gamifying learning, the project is presented in a story format so that you have the opportunity to take a break from complex tasks and tons of theory on Google. If you find the invented story talentless and boring, you can point this out in the feedback so the author can cry over their writing skills. You can also skip the introduction in each task and focus only on the substantive part.
## Chapter II
---
### Computer Network
A computer network is a collection of devices and systems that are logically or physically connected to each other and interact. Network devices include servers, computers, phones, etc. The size of such networks can vary — from a home network of two or three devices to an enterprise network or the entire internet. Networks are a vast topic, and it is recommended to begin the tasks of this project by independently studying the basic theory for each of them (in this project, you will need at least knowledge of the first four layers of the OSI model), and then proceed to the laboratory work.

The best option for getting acquainted with the basics of networks is study guides for the Cisco CCNA certification, as the information in them is well-structured and covers all the main necessary topics. If you have a sufficient level of English, I recommend studying the theory using video format CCNA materials (for example, you can look at CBT Nuggets or similar). You can also work with the printed/electronic version of the Cisco CCNA study guide.

*Note:* The translated Russian version of the CCNA study guide is categorically not recommended due to errors and inaccuracies in the translation.

Additionally, you can check out the Habr blog ["Networks for the Little Ones"](https://habr.com/ru/articles/447080/). To continue studying materials on networks and their security after completing this course, we recommend paying attention to the following materials:

* Implementing and Operating Cisco Security Core Technologies;
* Cisco Enterprise Network Core Technologies.
## Chapter III
---
### Task 1. Address Calculation
To solve this task, you need knowledge in the following topics: IP addresses, binary number system, subnetting, subnet mask.
>To begin with, Ulrich decided to recount the runes. What a mistake! The poor fellow didn't know that runes are counted in the binary number system. He started putting runes aside one by one and counting them out loud. Ulrich realized the trick after he had put aside 2 runes but had already counted 10. To sort the stones into piles, he would have to use a new number system...

**IP (Internet Protocol) is a network layer protocol. Yes, it was using this that any internet troublemaker could be traced back 10 years ago. However, its main task is to implement traffic transmission between different IP networks. This happens thanks to IP addresses. These addresses are similar to your registered address. The analogy is completely direct: there are no absolutely identical addresses on the entire planet, but several different cities may have the same house numbers, street names, and apartment numbers (for example, Moscow, Sovetskaya St., bldg. 12 or St. Petersburg, Sovetskaya St., bldg. 12)**.

[Article on the topic](https://habr.com/ru/articles/134892/).

To solidify your understanding of what CIDR notation and network addressing are, you need to solve several practical tasks given below:

1. Calculate the binary notation for the addresses:
    * 178.101.89.7
    * 201.57.153.161
2. Imagine that you need to allocate subnets for various segments of organization N: technological (3 machines), server (16 machines), and user (32 machines).
3. Which subnet masks need to be allocated for each segment? Provide a justification for your answer.
Write the solutions and justifications in a text file named `ip-1`.
### Task 2. Getting to Know GNS3
To solve this task, you need knowledge in the following topics: GNS3, importing a Cisco image into GNS3.
**Important:** When completing tasks, do not forget to save device configurations.
>Ulrich experienced all the pain of disappointment after he had sorted all the runes into piles but had not prepared any storage for them. Although he did not remember the exact instructions from his mentor, it was obvious that the stones should be sorted and carefully placed in some containers. There were no nice shelves or cabinets in the office. At first this upset him, but then he realized that the mentor had deliberately not prepared any containers for him in order to teach the young student to think unconventionally. Therefore, Ulrich decided to emulate shelves and cabinets using magic mushroom bags.

**To prepare the virtual environment in which you will perform the laboratory work for this and the next three blocks, you need to set up and prepare the GNS3 test environment and learn the principles of working in it. GNS3 is a virtual environment that, similar to virtual machines, allows you to emulate the operation of network equipment. To prepare the GNS3 virtual environment, you need to install it (if it hasn't been done previously), create a project, and import Cisco IOS images.**

Download Cisco IOS images from this [link](https://blog.netskills.ru/2011/12/ios-gns3-ios-for-gns3.html), IOS 3745.

[Article on the topic](https://docs.gns3.com/docs/getting-started/your-first-gns3-topology).
After installation, set permissions for dumpcap:
```
sudo chmod +x /usr/bin/dumpcap
```

If you encounter difficulties, the following links will help you:
- [Github GNS3](https://github.com/GNS3/gns3-gui).

**Important:** Do not install GNS as a systemd service, as some versions have a bug with project creation with such an installation.
[Installation instructions](https://docs.gns3.com/docs/getting-started/installation/linux).
As an answer, upload the GNS3 project containing the imported Cisco 3745 device to the repository.
### Task 3. Multicast Requests
To solve this task, you need knowledge in the following topics: broadcast, multicast, ICMP, Wireshark.
>When all the runes were sorted into bags, only one small thing remained: to carry hundreds of kilograms of stones to the basement so that the office wouldn't suddenly turn into a warehouse. Unfortunately, his aching shoulder wouldn't let Ulrich lift even one bag.
>
>"This is bad," thought Ulrich and then said to himself: "I'll have to call for help."
>
>So that the students passing by the office would hear him, the failed mover shouted at the top of his lungs, addressing everyone at once:
>"Help! Anybody!"

**Broadcast is a broadcast address used to transmit traffic to all nodes on the network (implemented at both L2 and L3). This is a sort of shout into a loudspeaker that will only be heard by those who are on the same network as you. For this "shout," a separate address is always allocated in each network, usually the last one (for example, for network 192.168.1.0/24, it is 192.168.1.255).**

**Multicast is an address used to transmit traffic to a group of nodes on the network. Essentially, a stripped-down version of broadcast.**

**ICMP (Internet Control Message Protocol) is a protocol used to transmit error information during traffic transmission. A popular way to test network reachability is `ping` — a command that is present in every operating system and allows you to send ICMP echo requests. They contain no useful information themselves; they are a kind of "poke" at the device.**

[Article on the topic](https://habr.com/ru/articles/217585/).

Your task:
- Create a project.
- Add two network devices to it (use the Cisco 3745 image), connect them, configure their network interfaces.
- Start the emulation and capture a packet trace by sending an ICMP request to a multicast IP address.
- Using Wireshark\*, study the resulting packet trace file, paying attention to the fields reflecting L2, L3, and ICMP information.
- Answer the question: what destination MAC address is the ICMP request sent to? Write the answer in a text file named `multicast`.
- Save the resulting captured packet trace file as a .pcap file named `multicast`.

\* Wireshark is software for traffic analysis. It allows you to both record traffic and view already recorded traffic. It is used quite often, especially when you need to manually see what is happening on the network. The interface is quite busy, but the [official documentation](https://wiki.wireshark.org/) will help you figure it out.

As the final answer, upload the `multicast.pcap` file and the `multicast` text file with the answer to the question to the repository.

*Hint:* For a device to respond to requests sent to a multicast address, you need to add the interface to a multicast group.

If you encounter difficulties, you can use this [Help](https://docs.gns3.com/docs/getting-started/your-first-cisco-topology).

**Tips:**
* Do not assign "complicated" IP addresses to network interfaces, it's better to use simple ones, for example, 10.10.10.0/24.
* Enter "?" in the command line interface to display help.
* Use the TAB key to complete command entry.

Additionally, after completing this task, we recommend that you independently study what a Broadcast Storm is.
### Task 4. ARP
To solve this task, you need knowledge in the following topics: ARP, Layer 2 of the OSI model, Wireshark, GNS3.

>Help did not arrive immediately. But what help! A charming girl looked into the office and looked at Ulrich questioningly. Then at the bags of stones. Then at Ulrich again. Disappointment first flickered in her eyes, then curiosity, anger, and finally, a desire to run away. But altruism prevailed. Together they managed in a few hours, carrying all the bags to the basement. All that remained was to place each bag into a specific cell with a certain number, so that they would be easier to find later.

**ARP (Address Resolution Protocol) allows you to determine a MAC address based on a known IP address. Every device has an ARP table, which is a "diary" — it records IP addresses with their associated MAC addresses.**

[Article on the topic](https://habr.com/ru/articles/138043/).

We continue to master basic network protocols using ARP as an example. We will also analyze it in the format of traffic analysis between two network nodes in our GNS3 project.

Your task:

- Start packet trace capture, run the `ping` command from one of the nodes to the IP address of the neighboring device. Ensure that after this, the corresponding ARP entry is present in the ARP table.
- In Wireshark, familiarize yourself with the contents of ARP and ICMP packets.
- What MAC address is the request sent to in the first ARP packet? What is this address called? Write the answers in a text file named `arp`.
- Pay attention to which MAC address the response packet originates from. Save the resulting Wireshark .pcap file named `arp`.

In total, upload three files to the repository: the `gns3` project, the `arp.pcap` file, and the `arp` text file.

Additionally, when completing this task, we recommend that you independently study what Gratuitous ARP is.


## Solution

# Task 1: Address Calculation
## 1. Binary Notation for the Given IP Addresses

For start you have to know what is [IP](https://en.wikipedia.org/wiki/IP_address) address and [subnetting](https://www.geeksforgeeks.org/computer-networks/introduction-to-subnetting/).There is so many ways to turn IP into binary. But let's start with this -> [binary code](https://learningnetwork.cisco.com/s/blogs/a0D3i000002SKMwEAO/network-binary-math-explained).
### a) 178.101.89.7
Calculation process:
- 178 = 128 + 32 + 16 + 2 = 10110010
- 101 = 64 + 32 + 4 + 1 = 01100101
- 89  = 64 + 16 + 8 + 1 = 01011001
- 7   = 4 + 2 + 1 = 00000111
**Result:** `10110010.01100101.01011001.00000111`
---
### b) 201.57.153.161
Calculation process:
- 201 = 128 + 64 + 8 + 1 = 11001001
- 57  = 32 + 16 + 8 + 1 = 00111001
- 153 = 128 + 16 + 8 + 1 = 10011001
- 161 = 128 + 32 + 1 = 10100001
**Result:** `11001001.00111001.10011001.10100001`
---
## 2. Subnet Allocation for Organization N
Requirements:
- Technological segment: 3 machines
- Server segment: 16 machines
- User segment: 32 machines
### Subnet Masks Calculation
| Segment | Required hosts | Formula 2^n - 2 ≥ hosts | n (host bits) | Subnet mask (CIDR) | Subnet mask (decimal) |
|---------|----------------|--------------------------|---------------|--------------------|------------------------|
| Technological | 3 | 2^3 - 2 = 6 ≥ 3 | 3 | /29 | 255.255.255.248 |
| Server | 16 | 2^5 - 2 = 30 ≥ 16 | 5 | /27 | 255.255.255.224 |
| User | 32 | 2^6 - 2 = 62 ≥ 32 | 6 | /26 | 255.255.255.192 |
### Justification
#### For the technological segment (3 machines):
- The minimum number of host bits n must satisfy 2^n - 2 ≥ number of hosts
- For n = 3: 2^3 - 2 = 6 ≥ 3 ✓ (n = 2 gives only 2 hosts, which is insufficient)
- Therefore: network prefix = 32 - 3 = 29 bits → subnet mask /29 (255.255.255.248)
- This subnet provides 6 usable IP addresses, enough for 3 machines with room for growth
#### For the server segment (16 machines):
- For n = 5: 2^5 - 2 = 30 ≥ 16 ✓ (n = 4 gives only 14 hosts, insufficient)
- Therefore: network prefix = 32 - 5 = 27 bits → subnet mask /27 (255.255.255.224)
- This subnet provides 30 usable IP addresses, sufficient for 16 servers
#### For the user segment (32 machines):
- For n = 6: 2^6 - 2 = 62 ≥ 32 ✓ (n = 5 gives only 30 hosts, insufficient)
- Therefore: network prefix = 32 - 6 = 26 bits → subnet mask /26 (255.255.255.192)
- This subnet provides 62 usable IP addresses, enough for 32 user machines
### Important Note
- The formula 2^n - 2 subtracts the network address and broadcast address, which cannot be assigned to hosts
- All allocated masks are from the same major network (e.g., 192.168.1.0/24), allowing efficient use of address space without overlap
- The chosen masks respect the hierarchy: /26 (user) > /27 (server) > /29 (technological), preventing address conflicts

# Task 2: Getting to Know GNS3
## What Is GNS3?

>GNS3 (Graphical Network Simulator-3) is a free, open-source software tool used to design, configure, and test complex computer networks without needing physical hardware.

Unlike basic simulators that only mimic commands, GNS3 actually runs real operating system images from devices like Cisco, Juniper, and MikroTik. This means the virtual routers and switches behave exactly like their physical counterparts.

It is widely used by network engineers and students for two main purposes: to prepare for professional certifications like the CCNA or CCNP, and to safely test network changes before deploying them in the real world. Because it runs real software, GNS3 is more powerful than entry-level simulators but requires you to provide your own device images.

## Answer
The GNS3 project with the imported Cisco 3745 device has been uploaded to the repository.

## Installation
These instructions are for Ubuntu and all distributions based on it (like Linux Mint).

```bash
# This command adds the official GNS3 software repository to your Ubuntu system, allowing you to install and update GNS3 directly using apt.

sudo add-apt-repository ppa:gns3/ppa
```

```bash
# This command refreshes your system's list of available software packages and their versions.

sudo apt update
```

```bash
# This command installs the GNS3 graphical interface and the backend server on your Ubuntu system.

sudo apt install gns3-gui gns3-server
```
## Project Contents

- GNS3 project file (`.gns3`)
- Cisco 3745 device configured and saved
- Project folder: `gns3/` (or as named)
## Completion Confirmation
- [ ] GNS3 installed (not as systemd service)
- [ ] `sudo chmod +x /usr/bin/dumpcap` executed
- [ ] Cisco IOS 3745 image imported
- [ ] New project created
- [ ] Cisco 3745 added to workspace
- [ ] Device configuration saved
- [ ] Project saved and exported
## Note
The project file itself is the required answer. This document serves as supporting documentation

# Task 3. Multicast Requests

For this task we need 2 Cisco3745 routers. Connect both to f0/0

```bash
# Giving an IP address for R1:

R1> enable
R1# configure terminal
R1(config)# interface f0/0
R1(config-if)# ip address 10.10.10.1 255.255.255.0
R1(config-if)# no shutdown
R1(config-if)# exit
R1(config)# exit
R1# write memory
```

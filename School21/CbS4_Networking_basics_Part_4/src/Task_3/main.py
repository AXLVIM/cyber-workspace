#!/usr/bin/env python3
"""
Script to send TCP message using Scapy to 127.0.0.1:12345
"""

from scapy.all import *

# Configuration
TARGET_IP = "127.0.0.1"
TARGET_PORT = 12345
SOURCE_PORT = 12346

# Message to send
message = "Dear Steel Cat! This is no attack, it's my humster Pinkie you should track"
message_bytes = message.encode('utf-8')

print("=== Scapy TCP Message Sender ===\n")
print(f"Target: {TARGET_IP}:{TARGET_PORT}")
print(f"Message: {message}\n")

# Create IP layer
ip = IP(dst=TARGET_IP)

# Send SYN packet
print("[1] Sending SYN...")
syn = TCP(sport=SOURCE_PORT, dport=TARGET_PORT, flags="S", seq=1000)
syn_response = sr1(ip/syn, timeout=2, verbose=False)

if syn_response and syn_response.haslayer(TCP):
    tcp = syn_response.getlayer(TCP)
    if tcp.flags & 0x12:  # SYN-ACK
        print("[2] SYN-ACK received!")
        
        # Send ACK + Data
        ack_num = tcp.seq + 1
        data_packet = ip / TCP(sport=SOURCE_PORT, dport=TARGET_PORT, 
                                flags="PA", seq=1000, ack=ack_num) / message_bytes
        send(data_packet, verbose=False)
        print("[3] Data sent!")
        
        # Send FIN
        fin_packet = ip / TCP(sport=SOURCE_PORT, dport=TARGET_PORT,
                               flags="FA", seq=1000 + len(message_bytes), ack=ack_num)
        send(fin_packet, verbose=False)
        print("[4] Connection closed.")
        
        print("\n[+] Message sent successfully!")
    else:
        print(f"[-] Unexpected response flags: {tcp.flags}")
else:
    print("[-] No SYN-ACK response. Sending packet anyway...")
    # Send packet without handshake
    packet = ip / TCP(sport=SOURCE_PORT, dport=TARGET_PORT, flags="S") / message_bytes
    send(packet, verbose=False)
    print("[+] Packet sent!")

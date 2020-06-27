#!/bin/bash
#clear
echo ''
echo 'Installing firewall'
echo '==================='
#Allow loopback device (internal communication)
sudo iptables -A INPUT -i lo -j ACCEPT
sudo iptables -A OUTPUT -o lo -j ACCEPT

#Allow all local traffic.
sudo iptables -A INPUT -s 192.168.1.0/24 -j ACCEPT
sudo iptables -A OUTPUT -d 192.168.1.0/24 -j ACCEPT

#Allow VPN establishment
sudo iptables -A OUTPUT -p udp --dport 1194 -j ACCEPT
sudo iptables -A INPUT -p udp --sport 1194 -j ACCEPT
sudo iptables -A OUTPUT -p tcp --dport 443 -j ACCEPT
sudo iptables -A INPUT -p tcp --sport 443 -j ACCEPT

#Accept all TUN connections (tun = VPN tunnel)
sudo iptables -A OUTPUT -o tun+ -j ACCEPT
sudo iptables -A INPUT -i tun+ -j ACCEPT

#Set default policies to drop all communication unless specifically allowed
sudo iptables -P INPUT DROP
sudo iptables -P OUTPUT DROP
sudo iptables -P FORWARD DROP

#Save the configuration
#sudo iptables-save > /etc/iptables/rules.v4
#sudo ip6tables-save > /etc/iptables/rules.v6

#Setup persistance
#sudo apt install iptables-persistent netfilter-persistent

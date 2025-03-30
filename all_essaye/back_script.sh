Sudo IPTABLES -F

IPTABLES -A INPUT -m iprange --src-range 192.168.1.1-192.168.1.50
IPTABLES -A INPUT -m iprange --src-range 192.168.1.51-192.168.1.100
IPTABLES -A INPUT -m iprange --src-range 192.168.1.101-192.168.1.150
IPTABLES -A INPUT -m iprange --src-range 192.168.1.151-192.168.1.200
IPTABLES -A INPUT -m iprange --src-range 192.168.1.201-192.168.1.250


IPTABLES -A OUTPUT -m iprange --src-range 192.168.1.1-192.168.1.50
IPTABLES -A OUTPUT -m iprange --src-range 192.168.1.51-192.168.1.100
IPTABLES -A OUTPUT -m iprange --src-range 192.168.1.101-192.168.1.150
IPTABLES -A OUTPUT -m iprange --src-range 192.168.1.151-192.168.1.200
IPTABLES -A OUTPUT -m iprange --src-range 192.168.1.201-192.168.1.250

IPTABLES -A FORWARD -m iprange --src-range 192.168.1.1-192.168.1.50
IPTABLES -A FORWARD -m iprange --src-range 192.168.1.51-192.168.1.100
IPTABLES -A FORWARD -m iprange --src-range 192.168.1.101-192.168.1.150
IPTABLES -A FORWARD -m iprange --src-range 192.168.1.151-192.168.1.200
IPTABLES -A FORWARD -m iprange --src-range 192.168.1.201-192.168.1.250



# Advanced Network Topics

## Project Structure
- PDFs regarding the two stages
### src:
- source code  
### obj:
- objects

---

## XDP

### Loading Objects
\$ sudo ip link set \<eth\> xdpgeneric obj \<obj\> sec \<sec\>

### Checking Objects
\$ sudo xdp-loader status

### Unloading Objects
\$ sudo ip link set \<eth\> xdpgeneric off

---

## Veth

### Add (Create) Namespaces
\$ sudo ip netns add \<netspace\>

### List (Show) Namespaces
\$ sudo ip netns list

### Add (Create) Veth Pair
\$ sudo ip link add \<veth\> type veth peer name \<veth\>

### Show Interfaces
\$ ip link show

### Attach Veth to Namespace
\$ sudo ip link set \<veth\> netns \<netspace\>

### Set Veth Up
\$ sudo ip netns exec \<netspace\> ip link set dev \<veth\> up

### Add IPV4 to Veth
\$ sudo ip netns exec \<netspace\> ip addr add \<addr\>/\<mask\> dev \<veth\>

\$ sudo ip netns exec \<netspace\> ip link set dev \<veth\> up

### Terminal
\$ sudo ip netns exec \<netspace\> bash

### Run tcpdump
tcpdump -i \<eth\> icmp
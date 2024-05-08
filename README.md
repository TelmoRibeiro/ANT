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

### Add Namespaces:
\$ sudo ip netns add \<netspace\>

### List Namespaces:
\$ sudo ip netns list

### Add Veth Pair:
\$ sudo ip link add \<veth\> type veth peer name \<veth\>

### Show Interfaces:
\$ ip link show

### Veth <-> Namespace:
\$ sudo ip link set \<veth\> netns \<netspace\>

### Veth Up:
\$ sudo ip netns exec \<netspace\> ip link set dev \<veth\> up

### Inspect:
\$ sudo ip netns exec \<netspace\> ip a

### Add IPV4:
\$ sudo ip netns exec \<netspace\> ip addr add \<addr\>/\<mask\> dev \<veth\>

\$ sudo ip netns exec \<netspace\> ip link set dev \<veth\> up

### Terminal:
\$ sudo ip netns exec \<netspace\> bash

### tcpdump:
\$ sudo ip netns exec \<netspace\> tcpdump -i \<veth\> icmp
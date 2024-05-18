# Advanced Network Topics

## XDP

### Building Objects
\$ clang -O2 -g -Wall -target bpf -c \<prog\> -o \<obj\>

### Loading Objects
\$ sudo ip link set \<eth\> xdpgeneric obj \<obj\> sec \<sec\>

or

\$ sudo xdp-loader load -m \<mode\> -s \<sec\> \<eth\> \<obj\>

### Checking Objects
\$ sudo xdp-loader status

### Unloading Objects
\$ sudo ip link set \<eth\> xdpgeneric off

or

\$ sudo xdp-loader unload -a \<eth\>

---

## Veth

### Add (Create) Namespaces
\$ sudo ip netns add \<ns\>

### Add (Create) Veth Pair
\$ sudo ip link add \<eth\> type veth peer name \<eth\>

### Attach Veth to Namespace
\$ sudo ip link set \<eth\> netns \<ns\>

### Add IPV4 to Veth
\$ sudo ip netns exec \<ns\> ip addr add \<addr\>/\<mask\> dev \<eth\>

### Set Veth Up
\$ sudo ip netns exec \<ns\> ip link set dev \<eth\> up

### Run Terminal
\$ sudo ip netns exec \<ns\> bash

---

## Bench

### List Channels
\$ sudo ethtool -l \<eth\>

### Set Channels
\s sudo ethtool -L \<eth\> tx \<number\> rx \<number\>

### List Flags
\s sudo ethtool -k \<eth\>

### Set GRO On
\$ sudo ethtool -K \<eth\> gro on


---

## SET-VETH

### How to Run set-veth.sh
\$ sudo ./set-veths \<ns\> \<eth\> \<eth\> \<addr\> \<addr\> 
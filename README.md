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
\$ sudo ip netns add \<netspace\>

### Add (Create) Veth Pair
\$ sudo ip link add \<veth\> type veth peer name \<veth\>

### Attach Veth to Namespace
\$ sudo ip link set \<veth\> netns \<netspace\>

### Add IPV4 to Veth
\$ sudo ip netns exec \<netspace\> ip addr add \<addr\>/\<mask\> dev \<veth\>

### Set Veth Up
\$ sudo ip netns exec \<netspace\> ip link set dev \<veth\> up

### Run Terminal
\$ sudo ip netns exec \<netspace\> bash
# Advanced Network Topics
## Project Structure
- PDFs regarding the two stages
### src:
- source code  
### obj:
- to load objects

## How To Load Objects:
\$ sudo ip link set \<eth\> xdpgeneric obj \<obj\> sec \<sec\>

## How To Check Objects:
\$ sudo xdp-loader status

## How To Unload Objects:
\$ sudo ip link set \<eth\> xdpgeneric off

## How To Create Virtual Interfaces:
\$ sudo ip link add \<eth\> type dummy

\$ sudo ip addr add \<ipv4\>/\<prefix\> dev \<eth\>

\$ sudo ip -6 addr add \<ipv6\>/\<prefix\> dev \<eth\>

\$ sudo ip link set dev \<eth\> up

\$ sudo ip addr show

## How To Delete Virtual Interfaces:
\$ sudo ip link delete \<eth\>

\$ sudo ip addr show
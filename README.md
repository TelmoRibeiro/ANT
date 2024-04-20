# Advanced Network Topics
## Project Structure
### Reports:
- PDFs regarding the two stages
### src:
- source code  
### obj:
- to load objects

## How To Load (ubuntu):
\$ sudo ip link set \<eth\> xdpgeneric obj \<obj\> sec \<sec\>

## How To Check (xdp-loader needed):
\$ sudo xdp-loader status

## How To Unload (ubuntu):
\$ sudo ip link set \<eth\> xdpgeneric off

## How To Create Virtual Interfaces (ubuntu):
\$ sudo ip link add \<name\> type dummy

\$ sudo ip addr add \<ipv4\>/\<prefix\> dev \<name\>

\$ sudo ip -6 addr add \<ipv6\>/\<prefix\> dev \<name\>

\$ sudo ip link set dev \<name\> up

\$ sudo ip addr show

## How To Delete Virtual Interfaces (ubuntu):
\$ sudo ip link delete \<name\>

\$ sudo ip addr show
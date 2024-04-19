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
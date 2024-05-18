#!/bin/bash

# orignal  by: Rogerio Rocha
# modified by: Telmo Ribeiro

# usage: sudo ./set-veths <ns> <vethA> <vethB> <addrA> <addrB>

ip netns add "${1}"

ip link add "${2}" type veth peer name "${3}"

ip link set "${3}" netns "${1}"

ip addr add "${4}/24" dev "${2}"

ip netns exec "${1}" ip addr add "${5}/24" dev "${3}"

ip link set dev "${2}" up

ip netns exec "${1}" ip link set dev "${3}" up

ip netns exec "${1}" ip link set dev lo up
#!/bin/bash

ip netns add "${2}"

ip link add "${1}r" type veth peer name "${1}v"

ip link set "${1}v" netns "${2}"

ip link set dev "${1}r" up

ip netns exec "${2}" ip link set dev "${1}v" up

ip netns exec "${2}" ip link set dev lo up

ip addr add "192.168.${3}.0/24" dev "${1}r"

ip netns exec "${2}" ip addr add "192.168.${3}.1/24" dev "${1}v"


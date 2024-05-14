#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <linux/ip.h>

#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/if.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/in6.h>
#include <linux/types.h>

#define IPV4_ADDR "192.168.2.0" // change me //
#define IPV4_ETH_INDEX 2        // change me //

/* @ telmo -
    TESTED:
    NOT TESTED:
        - Generic Mode
        - Native
        - Offloaded
    
    IDEA:
        - load xdp_redirect into an interface
        - it will redirect the IPV6 packets to interface with index X
*/

/*
struct bpf_map_def SEC("maps") MY_MAP = {
    .type = BPF_MAP_TYPE_DEVMAP_HASH,
    .key_size   = sizeof(__u32),
    .value_size = sizeof(int),
    .max_entries = 1024, 
};
*/
SEC("xdp_redirect_ipv4")
int xdp_redirect_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        return XDP_PASS;
    }
    if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
        return XDP_DROP;
    }
    struct iphdr* iph = data + sizeof(struct ethhdr);
    __u64 old_daddr = iph->daddr;
    iph->daddr = inet_addr(IPV4_ADDR);
    iph->check = bpf_csum_replace(x,y,old_daddr,iph->daddr);
    // bpf_redirect_map(&MY_MAP,IPV4_ETH_INDEX,0);
    return XDP_TX;
}
char _license[] SEC("license") = "GPL";
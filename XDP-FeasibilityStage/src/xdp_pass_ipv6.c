#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>

SEC("xdp_prog")
int xdp_pass_ipv6(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) { 
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        return XDP_PASS;
    }
    return XDP_DROP;
}

char _license[] SEC("license") = "GPL";
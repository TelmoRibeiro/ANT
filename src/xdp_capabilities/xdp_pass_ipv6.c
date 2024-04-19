#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

SEC("xdp_pass_ipv6")
int xdp_pass_ipv6_prog(struct xdp_md* ctx) {
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
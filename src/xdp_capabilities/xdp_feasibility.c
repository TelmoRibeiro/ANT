#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

SEC("xdp_feasibility")
int xdp_feasibility_prog(struct xdp_md* ctx) {
    // get packet crucial delimeters:
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    // drop packet without eth header:
    if (data + sizeof(struct ethhdr) > data_end) { 
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    // protocol = IPV6:
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        // pass packet
        return XDP_PASS;
    }
    // drop default packet
    return XDP_DROP;
}

char _license[] SEC("license") = "GPL";
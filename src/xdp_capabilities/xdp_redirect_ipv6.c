#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

#define INTERFACE_IPV6_INDEX 1 // change me //

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

struct bpf_map_def SEC("maps") MY_MAP = {
    .type = BPF_MAP_TYPE_DEVMAP_HASH,
    .key_size   = sizeof(__u32),
    .value_size = sizeof(int),
    .max_entries = 1024, 
};

SEC("xdp_redirect")
int xdp_redirect_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        return bpf_redirect_map(&MY_MAP,INTERFACE_IPV6_INDEX,XDP_REDIRECT);
    }
    return XDP_PASS;
}
char _license[] SEC("license") = "GPL";
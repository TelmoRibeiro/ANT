#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>

/*  @ telmo - 
    Not Tested Yet
    Expected Behaviour:
        - when loaded on interfaceA direct packets toward A
        - if packets != IPv6 then process normally
        - if packets == IPv6 then redirect to loopback
    Proposed Test:
        - load this in interface X
        - load xdp_drop_ipv6 in LoopBack
        - check that ping -4 X produces normal outputs
        - check that ping -6 X produces only drops
        - check that ping -4 X produces normal outputs
        - check that ping -4 X produces only drops
    - new propose: no matter the type of packet redirect!
        - check if X is behaving just as LoopBack
        - if so, it is right
*/

struct bpf_map_def SEC("maps") LOOPBACK_MAP = {
    .type = BPF_MAP_TYPE_DEVMAP_HASH, // ??
    .key_size   = sizeof(int),        // ??
    .value_size = sizeof(int),        // ??
    .max_entries = 1024,              // ??   
};

SEC("xdp_redirect")
int xdp_redirect_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) { 
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto != htons(ETH_P_IPV6)) {
        return XDP_PASS;
    }
    int interface_index = 1;
    return bpf_redirect_map(&LOOPBACK_MAP, interface_index, BPF_F_INGRESS);
}
char _license[] SEC("license") = "GPL";
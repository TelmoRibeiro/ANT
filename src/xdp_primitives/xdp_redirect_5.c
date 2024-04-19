#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

/* @ telmo -
    this version is yet to be tested...
    
    IDEA:
        - load xdp_redirect_4 to eth4
        - load xdp_redirect_5 to eth5
        - eth4 will redirect packets to eth5
        - eth5 will redirect packets to eth6
        - but eth5 also drops every packet but IPv6
        - IPv6 packets will roam freely
        - IPv4 packets will be lost
*/

struct bpf_map_def SEC("maps") MY_MAP = {
    .type = BPF_MAP_TYPE_DEVMAP_HASH,
    .key_size   = sizeof(int),
    .value_size = sizeof(int),
    .max_entries = 1024,
};

SEC("xdp_redirect_5")
int xdp_redirect_5_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto != htons(ETH_P_IPV6)) {
        return XDP_DROP;
    }
    int interface_index = 5;
    return bpf_redirect_map(&MY_MAP, interface_index, BPF_F_INGRESS);
}
char _license[] SEC("license") = "GPL";
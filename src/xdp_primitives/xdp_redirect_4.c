#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

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

SEC("xdp_redirect_4")
int xdp_redirect_4_prog(struct xdp_md* ctx) {
    int interface_index = 4;
    return bpf_redirect_map(&MY_MAP, interface_index, BPF_F_INGRESS);
}
char _license[] SEC("license") = "GPL";
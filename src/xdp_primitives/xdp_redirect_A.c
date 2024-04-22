#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#define INTERFACE_INDEX 5

/* @ telmo -
    TESTED:
        - Generic Mode
    NOT TESTED:
        - Native
        - Offloaded
    
    IDEA:
        - load xdp_redirect_A to interface with index 4
        - load xdp_redirect_B to interface with index 5
        - A will redirect packets to B
        - B will redirect packets to A
        - but B drops every packet but IPv6
        - IPv6 packets will roam freely
        - IPv4 packets will be lost
*/

struct bpf_map_def SEC("maps") MY_MAP = {
    .type = BPF_MAP_TYPE_DEVMAP_HASH,
    .key_size   = sizeof(int),
    .value_size = sizeof(int),
    .max_entries = 1024, 
};

SEC("xdp_redirect_A")
int xdp_redirect_A_prog(struct xdp_md* ctx) {
    return bpf_redirect_map(&MY_MAP, INTERFACE_INDEX, XDP_REDIRECT);
}
char _license[] SEC("license") = "GPL";
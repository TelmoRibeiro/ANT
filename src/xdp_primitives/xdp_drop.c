#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

/* @ telmo
    TESTED:
        - Generic Mode
    NOT TESTED:
        - Native
        - Offloaded

    IDEA:
        - drops every packet without trace point exception
*/

SEC("xdp_drop")
int xdp_drop_prog(struct xdp_md* ctx) {
    return XDP_DROP;
}
char _license[] SEC("license") = "GPL";
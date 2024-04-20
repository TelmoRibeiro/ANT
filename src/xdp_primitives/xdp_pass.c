#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

/* @ telmo -
    TESTED:
        - Generic Mode
    NOT TESTED:
        - Native
        - Offloaded

    IDEA:
        - pass every packet (standard network stack handling)
*/

SEC("xdp_pass")
int xdp_pass_prog(struct xdp_md* ctx) {
    return XDP_PASS;
}
char _license[] SEC("license") = "GPL";
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

/*  @ telmo -
    Not Yet Tested
*/

SEC("xdp_pass")
int xdp_pass_prog(struct xdp_md* ctx) {
    return XDP_PASS;
}
char _license[] SEC("license") = "GPL";
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

/* @ telmo -
    TESTED:
        - Generic Mode
    NOT TESTED:
        - Native
        - Offloaded

    IDEA:
        - drops every packet with trace point exception
*/

SEC("xdp_aborted")
int xdp_aborted_prog(struct xdp_md* ctx) {
    bpf_printk("@ xdp-aborted - packet received and yet dropped!\n");
    return XDP_ABORTED;
}
char _license[] SEC("license") = "GPL";
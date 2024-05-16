#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp_aborted")
int xdp_aborted_prog(struct xdp_md* ctx) {
    // abort all packets
    bpf_printk("@ xdp-aborted - packet received and yet dropped!\n");
    return XDP_ABORTED;
}
char _license[] SEC("license") = "GPL";
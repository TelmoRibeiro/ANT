#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>
#include <linux/ip.h>

#include <bpf/bpf_endian.h>
#include <linux/if_packet.h>
#include <linux/if_vlan.h>
#include <linux/if.h>
#include <linux/in.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/in6.h>
#include <linux/types.h>

#define ETH_INDEX 3

SEC("xdp_redirect_ipv4")
int xdp_redirect_ipv4_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto != htons(ETH_P_IP)) {
        return XDP_PASS;
    }
    struct iphdr* iph = data + sizeof(struct ethhdr);
    if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
        return XDP_DROP;
    }
    __u32 dst = inet_addr("192.168.1.95");
    iph->daddr = dst;
    return bpf_redirect(ETH_INDEX,0);
}
char _license[] SEC("license") = "GPL";
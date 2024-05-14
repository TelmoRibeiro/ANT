#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <arpa/inet.h>

SEC("xdp_drop_icmp")
int xdp_drop_icmp_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto == htons(ETH_P_IP)) {
        if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
            return XDP_DROP;
        }
        struct iphdr* iph = data + sizeof(struct ethhdr);
        if (iph->protocol == IPPROTO_ICMP) {
            return XDP_DROP;
        }
        return XDP_PASS;
    }
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        if (data + sizeof(struct ethhdr) + sizeof(struct ipv6hdr) > data_end) {
            return XDP_DROP;
        }
        struct ipv6hdr* ipv6h = data + sizeof(struct ethhdr);
        if (ipv6h->nexthdr == IPPROTO_ICMPV6) {
            return XDP_DROP;
        }
        return XDP_PASS;
    }
    return XDP_PASS;
}
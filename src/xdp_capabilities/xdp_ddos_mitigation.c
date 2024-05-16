#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <arpa/inet.h>

SEC("xdp_ddos_mitigation")
int xdp_ddos_mitigation_prog(struct xdp_md* ctx) {
    // get packet crucial delimeters:
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    // drop packet without eth header:
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    // protocol = IPV4:
    if (eth->h_proto == htons(ETH_P_IP)) {
        // drop packet without ipv4 header:
        if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
            return XDP_DROP;
        }
        struct iphdr* iph = data + sizeof(struct ethhdr);
        // protocol = ICMP:
        if (iph->protocol == IPPROTO_ICMP) {
            // drop packet
            return XDP_DROP;
        }
        // pass IPV4 packet
        return XDP_PASS;
    }
    // protocol = IPV6:
    if (eth->h_proto == htons(ETH_P_IPV6)) {
        // drop packet without ipv6 header:
        if (data + sizeof(struct ethhdr) + sizeof(struct ipv6hdr) > data_end) {
            return XDP_DROP;
        }
        struct ipv6hdr* ipv6h = data + sizeof(struct ethhdr);
        // protocol = ICMPv6
        if (ipv6h->nexthdr == IPPROTO_ICMPV6) {
            // drop packet
            return XDP_DROP;
        }
        // pass IPV6 packet
        return XDP_PASS;
    }
    // pass default packet
    return XDP_PASS;
}
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <arpa/inet.h>

SEC("xdp_firewalling")
int xdp_firewalling_prog(struct xdp_md* ctx) {
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
        // drop packet without ip header:
        if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end) {
            return XDP_DROP;
        }
        struct iphdr* iph = data + sizeof(struct ethhdr);
        // drop packet from 192.168.1.1:
        __u8 target_ip[] = {192,168,1,1};
        if (__builtin_memcmp(&iph->saddr,target_ip,sizeof(target_ip)) == 0) {
            return XDP_DROP;
        }
        // pass IPV4 packet:
        return XDP_PASS;
    }
    // pass default packet:
    return XDP_PASS;
}
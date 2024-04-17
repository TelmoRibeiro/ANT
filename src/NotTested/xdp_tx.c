#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/in.h>
// #include <linux/udp.h>
// #include <arpa/inet.h>

// @telmo - TO DO //

struct bpf_map_def SEC("maps") tx_port_map = {
    .type = BPF_MAP_TYPE_DEVMAP,
    .key_size = sizeof(int),
    .value_size = sizeof(int),
    .max_entries = 64, // change if needed
};

SEC("xdp_tx")
int xdp_tx_prog(struct xdp_md* ctx) {
    void* data_end = (void*)(long)ctx->data_end;
    void* data     = (void*)(long)ctx->data;
    if (data + sizeof(struct ethhdr) > data_end) {
        return XDP_DROP;
    }
    struct ethhdr* eth = data;
    if (eth->h_proto == htons(ETH_P_IP)) { // IPV4
        struct iphdr* ip = data + sizeof(struct ethhdr);
        if (ip + sizeof(struct iphdr) > data_end) {
            return XDP_DROP;
        }
        if (ip->protocol == IPPROTO_TCP) { // TCP
            struct tcphdr* tcp = (void*) ip + sizeof(struct iphdr);
            if ((void*)tcp + sizeof(struct tcphdr) > data_end) {
                return XDP_DROP;
            }
            struct ethhdr tmp_eth = *eth;
            __builtin_memcp(eth->h_dest, tmp_eth.h_source, ETH_ALEN);
            __builtin_memcp(eth->h_source, tmp_eth.h_dest, ETH_ALEN);
            return bpf_redirect_map(&tx_port_map, 0, XDP_TX);
        }
    }
    return XDP_PASS;
}
char _license[] SEC("license") = "GPL";
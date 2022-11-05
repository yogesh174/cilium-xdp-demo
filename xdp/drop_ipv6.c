#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

SEC("drop_ipv6")
int xdp_drop_ipv6(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;

    // If not ethernet frame pass it
    if (data + sizeof(struct ethhdr) > data_end)
        return XDP_PASS;

    // If the ethernet frame is ipv6 drop it
    if (eth->h_proto == htons(ETH_P_IPV6))
        return XDP_DROP;

    return XDP_PASS;
}

char __license[] SEC("license") = "GPL";

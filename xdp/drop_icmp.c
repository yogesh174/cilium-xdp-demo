#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <arpa/inet.h>

SEC("drop_icmp")
int xdp_drop_icmp(struct xdp_md *ctx)
{
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;

  // Not the required packet
  if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) > data_end)
    return XDP_PASS;

  struct ethhdr *eth = data;

  // If not ip packet pass it
  if (eth->h_proto != htons(ETH_P_IP))
        return XDP_PASS;

  struct iphdr *ip = data + sizeof(*eth);

  // If the ip packet is ICMP then drop it
  if (ip->protocol == IPPROTO_ICMP)
    return XDP_DROP;

  return XDP_PASS;
}

char __license[] SEC("license") = "GPL";

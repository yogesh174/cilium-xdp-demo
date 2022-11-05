#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <arpa/inet.h>

SEC("drop_tcp")
int xdp_drop_tcp(struct xdp_md *ctx)
{
  void *data = (void *)(long)ctx->data;
  void *data_end = (void *)(long)ctx->data_end;

  // Not required packet
  if (data + sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr) > data_end)
      return XDP_PASS;
  
  struct ethhdr *eth = data;
  // If not ip packet pass it
  if (eth->h_proto != htons(ETH_P_IP))
        return XDP_PASS;

  struct iphdr *ip = data + sizeof(*eth);
  // If the ip packet is not TCP then pass it
  if (ip->protocol != IPPROTO_TCP)
    return XDP_PASS;
  
  struct tcphdr *tcp = data + sizeof(*ip) + sizeof(*eth);
  // If the TCP port is 80 then drop
  if (ntohs(tcp->dest) == 80)
    return XDP_DROP;

  return XDP_PASS;
}

char __license[] SEC("license") = "GPL";

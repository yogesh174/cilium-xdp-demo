#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("drop_all")
int  xdp_drop_all(struct xdp_md *ctx)
{
	return XDP_DROP;
}

char __license[] SEC("license") = "GPL";

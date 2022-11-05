# Cilium and XDP
A network programming mini-project showcasing a basic working of Cilium and how it utilizes XDP & eBPF under the hood.

# Cilium

## Application background
The background would be crystal clear if you watch [Spy X Family](https://animixplay.to/v1/spy-x-family "Watch Spy X Family") but anyways here we go ... Corrupt politicians, frenzied nationalists, and other warmongering forces constantly jeopardise the thin veneer of peace between neighbouring countries Ostania and Westalis. In spite of their plots, the renowned spy and master of disguise "Twilight" from WISE (aka Westalis Intelligence) fulfils dangerous missions one after another in the hope that no child will have to experience the horrors of war. In the bustling Ostanian city of Berlint, Twilight dons the alias of "Loid Forger," an esteemed psychiatrist for the world peace mission "operation strix". Enlisting the help of unmarried city hall clerk Yor Briar to act as his wife and adopting the curious six-year-old orphan Anya as his daughter, Loid enacts his master plan to ensure world peace. And just like Loid is hiding his true identity, Yor— an underground assassin known as "Thorn Princess" and Anya—an esper who can read people's minds—have no plans to disclose their own secrets either. Although this picture-perfect family is founded on deception, the Forgers gradually come to understand that the love they share for one another trumps all else. On top of this already complex mesh of relationships, there is also Yor's brother Yuri Briar - who secretly works for State Security Service in Ostania, and hunts down spies from Westalis Intelligence. This makes it a hell mode level difficulty for the poor Twilight to succeed in his operation strix.

## WISE application
This is a flask application is an application for agents in WISE aka Westalis Intelligence that has three endpoints - `/`, `/report-mission` and `/emergency-abort`. The `/emergency-abort` endpoint is only meant for high level managers in WISE like the Handler aka Sylvia.

## K8s manifests
The `wise.yaml` launches this wise application as a Deployment with 2 replicas and a Service for this deployment. Note that these have the following labels:

    - country: westalis
    - org: wise

The `twilight.yaml` deploys a container installed with networking tools and has the following labels:

    - country: westalis
    - agent: twilight

The `yuri.yaml` deploys a container installed with networking tools and has the following labels:

    - country: ostania
    - agent: yuri

Now coming to enforcing policies `westalis-policy.yaml` acts as a layer 3 firewall allowing only resources with the label `country: westalis` access the application. Whereas `updated-westalis-policy.yaml` acts as a layer 7 firewall allowing resources with the label `country: westalis` access the `/` and `/report-mission`.

# XDP
To get the environment running:

```
docker build -t xdp .
docker run --privileged -dti --rm --name xdp-demo xdp
docker exec -it xdp-demo /bin/bash
```

To see `drop_all.c` running:
```
$XDP_COMPILE drop_all.c  # compiles the program
ip link set eth0 xdpgeneric obj drop_all.o sec drop_all
```

The file names are obvious enough to know what they do but anyways here's the description:
- `drop_all.c`: Drops all packets
- `drop_icmp.c`: Drops ICMPv4 packets
- `drop_ipv6.c`: DROPS all IPv6 packets
- `drop_tcp_80.c`: Drops TCP packets with destination port as 80

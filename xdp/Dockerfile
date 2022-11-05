FROM ubuntu:20.04

RUN export DEBIAN_FRONTEND=noninteractive && apt-get update \
  && apt-get install -y clang llvm iproute2 iputils-ping libbpf-dev libc6-dev-i386 apache2 apache2-utils 
COPY *.c /

ENV XDP_COMPILE="clang -g -c -O2 -target bpf -I/usr/include/x86_64-linux-gnu/"
EXPOSE 80

CMD ["apache2ctl", "-D", "FOREGROUND"]

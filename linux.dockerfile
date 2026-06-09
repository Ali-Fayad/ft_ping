FROM debian:stable-slim

RUN apt update && apt install -y \
    build-essential \
    iputils-ping \
    net-tools \
    iproute2 \
    tcpdump \
    gdb \
    valgrind

WORKDIR /app
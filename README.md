# ft_ping

`ft_ping` is a C reimplementation of the basic IPv4 ICMP behavior of the
`ping` command. It resolves a hostname or IPv4 address, opens a raw ICMP
socket, sends ICMP Echo Requests, receives matching Echo Replies, prints
round-trip timing, and reports final statistics when interrupted.

The project targets Debian/Linux. A Debian Docker image is provided for
development and testing.

## Goals

- Reproduce the core behavior of `ping` for IPv4 hosts.
- Build ICMP Echo Request packets manually.
- Receive and validate ICMP Echo Replies from raw sockets.
- Support the mandatory `-?` and `-v` options.
- Print final packet and RTT statistics on `Ctrl+C`.

## Features Implemented

- IPv4 hostname and raw IPv4 address resolution with `getaddrinfo()`.
- Raw ICMP socket creation with `socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)`.
- ICMP Echo Request construction.
- ICMP checksum generation.
- Continuous send/receive loop.
- Matching Echo Reply validation by process id and sequence number.
- RTT measurement with `gettimeofday()`.
- Final statistics: transmitted, received, packet loss, min/avg/max RTT.
- Signal-safe `SIGINT` flag for clean shutdown.
- Verbose reporting for selected ICMP error packets.

## Supported Flags

| Flag | Behavior |
|---|---|
| `-?` | Print help and exit successfully. No DNS or socket work is performed. |
| `-v` | Enable concise reporting for selected ICMP errors: time exceeded, destination unreachable, redirect, and parameter problem. |

Only standalone `-?` and `-v` are accepted. Combined options such as `-v?`
are not currently supported.

## Build

From the `dev/` directory:

```sh
make
```

The build creates:

```text
./ft_ping
```

Useful Makefile rules:

```sh
make clean
make fclean
make re
```

The Makefile compiles with:

```text
-Wall -Wextra -Werror
```

## Docker Environment

The project includes `linux.dockerfile`, which installs build and network
debugging tools on Debian:

```sh
docker build -f linux.dockerfile -t ft_ping-dev .
docker run --rm -it --cap-add=NET_RAW --cap-add=NET_ADMIN -v "$PWD":/app ft_ping-dev
```

Raw ICMP sockets normally require root privileges or the appropriate Linux
capabilities.

## Usage

```sh
./ft_ping [options] <destination>
```

Examples:

```sh
./ft_ping -?
./ft_ping 8.8.8.8
./ft_ping -v 8.8.8.8
./ft_ping google.com
```

## Example Outputs

Help:

```text
Usage
  ft_ping [options] <destination>

Options:
  -v        verbose output
  -?        display this help and exit
```

Missing target:

```text
ft_ping: missing host operand
```

Too many targets:

```text
ft_ping: too many arguments
```

Invalid option:

```text
ft_ping: invalid option
```

Without raw socket privileges:

```text
ft_ping: raw socket requires root privileges
```

Typical privileged run:

```text
PING 8.8.8.8 (8.8.8.8): 56 data bytes
64 bytes from 8.8.8.8: icmp_seq=1 ttl=117 time=12.345 ms
^C
--- 8.8.8.8 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss
round-trip min/avg/max = 12.345/12.345/12.345 ms
```

Verbose ICMP error example:

```text
92 bytes from 192.168.40.1: Time to live exceeded
```

## Project Structure

```text
dev/
├── includes/
│   ├── ft_ping.h        Shared types and function prototypes
│   └── messages.h       User-facing messages and constants
├── srcs/
│   ├── main.c           Program entry point
│   ├── init.c           t_ping initialization
│   ├── parser.c         Argument parsing
│   ├── error.c          Error/help output
│   ├── cleanup.c        Cleanup flow
│   ├── resolve_address.c Hostname/IP resolution
│   ├── socket.c         Raw ICMP socket lifecycle
│   ├── packet.c         ICMP Echo Request construction
│   ├── checksum.c       ICMP checksum
│   ├── process.c        Main ping loop
│   ├── receive.c        recvfrom(), packet parsing, reply output
│   ├── statistics.c     RTT and final statistics
│   └── signal.c         SIGINT flag and handler
├── Makefile
└── linux.dockerfile
```

## Current Implementation Status

The implementation currently performs real raw-socket ICMP work when run with
sufficient privileges. It continuously sends one Echo Request at a time,
waits for a matching Echo Reply, prints reply timing, sleeps one second, and
continues until `Ctrl+C`.

The receive path parses the IPv4 header first, then the ICMP header. Echo
Replies are accepted only when the identifier matches `getpid() & 0xffff`
and the sequence matches the current request.

## Known Limitations

- No timeout handling is implemented. A lost packet can block in `recvfrom()`
  until a packet arrives or `Ctrl+C` interrupts the program.
- Packet loss only reflects transmitted requests versus valid replies observed
  before shutdown; unanswered probes are not timed out.
- Linux portability should be verified in the target Debian container. The
  current source uses BSD-style ICMP names such as `struct icmp` and
  `ICMP_TIMXCEED`.
- Verbose mode prints concise messages for only four ICMP error classes.
- No duplicate packet detection.
- No min/avg/max/mdev formatting.
- No configurable interval, TTL, payload size, timeout, or packet count.
- No IPv6 support.
- No advanced GNU/inetutils output compatibility.

## Future Improvements

- Add receive timeouts and count unanswered probes as packet loss.
- Verify and adjust ICMP type names for Debian/Linux headers.
- Decode more ICMP error codes in verbose mode.
- Add duplicate detection.
- Add configurable packet count and interval options.
- Add better parity with inetutils `ping` output.
- Add integration tests inside the Debian Docker environment.

## License

No explicit license file is currently included in this repository. Treat the
code as unlicensed until a project license is added.

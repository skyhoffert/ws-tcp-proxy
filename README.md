# ws-tcp-proxy
Proxy that bridges a websocket and a tcp connection.

## Modes

Mode is set with the command line argument with the following format:

`--mode=<M>`

where `<M>` is replaced with the desired mode. Mode is a required argument.

Modes are described below:

### W Mode

This program hosts a websocket server. Data is then sent to an external TCP server.

### T Mode

This program hosts a TCP server. Data is then sent to an external Websocket server.

## Port In

Port In tells this program which port to listen on for incoming data.

`--port-in=<port>`

where `<port>` is replaced with the desired port. Port In is a required argument.

## Port Out

Port Out tells this program which port to send data to in the given mode.

`--port-out=<port>`

where `<port>` is replaced with the desired port. Port Out is a required argument.

## Addr Out

Addr Out tells this program what address to use when sending data out.

`--addr-out=<addr>`

where `<addr>` is replaced with the desired address. This should be IPv6, but IPv4 is also acceptable.

Addr Out is an optional requirement that defaults to "::1" (localhost) when omitted.

## Example

An example unix command for running the program is as below:

`./wstcpproxy --mode=A --port-in=5000 --port-out=5001`

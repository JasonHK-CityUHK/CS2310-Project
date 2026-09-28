# Minecraft Server Snapshot

This bundle contains the server executable and the Minecraft 26.3 registry and
data-pack files required at runtime. It was built and tested on Ubuntu 24.04.

Run it from the extracted bundle directory:

```sh
./run-snapshot.sh
```

Pass an optional port as the first argument, or choose a logging level with
`MCSERVER_LOG_LEVEL=error`, `warning`, `info`, or `debug`:

```sh
MCSERVER_LOG_LEVEL=debug ./run-snapshot.sh 25566
```

The default port is 25565. The bundle is built for Linux and requires a
compatible C++ runtime and zlib shared library on the host.

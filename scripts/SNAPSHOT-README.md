# Minecraft Server Snapshot

This bundle contains the server executable and the Minecraft 26.3 registry and
data-pack files required at runtime. It was built and tested on Ubuntu 24.04.

Run it from the extracted bundle directory:

```sh
./run-snapshot.sh
```

Set `server-port` in `server.properties` in the working directory to change
the port. Choose a logging level with `MCSERVER_LOG_LEVEL=error`, `warning`,
`info`, or `debug`:

```sh
MCSERVER_LOG_LEVEL=debug ./run-snapshot.sh
```

The default port is 25565. The bundle is built for Linux and requires a
compatible C++ runtime and zlib shared library on the host.

Place an existing Java 26.3 world in `world` in the working directory, or set
`level-name` in `server.properties` to another world directory. The server does
not generate worlds or chunks. Only enclosed-stone edits are currently supported;
back up the world before use. Changes autosave every five seconds and on Ctrl+C.

FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        cmake \
        git \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --target mcserver --parallel 2

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        zlib1g \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt/mcserver
COPY --from=build /src/build/src/mcserver ./bin/mcserver
COPY --from=build /src/build/share/mcserver ./share/mcserver

ENV MCSERVER_DATA_DIR=/opt/mcserver/share/mcserver
EXPOSE 25565
ENTRYPOINT ["/opt/mcserver/bin/mcserver"]

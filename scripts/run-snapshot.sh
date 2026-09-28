#!/usr/bin/env bash
set -euo pipefail

bundle_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
export MCSERVER_DATA_DIR="${bundle_dir}/share/mcserver"
exec "${bundle_dir}/bin/mcserver" "$@"

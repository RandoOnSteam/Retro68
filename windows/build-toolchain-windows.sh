#!/bin/sh
set -e
src=$(cd "$(dirname "$0")/.." && pwd)
export MSYS=winsymlinks:native
export CONFIG_SITE="$src/windows/config.site"
bash "$src/build-toolchain.bash" "$@"
find toolchain -name '*.exe' | while read -r program; do
  directory=$(dirname "$program")
  ldd "$program" | awk '$3 ~ /^\/ucrt64\/bin\// { print $3 }' | while read -r library; do
    cp -f "$library" "$directory/"
  done
done

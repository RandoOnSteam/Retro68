#!/bin/sh
set -e
src=$(cd "$(dirname "$0")/.." && pwd)
toolchain="$1"
stage="$2"
flavor="$3"
rm -rf "$stage"
mkdir -p "$stage"
if [ "$flavor" = public ]; then
  export MSYS=winsymlinks:native
  cp -a "$toolchain" "$stage/linked"
  bash "$src/interfaces-and-libraries.sh" "$stage/linked" --multiversal
  rm -rf "$stage/linked/universal"
  mkdir -p "$stage/share/retro68"
  (cd "$stage/linked" && find . -type l -lname '*multiversal/*' | sed 's|^\./||') > "$stage/share/retro68/multiversal.manifest"
  cp -rL "$stage/linked" "$stage/toolchain"
  rm -rf "$stage/linked"
  cp -f "$src/interfaces-and-libraries.sh" "$src/prepare-headers.sh" "$src/prepare-rincludes.sh" "$src/windows/install-interfaces.sh" "$stage/share/retro68/"
  cp -f "$src/windows/install-interfaces.cmd" "$stage/"
  mkdir -p "$stage/msys/usr/bin" "$stage/msys/etc"
  for tool in bash sh find ln rm mkdir cp mv basename dirname sed tr ls cat readlink cygpath env uname; do
    cp -f "/usr/bin/$tool.exe" "$stage/msys/usr/bin/"
  done
  for program in "$stage"/msys/usr/bin/*.exe; do
    ldd "$program" | awk '$3 ~ /^\/usr\/bin\// { print $3 }'
  done | sort -u | while read -r library; do
    cp -f "$library" "$stage/msys/usr/bin/"
  done
  {
    echo "none / cygdrive binary,posix=0,noacl,user 0 0"
    echo "none /tmp usertemp binary,posix=0,noacl 0 0"
  } > "$stage/msys/etc/fstab"
else
  cp -rL "$toolchain" "$stage/toolchain"
fi
find "$stage/toolchain" \( -name "*.exe" -o -name "*.dll" \) -exec strip --strip-unneeded {} +
cp -f "$src/windows/README.windows.txt" "$stage/README.txt"
cp -f "$src/COPYING" "$stage/COPYING"
cp -f "$src/COPYING.RUNTIME" "$stage/COPYING.RUNTIME"

#!/bin/sh
here=$(cd "$(dirname "$0")" && pwd)
prefix=$(cd "$here/../../toolchain" && pwd)
interfaces=$(cygpath -u "$1")
while IFS= read -r file; do
  rm -f "$prefix/$file"
done < "$here/multiversal.manifest"
rm -rf "$prefix/m68k-apple-macos/RIncludes" "$prefix/powerpc-apple-macos/RIncludes"
if ! bash "$here/interfaces-and-libraries.sh" "$prefix" "$interfaces"; then
  bash "$here/interfaces-and-libraries.sh" "$prefix" --multiversal
  exit 1
fi

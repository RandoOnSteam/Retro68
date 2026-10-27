cmake_minimum_required(VERSION 3.20)
project(Retro68Windows NONE)

if(NOT CMAKE_HOST_WIN32)
  message(FATAL_ERROR "This CMake build is for Windows hosts. Use build-toolchain.bash elsewhere.")
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/MSYS2.cmake)

set(RETRO68_BUILD_OPTIONS "--ninja" CACHE STRING "Options passed to build-toolchain.bash")
set(RETRO68_WORK_DIR "${CMAKE_BINARY_DIR}/work" CACHE PATH "build-toolchain.bash build directory; the toolchain is installed to <dir>/toolchain")

msys2_bootstrap(
  base-devel git bison flex texinfo
  mingw-w64-ucrt-x86_64-gcc
  mingw-w64-ucrt-x86_64-cmake
  mingw-w64-ucrt-x86_64-ninja
  mingw-w64-ucrt-x86_64-boost
  mingw-w64-ucrt-x86_64-gmp
  mingw-w64-ucrt-x86_64-mpfr
  mingw-w64-ucrt-x86_64-mpc
  mingw-w64-ucrt-x86_64-isl
  mingw-w64-ucrt-x86_64-zlib
  mingw-w64-ucrt-x86_64-ruby)

set(stamp "${CMAKE_BINARY_DIR}/retro68.stamp")
add_custom_command(
  OUTPUT "${stamp}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${RETRO68_WORK_DIR}"
  COMMAND ${CMAKE_COMMAND} -E env
    MSYSTEM=UCRT64 CHERE_INVOKING=1 MSYS2_PATH_TYPE=minimal
    "${MSYS2_ROOT}/usr/bin/bash.exe" -lc
    "cd \"$(cygpath -u '${RETRO68_WORK_DIR}')\" && sh \"$(cygpath -u '${CMAKE_CURRENT_SOURCE_DIR}/build-toolchain-windows.sh')\" ${RETRO68_BUILD_OPTIONS}"
  COMMAND ${CMAKE_COMMAND} -E touch "${stamp}"
  USES_TERMINAL
  VERBATIM)
add_custom_target(retro68 ALL DEPENDS "${stamp}")

function(retro68_package name flavor)
  set(package "${CMAKE_BINARY_DIR}/${name}.zip")
  set(stage "${CMAKE_BINARY_DIR}/package-${flavor}")
  add_custom_command(
    OUTPUT "${package}"
    COMMAND ${CMAKE_COMMAND} -E env
      MSYSTEM=UCRT64 CHERE_INVOKING=1 MSYS2_PATH_TYPE=minimal
      "${MSYS2_ROOT}/usr/bin/bash.exe" -lc
      "sh \"$(cygpath -u '${CMAKE_CURRENT_SOURCE_DIR}/package-windows.sh')\" \"$(cygpath -u '${RETRO68_WORK_DIR}/toolchain')\" \"$(cygpath -u '${stage}/Retro68')\" ${flavor}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${package}"
    COMMAND ${CMAKE_COMMAND} -E chdir "${stage}" ${CMAKE_COMMAND} -E tar cf "${package}" --format=zip Retro68
    DEPENDS retro68 "${stamp}"
      "${CMAKE_CURRENT_SOURCE_DIR}/package-windows.sh"
      "${CMAKE_CURRENT_SOURCE_DIR}/install-interfaces.sh"
      "${CMAKE_CURRENT_SOURCE_DIR}/install-interfaces.cmd"
      "${CMAKE_CURRENT_SOURCE_DIR}/README.windows.txt"
    USES_TERMINAL
    VERBATIM)
  add_custom_target(retro68-package-${flavor} DEPENDS "${package}")
endfunction()

retro68_package(retro68-windows-x86_64 private)
retro68_package(retro68-windows-x86_64-nointerfaces public)

#!/usr/bin/env bash

set -e
export GTEST_COLOR=1

CMAKE_CONFIG_OPTS="-DCMAKE_BUILD_TYPE=Release"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic-cxx17.cmake'"
CMAKE_OPTS="$CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"

cmake -H. -B_builds "$CMAKE_OPTS"
cmake --build _builds
cmake --build _builds --target algorithm 

cp _builds/src/libalgorithm.a src/include/*.hpp "$1"

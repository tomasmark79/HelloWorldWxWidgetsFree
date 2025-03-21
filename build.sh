#!/bin/bash
set -e
conan profile detect --force
conan install "." --output-folder="./build/standalone/default/debug" --deployer=full_deploy --build=missing --profile default --settings build_type=Debug
source "./build/standalone/default/debug/conanbuild.sh" && cmake -S "./standalone" -B "./build/standalone/default/debug" -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="./build/installation/default/debug"
source "./build/standalone/default/debug/conanbuild.sh" && cmake --build "./build/standalone/default/debug"  -j 16
source "./build/standalone/default/debug/conanbuild.sh" && cmake --build "./build/standalone/default/debug" --target install -j 16
#!/bin/bash

set -e

src="$1"
dst="$2"

if [ "$#" -ne 2 ] || [ ! -f "$src/llvm/CMakeLists.txt" ]; then
    echo "Usage: $(dirname "$0") <src> <dst>"
    exit 1
fi

function read_cmake_variable() {
    sed -nE 's/^[[:space:]]*set[[:space:]]*\([[:space:]]*'"$2"'[[:space:]]+("?)([^")]*)(\1)[[:space:]]*\).*/\2/p' "$1"
}

if [ -f "$src/cmake/Modules/LLVMVersion.cmake" ]; then
    llvm_version_major=$(read_cmake_variable "$src/cmake/Modules/LLVMVersion.cmake" LLVM_VERSION_MAJOR)
    llvm_version_minor=$(read_cmake_variable "$src/cmake/Modules/LLVMVersion.cmake" LLVM_VERSION_MINOR)
    llvm_version_patch=$(read_cmake_variable "$src/cmake/Modules/LLVMVersion.cmake" LLVM_VERSION_PATCH)
    llvm_version_suffix=$(read_cmake_variable "$src/cmake/Modules/LLVMVersion.cmake" LLVM_VERSION_SUFFIX)
else
    llvm_version_major=$(read_cmake_variable "$src/CMakeLists.txt" LLVM_VERSION_MAJOR)
    llvm_version_minor=$(read_cmake_variable "$src/CMakeLists.txt" LLVM_VERSION_MINOR)
    llvm_version_patch=$(read_cmake_variable "$src/CMakeLists.txt" LLVM_VERSION_PATCH)
    llvm_version_suffix=$(read_cmake_variable "$src/CMakeLists.txt" LLVM_VERSION_SUFFIX)
fi
if [ -n "$llvm_version_suffix" ]; then
    echo "LLVM ${llvm_version_major}.${llvm_version_minor}.${llvm_version_patch}-${llvm_version_suffix}"
else
    echo "LLVM ${llvm_version_major}.${llvm_version_minor}.${llvm_version_patch}"
fi

mkdir -p "$dst"
cp -r $src/libunwind "$dst/"

if [ -d "$src/cmake/Modules" ]; then
    mkdir -p "$dst/cmake/Modules"
    cp "$src/cmake/Modules/HandleCompilerRT.cmake" \
       "$src/cmake/Modules/LLVMCheckCompilerLinkerFlag.cmake" \
       "$dst/cmake/Modules/"
fi

if [ -d "$src/runtimes/cmake/Modules" ]; then
    mkdir -p "$dst/runtimes/cmake/Modules"
    cp "$src/runtimes/cmake/Modules/WarningFlags.cmake" \
       "$src/runtimes/cmake/Modules/HandleFlags.cmake" \
       "$dst/runtimes/cmake/Modules/"
fi

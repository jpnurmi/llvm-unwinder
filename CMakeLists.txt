cmake_minimum_required(VERSION 3.10)

project(llvm-unwinder C CXX ASM)

set(LIBUNWIND_ENABLE_SHARED OFF)
set(LIBUNWIND_ENABLE_STATIC ON)
add_subdirectory(libunwind)

add_executable(llvm-unwinder main.c)
target_include_directories(llvm-unwinder PRIVATE libunwind/include)
target_link_libraries(llvm-unwinder PRIVATE unwind_static)

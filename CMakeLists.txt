cmake_minimum_required(VERSION 3.10)

project(test-unwinder C CXX ASM)

option(USE_LLVM "Use LLVM" ON)

add_executable(test-unwinder main.c)

if(USE_LLVM)
  set(LIBUNWIND_ENABLE_SHARED OFF)
  set(LIBUNWIND_ENABLE_STATIC ON)
  add_subdirectory(llvm/libunwind)
  target_include_directories(test-unwinder PRIVATE llvm/libunwind/include)
  target_link_libraries(test-unwinder PRIVATE unwind_static)
else()
  include(FindPkgConfig)
  pkg_check_modules(UNWIND REQUIRED IMPORTED_TARGET libunwind)
  target_link_libraries(test-unwinder PRIVATE PkgConfig::UNWIND)
endif()

target_compile_options(test-unwinder PRIVATE -fno-omit-frame-pointer)

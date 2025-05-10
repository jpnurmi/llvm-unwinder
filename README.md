# test-unwinder

## non-GNU libunwind

```sh
$ cmake -B build -D USE_LLVM=OFF && cmake --build build && ./build/test-unwinder 
[...]
ip = 60fbf729c641, sp = 7fff27462390, proc = main+0x123, dw = main
ip = 77704622a338, sp = 7fff274623c0, proc = __libc_init_first+0x88, dw = __libc_start_call_main
ip = 77704622a3fb, sp = 7fff27462460, proc = __libc_start_main+0x8b, dw = __libc_start_main@@GLIBC_2.34
ip = 60fbf729c285, sp = 7fff274624c0, proc = _start+0x25, dw = _start
```

## LLVM libunwind

```sh
$ cmake -B build -D USE_LLVM=ON && cmake --build build && ./build/test-unwinder 
[...]
ip = 61171246d7a1, sp = 7fff32e9e970, proc = <unknown>, dw = main
ip = 73e9d402a338, sp = 7fff32e9e9a0, proc = <unknown>, dw = __libc_start_call_main
ip = 73e9d402a3fb, sp = 7fff32e9ea40, proc = __libc_start_main+0x8b, dw = __libc_start_main@@GLIBC_2.34
ip = 61171246d3e5, sp = 7fff32e9eaa0, proc = <unknown>, dw = _start
```

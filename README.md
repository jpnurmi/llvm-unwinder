# test-unwinder

```sh
sudo apt install libdw-dev libunwind-dev
```

## non-GNU [libunwind](https://github.com/libunwind/libunwind)

```sh
$ cmake -B build -D USE_LLVM=OFF && cmake --build build && ./build/test-unwinder 
[...]
ip = 5b22c9ad263a, sp = 7ffdbe5e43e0, proc = do_something+0x11c, dw = do_something
ip = 5b22c9ad265a, sp = 7ffdbe5e4400, proc = run_program+0xd, dw = run_program
ip = 5b22c9ad2687, sp = 7ffdbe5e4410, proc = main+0x18, dw = main
ip = 71ec2182a338, sp = 7ffdbe5e4430, proc = __libc_init_first+0x88, dw = __libc_start_call_main
ip = 71ec2182a3fb, sp = 7ffdbe5e44d0, proc = __libc_start_main+0x8b, dw = __libc_start_main@@GLIBC_2.34
ip = 5b22c9ad2285, sp = 7ffdbe5e4530, proc = _start+0x25, dw = _start
```

## LLVM [libunwind](https://github.com/llvm/llvm-project/tree/main/libunwind)

```sh
$ cmake -B build -D USE_LLVM=ON && cmake --build build && ./build/test-unwinder 
[...]
ip = 58d83a1ee79a, sp = 7ffef16e82a0, proc = <unknown>, dw = do_something
ip = 58d83a1ee7ba, sp = 7ffef16e82c0, proc = <unknown>, dw = run_program
ip = 58d83a1ee7e7, sp = 7ffef16e82d0, proc = <unknown>, dw = main
ip = 7782d922a338, sp = 7ffef16e82f0, proc = <unknown>, dw = __libc_start_call_main
ip = 7782d922a3fb, sp = 7ffef16e8390, proc = __libc_start_main+0x8b, dw = __libc_start_main@@GLIBC_2.34
ip = 58d83a1ee3e5, sp = 7ffef16e83f0, proc = <unknown>, dw = _start
```

# test-unwinder

## non-GNU libunwind

```sh
$ cmake -B build -D USE_LLVM=OFF && cmake --build build && ./build/test-unwinder 
[...]
ip = 60b66c45a362, sp = 7ffdca6913c0, function = main+0x18
ip = 77277962a338, sp = 7ffdca6913e0, function = __libc_init_first+0x88
ip = 77277962a3fb, sp = 7ffdca691480, function = __libc_start_main+0x8b
ip = 60b66c45a145, sp = 7ffdca6914e0, function = _start+0x25
```

## LLVM libunwind

```sh
$ cmake -B build -D USE_LLVM=ON && cmake --build build && ./build/test-unwinder 
[...]
ip = 5ab8cb68c4e2, sp = 7ffcd94af060, function = <unknown>
ip = 7a28e382a338, sp = 7ffcd94af080, function = <unknown>
ip = 7a28e382a3fb, sp = 7ffcd94af120, function = __libc_start_main+0x8b
ip = 5ab8cb68c2c5, sp = 7ffcd94af180, function = <unknown>
```

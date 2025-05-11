default:
	cmake -B build/non-gnu && cmake --build build/non-gnu && ./build/non-gnu/test-unwinder

LLVM_VERSIONS := $(sort $(patsubst llvm/%/libunwind/CMakeLists.txt,%,$(wildcard llvm/*/libunwind/CMakeLists.txt)))

define llvm_target
llvm-$(1):
	cmake -B build/llvm-$(1) -D LLVM=$(1) && cmake --build build/llvm-$(1) && ./build/llvm-$(1)/test-unwinder
.PHONY: llvm-$(1)
endef

$(foreach ver,$(LLVM_VERSIONS),$(eval $(call llvm_target,$(ver))))

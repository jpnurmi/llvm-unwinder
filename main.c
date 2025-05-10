#include <elfutils/libdw.h>
#include <elfutils/libdwfl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

static const Dwfl_Callbacks dwfl_callbacks = {
    .find_elf = dwfl_linux_proc_find_elf,
    .find_debuginfo = dwfl_standard_find_debuginfo,
};

void show_backtrace(Dwfl *dwfl) {
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t ip, sp, offset;
  char sym[256];

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);

  while (unw_step(&cursor) > 0) {
    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    unw_get_reg(&cursor, UNW_REG_SP, &sp);

    const char *name = NULL;
    Dwfl_Module *module = dwfl_addrmodule(dwfl, ip);
    if (module) {
      GElf_Sym sym;
      GElf_Off off;
      name = dwfl_module_addrinfo(module, ip, &off, &sym, NULL, NULL, NULL);
    }

    if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
      printf("ip = %lx, sp = %lx, proc = %s+0x%lx, dw = %s\n", (long)ip,
             (long)sp, sym, (long)offset, name);
    } else {
      printf("ip = %lx, sp = %lx, proc = <unknown>, dw = %s\n", (long)ip,
             (long)sp, name);
    }
  }
}

int main(int argc, char *argv[]) {
  Dwfl *dwfl = dwfl_begin(&dwfl_callbacks);
  if (!dwfl) {
    fprintf(stderr, "dwfl_begin: %s\n", dwfl_errmsg(dwfl_errno()));
    return -1;
  }

  if (dwfl_linux_proc_report(dwfl, getpid()) != 0) {
    fprintf(stderr, "dwfl_linux_proc_report: %s\n", dwfl_errmsg(dwfl_errno()));
    dwfl_end(dwfl);
    return -1;
  }

  if (dwfl_report_end(dwfl, NULL, NULL) != 0) {
    fprintf(stderr, "dwfl_report_end: %s\n", dwfl_errmsg(dwfl_errno()));
    dwfl_end(dwfl);
    return -1;
  }

  show_backtrace(dwfl);

  dwfl_end(dwfl);

  return 0;
}

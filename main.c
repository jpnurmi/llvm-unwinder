#include <stdio.h>

#define UNW_LOCAL_ONLY
#include <libunwind.h>

void show_backtrace(void) {
  unw_cursor_t cursor;
  unw_context_t uc;
  unw_word_t ip, sp, offset;
  char sym[256];

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);
  while (unw_step(&cursor) > 0) {
    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    unw_get_reg(&cursor, UNW_REG_SP, &sp);
    if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
      printf("ip = %lx, sp = %lx, function = %s+0x%lx\n", (long)ip, (long)sp,
             sym, (long)offset);
    } else {
      printf("ip = %lx, sp = %lx, function = <unknown>\n", (long)ip, (long)sp);
    }
  }
}

int main(int argc, char *argv[]) {
  show_backtrace();
  return 0;
}

// A call through a noreturn pointer with no known target still ends its
// path once lowered, with no false __builtin_unreachable after it.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT-NOT: __builtin_unreachable
extern __attribute__((noreturn)) void (*fatal)(void);
int main(void) { fatal(); }

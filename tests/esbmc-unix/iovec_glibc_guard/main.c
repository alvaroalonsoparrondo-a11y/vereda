#include <sys/socket.h>
#include <fcntl.h>

int main(void)
{
    return 0;
}
// Imported from ESBMC regression/esbmc-unix/iovec_glibc_guard
// Needs: -I wrap
// RUN: -I wrap -D_GNU_SOURCE
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: FUTURE test passed unexpectedly; promote it to CORE
// MODE: CORE

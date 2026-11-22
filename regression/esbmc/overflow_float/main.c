int main() {
    double x = -1e11;
    return 0;
}
// Imported from ESBMC regression/esbmc/overflow_float
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$

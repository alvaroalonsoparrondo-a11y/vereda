
const char *strerror(int);

int main(int argc, char *argv[])
{
  // this should work
  char *my_ptr=argv[0];

  // this should work
  int i=strlen(my_ptr);
}
// Imported from ESBMC regression/nonz3/01_cbmc_String_Abstraction6
// RUN: --unwind 3
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE

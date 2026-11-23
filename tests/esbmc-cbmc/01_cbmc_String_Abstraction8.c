unsigned strlen(const char *);

// my own version, which returns the length +1
unsigned strlen(const char *s)
{
  unsigned int result=1;
  while(*s!=0) { s++; result++; }
  return result;  
}

int main()
{
  assert(strlen("asd")==4);
}
// Imported from ESBMC regression/cbmc/01_cbmc_String_Abstraction8
// RUN: --unwind 5
// EXPECT: ^VERIFICATION SUCCESSFUL$

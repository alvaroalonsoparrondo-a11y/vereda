unsigned strlen(const char *);
char *strcpy(char *, const char *);

int main()
{
  char a[100], b[100], *p;
  unsigned int i;
  
  i=strlen("asdasd");
  
  strcpy(a, "asd");
  strcpy(b, "asd");
  
  p=i?a:b;
  
  i=strlen(p);
  
  assert(i==3);
}
// Imported from ESBMC regression/cbmc/01_cbmc_String_Abstraction2
// RUN: --unwind 101
// EXPECT: ^VERIFICATION SUCCESSFUL$

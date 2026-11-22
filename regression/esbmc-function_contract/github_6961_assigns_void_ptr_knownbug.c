/* A void pointee names no object, so there is nothing to write through and the
 * frame the contract states is not havocked. The run says so -- "__ESBMC_assigns:
 * nothing can be written through the pointer parameter named at ..." -- rather
 * than dropping the target silently, but the caller still keeps a value the
 * callee overwrites. Stating an extent is what would fix it. */
void wipe(void *p)
{
  __ESBMC_assigns(p);
  __ESBMC_ensures(1);

  *(int *)p = 0;
}

int main(void)
{
  int x = 7;
  wipe(&x);
  __ESBMC_assert(x == 7, "wipe zeroed x, so this must be reported");
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6961_assigns_void_ptr_knownbug
// Needs: --replace-call-with-contract wipe
// RUN: --replace-call-with-contract wipe
// MODE: KNOWNBUG
// EXPECT: ^VERIFICATION FAILED$

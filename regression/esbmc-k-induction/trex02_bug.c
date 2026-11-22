_Bool nondet_bool();
int nondet_int();

//x is an input variable
int x;

void foo() {
  x--;
}

int main() {
  x=nondet_int();
  while (x > 0) {
    _Bool c = nondet_bool();
    if(c) foo();
    else foo();
  }
  assert(x==0);
}



// Imported from ESBMC regression/k-induction/trex02_bug
// Needs: --k-induction
// RUN: --k-induction -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$

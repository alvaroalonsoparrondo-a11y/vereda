typedef struct {
	float x;
} myStruct;

int main(void) {
  myStruct testObj;
  testObj.x = 200.0;
  float z = 0.0;

  if (testObj.x > 10.0f)
  {
    z = testObj.x;
  }

  assert(z == 0.0); // fail
  return 0;
}
// Imported from ESBMC regression/esbmc/github_690_z3_nocast_fail
// Needs: --ir
// RUN: --ir --z3 -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$

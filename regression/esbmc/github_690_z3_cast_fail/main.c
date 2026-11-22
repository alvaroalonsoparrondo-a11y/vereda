typedef struct {
	float x;
} myStruct;

int main(void) {
  myStruct testObj;
  testObj.x = 200.0;
  double y = 10.0;
  float z = 0.0;

  if (testObj.x > y)
  {
    z = testObj.x;
  }
  else
  {
    z = y;
  }

  assert(z == y); // fail
  return 0;
}
// Imported from ESBMC regression/esbmc/github_690_z3_cast_fail
// Needs: --ir
// RUN: --ir --z3 -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$

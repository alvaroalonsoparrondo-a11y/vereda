#include <stdbool.h>
typedef struct {
	float x;
	bool z;
} myStruct;

int main(void) {
  myStruct testObj;
  testObj.x = 0.0;
  testObj.z = false;

  if (testObj.x > 10.0)
  {
    testObj.z = true;
  }

  assert(testObj.z); // fail
  return 0;
}
// Imported from ESBMC regression/esbmc/github_687-2
// Needs: --ir
// RUN: --ir --z3 -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$

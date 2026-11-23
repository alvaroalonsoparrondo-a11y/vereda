// A double argument for a pointer parameter goes through an integer of the
// same width, as inttoptr takes integers only: 1.0 arrives as its bits.
// RUN: -m64 --dump-ir-only
// EXPECT: call void @byPointer\(ptr inttoptr \(i64 4607182418800017408 to ptr\)\)
extern int nondet(void);
static int seen;
static void byPointer(void *p) { seen = p != 0; }
static void byDouble(double d) { seen = 2; }
int main(void) {
  void (*cb)(double) = nondet() ? byDouble : (void (*)(double))byPointer;
  cb(1.0);
  return seen;
}

// Stage driver: parses options, runs the stages, prints the verdict.
#include "ir/load.h"

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

static cl::opt<std::string> inputFile(cl::Positional, cl::desc("<file.bc|file.ll>"),
                                      cl::Required);
static cl::opt<bool> dumpIR("dump-ir", cl::desc("Print the IR after the pass list and exit"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "vereda: LLVM-IR verifier\n");
  LLVMContext ctx;
  Expected<std::unique_ptr<Module>> module = vereda::ir::load(inputFile, ctx);
  if (!module) {
    errs() << argv[0] << ": " << toString(module.takeError()) << "\n";
    return 1;
  }
  if (dumpIR) {
    (*module)->print(outs(), nullptr);
    return 0;
  }
  // ponytail: the walker goes here; until then, list what would be walked.
  for (const Function &f : **module)
    if (!f.isDeclaration())
      outs() << f.getName() << "\n";
  return 0;
}

int main() { return 0; }
// Imported from ESBMC regression/goto-transcoder/cbmc_kani_report_property_class_incompatible
// Needs: --report-property-class cover --ltl
// RUN: --report-property-class cover --ltl
// MODE: FUTURE
// EXPECT: ^ERROR: --report-property-class does not support --ltl$

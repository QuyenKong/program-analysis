#include <iostream>

using namespace std;

// --- PART 6: DYNAMIC SLICING ILLUSTRATION ---
// Dynamic Slicing computes the set of statements that actually affected the
// value of a variable at a specific point during a specific execution (the
// slice criterion).
void IllustrateDynamicSlicing() {
  cout << "\n--- 6. DYNAMIC SLICING ILLUSTRATION ---" << endl;

  int x = 10; // Statement S1
  int y = 5;  // Statement S2
  int z = 0;  // Statement S3

  // Conditional statement (Control Dependency)
  if (x > y) { // Statement S4
    z = x + 1; // Statement S5 (Executed)
  } else {
    z = y + 1; // Statement S6 (Skipped)
  }

  x = z * 2; // Statement S7 (Slice Criterion Point)

  // Execution path: S1 -> S2 -> S3 -> S4 (True) -> S5 -> S7

  // Dynamic Slice (relevant statements):
  // The value of 'x' at S7 depends on 'z' (S5).
  // The execution of S5 depends on the condition S4.
  // S5 depends on the original 'x' value (S1).
  // S2 and S3 are irrelevant in this specific run.

  cout << "Output value 'x' = " << x << endl;
  cout << "Dynamic Slice for 'x' at S7 (Specific Execution):" << endl;
  cout << "  - S7: x = z * 2 (Output)" << endl;
  cout << "  - S5: z = x + 1 (Data Dependency on z)" << endl;
  cout << "  - S4: if (x > y) (Control Dependency)" << endl;
  cout << "  - S1: x = 10 (Initial definition of x)" << endl;

  cout << "*Dynamic Slicing isolates the minimal set of executed code "
          "responsible for the observed behavior.*"
       << endl;
  //
}

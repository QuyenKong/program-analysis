#include <iostream>

using namespace std;

// --- PART 1: DATAFLOW ANALYSIS ILLUSTRATION ---
// Dataflow Analysis (DFA) is a technique for gathering information about the
// possible execution of a program at various points. The core idea is to
// compute a "property" that is propagated through the Control Flow. This
// example illustrates the idea of "Reaching Definitions" analysis.
void IllustrateDataflowAnalysis() {
  cout << "--- 1. DATAFLOW ANALYSIS ILLUSTRATION (Reaching Definitions) ---"
       << endl;

  // Assume we are tracking the definitions of variables 'x' and 'y'.

  // A definition (d) is an assignment statement.

  int x = 10; // d1: Definition 1 (x is defined as 10)
  // At this point, Reaching Definitions are: {d1}

  int y = 5; // d2: Definition 2 (y is defined as 5)
  // At this point, Reaching Definitions are: {d1, d2}

  if (y > 0) {
    x = x + 1; // d3: Definition 3 (x is redefined)
    // At this point (inside the if block), Reaching Definitions are: {d2, d3}
    // (d1 is killed because x is redefined)
  } else {
    y = y - 1; // d4: Definition 4 (y is redefined)
    // At this point (inside the else block), Reaching Definitions are: {d1, d4}
    // (d2 is killed because y is redefined)
  }

  // After the if/else block ends (Point P):
  // Reaching Definitions is the join of the definitions from both branches:
  // If branch: {d2, d3}
  // Else branch: {d1, d4}
  // Join: {d1, d2, d3, d4}
  // *The analysis indicates that at Point P, variable 'x' can come from d1 OR
  // d3, and variable 'y' can come from d2 OR d4.* This is the essence of DFA:
  // collecting sound approximation information at program points.
  cout << "Execution Result (cannot statically know if x came from d1 or d3): "
          "x = "
       << x << endl;
  //
}
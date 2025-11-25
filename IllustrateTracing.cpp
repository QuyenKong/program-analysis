#include <iostream>

using namespace std;

// --- PART 5: TRACING ILLUSTRATION ---
// Tracing records the sequence of executed instructions and their associated
// state (variable values) to reconstruct the program's execution history.
void IllustrateTracing() {
  cout << "\n--- 5. TRACING ILLUSTRATION ---" << endl;
  cout << "Simulating execution trace recording:" << endl;

  int a = 1; // Trace Event 1: a=1 (Line X)
  cout << "Event 1: Line X, a = " << a << endl;

  int b = 2; // Trace Event 2: b=2 (Line X+1)
  cout << "Event 2: Line X+1, b = " << b << endl;

  int sum = 0;

  for (int i = 0; i < 3; ++i) { // Trace Events (Loop iterations)
    sum += a;                   // Trace Event (Assignment)
    a++;                        // Trace Event (Mutation)
    // Note: A real trace records variable states at these points across loop
    // iterations.
  }

  cout << "Final trace event: Loop exit. Final sum = " << sum << endl;
  cout << "Final state: a = " << a << ", sum = " << sum << endl;
  cout << "*The collected trace is a sequential list of (Line, State) pairs "
          "allowing replay.*"
       << endl;
  //
}

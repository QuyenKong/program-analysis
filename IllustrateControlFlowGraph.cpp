#include <iostream>

using namespace std;

// --- PART 2: CONTROL FLOW GRAPH (CFG) ILLUSTRATION ---
// Control Flow Graph (CFG) is a diagram representing all possible paths
// the program may take during execution.
// Nodes are Basic Blocks of source code.
// Edges are control jumps or branches.
void IllustrateControlFlowGraph() {
  cout << "\n--- 2. CONTROL FLOW GRAPH (CFG) ILLUSTRATION ---" << endl;

  int input = 15;
  cout << "Input: " << input << endl;

  // Start (Entry Node) -> Node 1 (Basic Block 1)
  // Node 1: First Basic Block (no entry/exit jumps)
  int result = 0; // Statement A

  // Edge 1: Connects Node 1 to Node 2 (Condition Node)
  // Node 2: Decision Block
  if (input > 10) { // Condition B - Branch

    // Edge 2: From Node 2 to Node 3 (True Branch)
    // Node 3: Basic Block for 'True' case
    result = input * 2; // Statement C
    cout << "True Branch (Node 3): " << result << endl;

  } else if (input < 5) { // Condition D - Branch

    // Edge 3: From Node 2 to Node 4 (False branch of B, Condition D)
    // Node 4: Second Decision Block
    result = input + 1; // Statement E
    cout << "If Else Branch (Node 4): " << result << endl;

  } else {

    // Edge 4: From Node 4 to Node 5 (False branch of D)
    // Node 5: Basic Block for 'Else' case
    result = input; // Statement F
    cout << "Else Branch (Node 5): " << result << endl;
  }

  // Edges 5, 6, 7: Branches (from Node 3, 4, 5) all merge to Node 6
  // Node 6: Join Block
  cout << "Final Result (Node 6): " << result << endl;

  // End (Exit Node) -> Node 6

  // *CFG helps static analysis tools identify all possible control flows
  // and ensures that the analysis is applied to every possible path.*
  //
}
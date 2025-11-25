#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For setprecision in Part 8

// Language: C++
// Course: Principles and Techniques of Program Analysis (Static Program Analysis)

using namespace std;

// --- PART 1: DATAFLOW ANALYSIS ILLUSTRATION ---
// Dataflow Analysis (DFA) is a technique for gathering information about the possible
// execution of a program at various points. The core idea is to compute a "property"
// that is propagated through the Control Flow.
// This example illustrates the idea of "Reaching Definitions" analysis.
void IllustrateDataflowAnalysis() {
    cout << "--- 1. DATAFLOW ANALYSIS ILLUSTRATION (Reaching Definitions) ---" << endl;

    // Assume we are tracking the definitions of variables 'x' and 'y'.
    
    // A definition (d) is an assignment statement.

    int x = 10; // d1: Definition 1 (x is defined as 10)
    // At this point, Reaching Definitions are: {d1}

    int y = 5;  // d2: Definition 2 (y is defined as 5)
    // At this point, Reaching Definitions are: {d1, d2}

    if (y > 0) {
        x = x + 1; // d3: Definition 3 (x is redefined)
        // At this point (inside the if block), Reaching Definitions are: {d2, d3} (d1 is killed because x is redefined)
    } else {
        y = y - 1; // d4: Definition 4 (y is redefined)
        // At this point (inside the else block), Reaching Definitions are: {d1, d4} (d2 is killed because y is redefined)
    }

    // After the if/else block ends (Point P):
    // Reaching Definitions is the join of the definitions from both branches:
    // If branch: {d2, d3}
    // Else branch: {d1, d4}
    // Join: {d1, d2, d3, d4}
    // *The analysis indicates that at Point P, variable 'x' can come from d1 OR d3,
    // and variable 'y' can come from d2 OR d4.*
    // This is the essence of DFA: collecting sound approximation information at program points.
    cout << "Execution Result (cannot statically know if x came from d1 or d3): x = " << x << endl;
    // 
}

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

// --- PART 3: MEMORY ALLOCATION AND DEALLOCATION ILLUSTRATION ---
// Illustrates the difference between Stack (Static Memory) and Heap (Dynamic Memory) allocation.
void IllustrateMemoryAllocation() {
    cout << "\n--- 3. MEMORY ALLOCATION AND DEALLOCATION ILLUSTRATION ---" << endl;

    // 1. STACK Allocation (Static Memory)
    // Variables are allocated when the function is called and automatically deallocated when the function ends.
    int stackVariable = 100; // Allocated on Stack
    cout << "Stack: Variable 'stackVariable' = " << stackVariable << " (Automatically Deallocated)" << endl;
    
    // 2. HEAP Allocation (Dynamic Memory)
    // Requires using the 'new' operator and manual management (or Smart Pointers).
    // The size might not be known at compile time.
    
    // Allocating memory for an integer on the Heap
    int* heapPtr = new int(200); // Allocated on Heap (Dynamic Allocation)
    cout << "Heap: Allocated memory region value: " << *heapPtr << endl;
    
    // Deallocating Heap Memory
    // Without the 'delete' command, this memory would leak (memory leak).
    delete heapPtr; // Deallocating Heap memory
    heapPtr = nullptr; // Set pointer to NULL to prevent using a dangling pointer
    
    cout << "Heap: Allocated memory region has been deallocated. (Manual Management)" << endl;
    // [Image of Stack and Heap Memory Model]
}

// --- PART 4: POINTER USAGE AND DEALLOCATION ILLUSTRATION ---
// Illustrates how to use a Pointer and the importance of deallocation.
void IllustratePointerUsage() {
    cout << "\n--- 4. POINTER USAGE AND DEALLOCATION ILLUSTRATION ---" << endl;

    // 1. Basic Pointer Usage (Pointing to a Stack variable)
    int value = 42;
    int* ptrValue = &value; // Assign the address of 'value' to 'ptrValue'

    cout << "Value: " << value << endl;
    cout << "Address of Value (&value): " << &value << endl;
    cout << "Pointer Value (ptrValue): " << ptrValue << endl;
    cout << "Access via Pointer (*ptrValue): " << *ptrValue << endl;

    // Changing the value via Pointer
    *ptrValue = 99;
    cout << "New Value: " << value << endl;

    // 2. Using Pointer for Dynamic Memory (Heap) and Deallocation
    // This is where manual memory management becomes critical.
    int size = 5;
    int* dynamicArray = new int[size]; // Allocating an array of 5 elements on the Heap

    for (int i = 0; i < size; ++i) {
        dynamicArray[i] = (i + 1) * 10;
    }
    cout << "Dynamic Array on Heap: " << dynamicArray[0] << ", " << dynamicArray[4] << "..." << endl;

    // IMPORTANT: Deallocating the array memory allocated on the Heap
    // Must use 'delete[]' for arrays.
    delete[] dynamicArray;
    dynamicArray = nullptr; // Preventing dangling pointer usage error

    // Note: In modern C++, Smart Pointers (std::unique_ptr, std::shared_ptr) should be used
    // to automate memory deallocation and prevent leaks.
    // Example: auto modern_ptr = std::make_unique<int>(10);
    cout << "Dynamic array memory has been safely deallocated." << endl;
}

// --- PART 5: TRACING ILLUSTRATION ---
// Tracing records the sequence of executed instructions and their associated state (variable values)
// to reconstruct the program's execution history.
void IllustrateTracing() {
    cout << "\n--- 5. TRACING ILLUSTRATION ---" << endl;
    cout << "Simulating execution trace recording:" << endl;

    int a = 1; // Trace Event 1: a=1 (Line X)
    cout << "Event 1: Line X, a = " << a << endl;

    int b = 2; // Trace Event 2: b=2 (Line X+1)
    cout << "Event 2: Line X+1, b = " << b << endl;

    int sum = 0;

    for (int i = 0; i < 3; ++i) { // Trace Events (Loop iterations)
        sum += a; // Trace Event (Assignment)
        a++;      // Trace Event (Mutation)
        // Note: A real trace records variable states at these points across loop iterations.
    }

    cout << "Final trace event: Loop exit. Final sum = " << sum << endl;
    cout << "Final state: a = " << a << ", sum = " << sum << endl;
    cout << "*The collected trace is a sequential list of (Line, State) pairs allowing replay.*" << endl;
    // 
}

// --- PART 6: DYNAMIC SLICING ILLUSTRATION ---
// Dynamic Slicing computes the set of statements that actually affected the value of a variable
// at a specific point during a specific execution (the slice criterion).
void IllustrateDynamicSlicing() {
    cout << "\n--- 6. DYNAMIC SLICING ILLUSTRATION ---" << endl;

    int x = 10;   // Statement S1
    int y = 5;    // Statement S2
    int z = 0;    // Statement S3

    // Conditional statement (Control Dependency)
    if (x > y) {  // Statement S4
        z = x + 1; // Statement S5 (Executed)
    } else {
        z = y + 1; // Statement S6 (Skipped)
    }

    x = z * 2;    // Statement S7 (Slice Criterion Point)

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
    
    cout << "*Dynamic Slicing isolates the minimal set of executed code responsible for the observed behavior.*" << endl;
    // 
}

// --- PART 7: EXECUTION INDEXING ILLUSTRATION ---
// Execution Indexing assigns a unique, totally ordered identifier (index or timestamp)
// to every event (instruction, variable access) in a specific program run.
void IllustrateExecutionIndexing() {
    cout << "\n--- 7. EXECUTION INDEXING ILLUSTRATION ---" << endl;

    struct TraceEvent {
        int index;
        string description;
    };
    
    vector<TraceEvent> trace;
    int indexCounter = 1;

    // Simulate instructions and assign indices
    trace.push_back({indexCounter++, "Initialize i = 0"});
    int i = 0;
    
    // Loop execution generates multiple uniquely indexed events
    while (i < 2) { 
        trace.push_back({indexCounter++, "Check condition i < 2 (True)"});
        i++;
        trace.push_back({indexCounter++, "Increment i"});
    }
    trace.push_back({indexCounter++, "Check condition i < 2 (False)"});
    
    cout << "Simulated Trace Events (Index, Description):" << endl;
    for (const auto& event : trace) {
        cout << "  [" << event.index << "] " << event.description << endl;
    }
    
    // The index allows deterministic navigation and dependency tracking.
    cout << "*Execution indexing enables precise 'time travel' and causal analysis in debugging.*" << endl;
    // 
}


// --- PART 8: FAULT LOCALIZATION ILLUSTRATION ---
// Fault Localization identifies the suspicious parts of code that are most likely
// responsible for a failure, often by comparing the execution coverage of passing vs. failing tests.
void IllustrateFaultLocalization() {
    cout << "\n--- 8. FAULT LOCALIZATION ILLUSTRATION ---" << endl;

    // Simulate coverage data for 4 code blocks (B1: Initial, B2: Error-prone, B3: Safe, B4: Final)
    // T1: PASS (1 passing test)
    // T2, T3: FAIL (2 failing tests)
    
    // Coverage Data: 1 if block was executed, 0 otherwise.

    cout << "Test Results and Block Coverage (0=Skipped, 1=Executed):" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Test | Result | B1 (Init) | B2 (Faulty) | B3 (Safe) | B4 (Output) |" << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "T1   | PASS   |     1     |      0      |     1     |      1      |" << endl;
    cout << "T2   | FAIL   |     1     |      1      |     0     |      1      |" << endl;
    cout << "T3   | FAIL   |     1     |      1      |     1     |      1      |" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    // Simplified Fault Localization Logic (e.g., Ochiai coefficient):
    // Suspiciousness (B) = (Failing tests covering B) / sqrt(Total Failing tests * Total tests covering B)
    
    // Total Failing Tests (F): 2 (T2, T3)
    // Total Passing Tests (P): 1 (T1)

    // B2: Executed by F=2, Executed by P=0. Total coverage=2. Suspiciousness = 2 / sqrt(2 * 2) = 1.0
    // B3: Executed by F=1 (T3), Executed by P=1 (T1). Total coverage=2. Suspiciousness = 1 / sqrt(2 * 2) = 0.5
    
    cout << fixed << setprecision(2);
    cout << "\nAnalysis Conclusion (based on coverage comparison):" << endl;
    cout << "Block B2 (Faulty) Suspiciousness Score: 1.00" << endl;
    cout << "Block B3 (Safe) Suspiciousness Score: 0.50" << endl;
    cout << "Block B2 was executed by ALL failing tests but NO passing tests (T1)." << endl;
    cout << "*Fault Localization ranks B2 as the most likely location of the fault.*" << endl;
    // 
}

int main() {
    // Call illustration functions from the previous questions
    IllustrateDataflowAnalysis();
    IllustrateControlFlowGraph();
    IllustrateMemoryAllocation();
    IllustratePointerUsage();

    // Call illustration functions for the new questions (Dynamic Analysis)
    IllustrateTracing();
    IllustrateDynamicSlicing();
    IllustrateExecutionIndexing();
    IllustrateFaultLocalization();

    return 0;
}
#include <iostream>

using namespace std;

// --- PART 3: MEMORY ALLOCATION AND DEALLOCATION ILLUSTRATION ---
// Illustrates the difference between Stack (Static Memory) and Heap (Dynamic
// Memory) allocation.
void IllustrateMemoryAllocation() {
  cout << "\n--- 3. MEMORY ALLOCATION AND DEALLOCATION ILLUSTRATION ---"
       << endl;

  // 1. STACK Allocation (Static Memory)
  // Variables are allocated when the function is called and automatically
  // deallocated when the function ends.
  int stackVariable = 100; // Allocated on Stack
  cout << "Stack: Variable 'stackVariable' = " << stackVariable
       << " (Automatically Deallocated)" << endl;

  // 2. HEAP Allocation (Dynamic Memory)
  // Requires using the 'new' operator and manual management (or Smart
  // Pointers). The size might not be known at compile time.

  // Allocating memory for an integer on the Heap
  int *heapPtr = new int(200); // Allocated on Heap (Dynamic Allocation)
  cout << "Heap: Allocated memory region value: " << *heapPtr << endl;

  // Deallocating Heap Memory
  // Without the 'delete' command, this memory would leak (memory leak).
  delete heapPtr;    // Deallocating Heap memory
  heapPtr = nullptr; // Set pointer to NULL to prevent using a dangling pointer

  cout << "Heap: Allocated memory region has been deallocated. (Manual "
          "Management)"
       << endl;
  // [Image of Stack and Heap Memory Model]
}
int main() {
    // Call illustration functions from the previous questions
    IllustrateMemoryAllocation();

    return 0;
}
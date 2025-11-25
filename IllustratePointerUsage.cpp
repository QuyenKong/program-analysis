#include <iostream>

using namespace std;

// --- PART 4: POINTER USAGE AND DEALLOCATION ILLUSTRATION ---
// Illustrates how to use a Pointer and the importance of deallocation.
void IllustratePointerUsage() {
  cout << "\n--- 4. POINTER USAGE AND DEALLOCATION ILLUSTRATION ---" << endl;

  // 1. Basic Pointer Usage (Pointing to a Stack variable)
  int value = 42;
  int *ptrValue = &value; // Assign the address of 'value' to 'ptrValue'

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
  int *dynamicArray =
      new int[size]; // Allocating an array of 5 elements on the Heap

  for (int i = 0; i < size; ++i) {
    dynamicArray[i] = (i + 1) * 10;
  }
  cout << "Dynamic Array on Heap: " << dynamicArray[0] << ", "
       << dynamicArray[4] << "..." << endl;

  // IMPORTANT: Deallocating the array memory allocated on the Heap
  // Must use 'delete[]' for arrays.
  delete[] dynamicArray;
  dynamicArray = nullptr; // Preventing dangling pointer usage error

  // Note: In modern C++, Smart Pointers (std::unique_ptr, std::shared_ptr)
  // should be used to automate memory deallocation and prevent leaks. Example:
  // auto modern_ptr = std::make_unique<int>(10);
  cout << "Dynamic array memory has been safely deallocated." << endl;
}
int main() {
    // Call illustration functions from the previous questions
    IllustratePointerUsage();

    return 0;
}
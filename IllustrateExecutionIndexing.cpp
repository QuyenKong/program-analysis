#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- PART 7: EXECUTION INDEXING ILLUSTRATION ---
// Execution Indexing assigns a unique, totally ordered identifier (index or
// timestamp) to every event (instruction, variable access) in a specific
// program run.
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
  for (const auto &event : trace) {
    cout << "  [" << event.index << "] " << event.description << endl;
  }

  // The index allows deterministic navigation and dependency tracking.
  cout << "*Execution indexing enables precise 'time travel' and causal "
          "analysis in debugging.*"
       << endl;
  //
}
int main() {
    IllustrateExecutionIndexing();

    return 0;
}
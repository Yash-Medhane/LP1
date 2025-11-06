#include <iostream>
#include <vector>
#include <numeric>  // for accumulate()
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
using namespace std;

int main() {
    int numProcesses = 5;
    int coordinator = 0;
    vector<int> processTimes(numProcesses);

    // Step 1: Assign random local times to all processes
    srand(time(0));
    cout << "Initial clock times of processes:\n";
    for (int i = 0; i < numProcesses; i++) {
        processTimes[i] = rand() % 100; // Random time between 0–99
        cout << "Process " << i << " -> Time: " << processTimes[i] << endl;
    }

    // Step 2: Coordinator collects all times
    cout << "\nCoordinator (Process " << coordinator << ") collects all times.\n";

    // Step 3: Calculate average time
    int total = accumulate(processTimes.begin(), processTimes.end(), 0);
    int average = total / numProcesses;

    cout << "\nAverage (synchronized) time calculated by coordinator: " << average << endl;

    // Step 4: Coordinator sends average time to all processes
    cout << "\nCoordinator sends synchronized time to all processes.\n";

    // Step 5: Each process adjusts its clock
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << i << " adjusts its clock from "
             << processTimes[i] << " -> " << average << endl;
        processTimes[i] = average;
    }

    // Step 6: Display final synchronized times
    cout << "\nFinal clock times after synchronization:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << i << " -> Time: " << processTimes[i] << endl;
    }

    return 0;
}

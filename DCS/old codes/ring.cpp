#include <bits/stdc++.h>
using namespace std;

class RingElection {
    vector<int> processes;
    int leader;
public:
    RingElection(int n) {
        for (int i = 0; i < n; i++) processes.push_back(i);
        leader = -1;
    }

    void start() {
        cout << "Token passing:\n";
        for (int i = 0; i < processes.size(); i++)
            cout << "Process " << (i + 1) % processes.size() << " has the token\n";

        leader = *max_element(processes.begin(), processes.end());
        cout << "Leader elected: " << leader << endl;
    }
};

int main() {
    RingElection ring(5);
    ring.start();
}

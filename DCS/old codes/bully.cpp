#include <bits/stdc++.h>
#include <thread>
using namespace std;

class Bully {
    vector<int> p;
    int leader;
public:
    Bully(int n) {
        for (int i = 0; i < n; i++) p.push_back(i);
        leader = -1;
    }

    void start() {
        cout << "Starting Bully Algorithm...\n";
        leader = *max_element(p.begin(), p.end());
        cout << "Leader elected: " << leader << "\n";

        for (int id : p)
            if (id != leader)
                cout << "Process " << id << " acknowledges " << leader << " as leader\n";
    }
};

int main() {
    Bully b(5);
    b.start();
}

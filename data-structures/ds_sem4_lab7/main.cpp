#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    int order;
    int timeToComplete;
    int penalty;
};

bool compareJobsGreater(const Job& a, const Job& b) {
    double ratioA = (double)a.penalty / a.timeToComplete;
    double ratioB = (double)b.penalty / b.timeToComplete;
    if (ratioA == ratioB) {
        return a.order < b.order; // sort by order if equals
    }
    return ratioA > ratioB;
}

int main() {
    int n;
    while (cin >> n) {
        vector<Job> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i].order = i + 1;
            cin >> jobs[i].timeToComplete >> jobs[i].penalty;
        }

        // sort DESC by S/T (penalty/time)
        sort(jobs.begin(), jobs.end(), compareJobsGreater);

        for (int i = 0; i < n; ++i) {
            if (i > 0) cout << " ";
            cout << jobs[i].order;
        }
        cout << endl;
    }

    return 0;
}

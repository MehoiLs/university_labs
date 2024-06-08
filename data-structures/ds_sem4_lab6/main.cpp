#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

static unordered_map<int, int> memo;

bool memoContains(int num) {
    return memo.find(num) != memo.end();
}

int calculateJoy(int n, int k) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        int power = 1;
        for (int i = 0; i < k; ++i) {
            power *= digit;
        }
        sum += power;
        n /= 10;
    }
    return sum;
}

int performCalculations(int number, int degree) {
    if (memoContains(number)) {
        return memo[number];
    }

    unordered_set<int> visited; // for managing cycles
    vector<int> sequence; // n, S(n), S(S(n)), ...
    int current = number;
    while (visited.find(current) == visited.end()) { // if cycle is found
        visited.insert(current);
        sequence.push_back(current);

        current = calculateJoy(current, degree);
    }

    int minJoy = current;
    for (const auto& num : sequence) {
        minJoy = min(minJoy, num);
    }
    memo[number] = minJoy;
    return minJoy;
}

int main() {
    int a, b, k;
    while (cin >> a >> b >> k) {
        if (a == b == k == 0) { // 0 0 0 for exiting program
            break;
        }
        long long sumJoy = 0;
        for (int i = a; i <= b; ++i) {
            sumJoy += performCalculations(i, k);
        }
        cout << sumJoy << endl;
    }
    return 0;
}

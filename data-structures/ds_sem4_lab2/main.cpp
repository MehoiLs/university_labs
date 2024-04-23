#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int countNumbers(int m, const vector<int>& numbers) {
    int result = m;

    for (int i = 1; i < (1 << numbers.size()); ++i) {
        int sign = (i % 2 == 1) ? 1 : -1;
        int lcm = 1;
        for (int j = 0; j < numbers.size(); ++j) {
            if (i & (1 << j)) {
                lcm = (lcm  / gcd(lcm, numbers[j])) * numbers[j];
            }
        }
        result += sign * (m / lcm);
    }
    return result;
}

int main() {
    int m, k;
    cout << "Enter m: ";
    cin >> m;
    cout << "Enter k: ";
    cin >> k;
    vector<int> numbers(k);
    cout << "Enter " << k << " numbers: ";
    for (int i = 0; i < k; ++i) {
        cin >> numbers[i];
    }
    int result = countNumbers(m, numbers);
    cout << "Result: " << result << endl;

    return 0;
}

/**
 * Написать программу для формулы включения и исключения. С её помощью определить количество
 * натуральных чисел меньше или равных m, не делящихся ни на одно из заданных k чисел n_1, n_2, ..., n_k.
 * */
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <map>
#include <cmath>

using std::map;

static map<int, int> numberToJoy;

int calculateJoy(int number, int degree) {
    int sum = 0;
    while (number > 0) {
        auto digit = number % 10;
        sum += pow(digit, degree);
        number /= 10;
    }
    numberToJoy[number] = sum;
    return sum;
}

int foo(const int targetNum, const int degree) {
    if (numberToJoy[targetNum] != 0) {
        return numberToJoy[targetNum]; // immediately return if we have already calculated this number
    }
    // TODO finish the task, perform comparison, etc...
}

void performCalculations(int borderLeft, int borderRight, int degree) {
    int sum = 0;
    for (int num = borderLeft; num <= borderRight; num++) {
        sum += foo(num, degree);
    }
    cout << sum << endl;
}

int main() {
    int borderLeft, borderRight, degree;
    int entriesCount;

    cout << "Please, enter the number of entries: ";
    cin >> entriesCount;

    while (entriesCount--) {
        cout << "Please, enter the left border, right border and the degree: ";
        bool isInputValid = false;
        while(!isInputValid) {
            cin >> borderLeft >> borderRight >> degree;
            if (borderLeft < 0 || borderRight < 0 || degree < 0) {
                cerr << "All numbers must be positive!\n";
                continue;
            }
            if (borderLeft > borderRight) {
                cerr << "Left border must be less than right border!\n";
                continue;
            }
            if (degree < 2) {
                cerr << "Degree must be greater than 1!\n";
                continue;
            }
            isInputValid = true;
        }
        performCalculations(borderLeft, borderRight, degree);
    }

    return 0;
}
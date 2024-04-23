#ifndef DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H
#define DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H

#include <cassert>
#include <iostream>
#include <vector>
#include "../InclusionExclusionCalculator.h"

using std::cout;
using std::cerr;
using std::vector;

class TestInclusionExclusionCalculator {
private:

    static void handleAssertion(
            const bool isPassed,
            const int expected,
            const int actual,
            const int lineAt,
            const string& testName = ""
    ) {
        if (!isPassed) {
            cerr << "Test " << testName << " FAILED at line: " << lineAt << " \n";
            cerr << " Expected: <" << expected << ">, actual: <" << actual << ">\n\n";
        }
    }

    static void performAssertCountNumbers(
            const int m,
            const vector<int>& numbers,
            const int expected,
            const int lineAt,
            const string& testName = ""
    ) {
        auto actual = InclusionExclusionCalculator::performComparison(m, numbers);
        auto isPassed = (actual == expected);
        handleAssertion(isPassed, expected, actual, lineAt, testName);
    }

    static void testCountNumbers() {
        static const string TEST_NAME = "\"testCountNumbers\"";

        performAssertCountNumbers(30, {2, 3, 5}, 8, __LINE__, TEST_NAME);
        performAssertCountNumbers(20, {3, 5}, 11, __LINE__, TEST_NAME);
    }

public:
    static void runTests() {
        testCountNumbers();
        cout << "\nFINISHED TESTING." << std::endl;
    }
};


#endif //DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H

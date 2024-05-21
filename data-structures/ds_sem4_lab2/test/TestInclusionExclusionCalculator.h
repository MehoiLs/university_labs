#ifndef DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H
#define DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H

#include <cassert>
#include <iostream>
#include <vector>
#include "../InclusionExclusionCalculator.h"

using std::cout;
using std::cerr;
using std::vector;

/**
 * Тестирование класса `InclusionExclusionCalculator`
 *
 * @author MehoiLs (Dorokhov Mikhail)
 * */
class TestInclusionExclusionCalculator {
private:

    /**
     * Обработка assertion, вывод результата отдельной части теста, где был вызван `performAssert`.
     *
     * @param isPassed - результат проверки
     * @param expected - ожидаемое значение
     * @param actual - фактическое значение
     * @param lineAt - номер строки, где был вызван `performAssert`
     * @param testName - имя теста
     */
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

    /**
     * Выполнение assertion для метода `performComparison` класса `InclusionExclusionCalculator`.
     *
     * @param m - число, с которым производится сравнение
     * @param numbers - вектор делителей
     * @param expected - ожидаемое значение
     * @param lineAt - номер строки, где был вызван `performAssert`
     * @param testName - имя теста
     */
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

    /**
     * Тестирование метода `performComparison`
     */
    static void testCountNumbers() {
        static const string TEST_NAME = "\"testCountNumbers\"";

        performAssertCountNumbers(30, {2, 3, 5}, 8, __LINE__, TEST_NAME);
        performAssertCountNumbers(20, {3, 5}, 11, __LINE__, TEST_NAME);
    }

public:
    /**
     * Запуск всех тестов
     */
    static void runTests() {
        testCountNumbers();
        cout << "\nFINISHED TESTING." << std::endl;
    }
};


#endif //DS_SEM4_LAB2_TESTINCLUSIONEXCLUSIONCALCULATOR_H

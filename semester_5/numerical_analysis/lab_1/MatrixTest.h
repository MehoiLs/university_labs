#ifndef MATRIXTEST_H
#define MATRIXTEST_H
#include <list>
#include <map>

#include "Matrix.h"
#include "MatrixUtil.h"

#define EPS 1.0E-9

struct SubTestEntry {
    ldouble relativeError;
    ldouble accuracyEstimate;

    explicit SubTestEntry(const ldouble relativeError, const ldouble accuracyEstimate)
        : relativeError(relativeError), accuracyEstimate(accuracyEstimate) {}
};

struct TestEntry {
    int num;
    int size;
    ldouble bounds;
    ldouble avgRelativeError;
    ldouble avgAccuracyEstimate;

    explicit TestEntry(const int num, const int size, const ldouble bounds): num(num), size(size), bounds(bounds),
        avgRelativeError(0), avgAccuracyEstimate(0) {
        if (num < 1) {
            throw std::invalid_argument("num must be bigger than 0");
        }
    }
};

constexpr int SUB_TESTS_COUNT = 10;

class MatrixTest {
    public:


    static void performDefaultTests() {
        std::list<TestEntry> allEntries;
        int testNum = 1;

        // Test 1
        auto entry1 = performTest(testNum++, SUB_TESTS_COUNT, 10, 10);
        allEntries.insert(allEntries.end(), entry1);

        // Test 2
        auto entry2 = performTest(testNum++, SUB_TESTS_COUNT, 10, 100);
        allEntries.insert(allEntries.end(), entry2);

        // Test 3
        auto entry3 = performTest(testNum++, SUB_TESTS_COUNT, 10, 1000);
        allEntries.insert(allEntries.end(), entry3);

        // Test 4
        auto entry4 = performTest(testNum++, SUB_TESTS_COUNT, 100, 10);
        allEntries.insert(allEntries.end(), entry4);

        // Test 5
        auto entry5 = performTest(testNum++, SUB_TESTS_COUNT, 100, 100);
        allEntries.insert(allEntries.end(), entry5);

        // Test 6
        auto entry6 = performTest(testNum++, SUB_TESTS_COUNT, 100, 1000);
        allEntries.insert(allEntries.end(), entry6);

        // Test 7
        auto entry7 = performTest(testNum++, SUB_TESTS_COUNT, 1000, 10);
        allEntries.insert(allEntries.end(), entry7);

        // Test 8
        auto entry8 = performTest(testNum++, SUB_TESTS_COUNT, 1000, 100);
        allEntries.insert(allEntries.end(), entry8);

        // Test 9
        auto entry9 = performTest(testNum++, SUB_TESTS_COUNT, 1000, 1000);
        allEntries.insert(allEntries.end(), entry9);

        printTestEntries(allEntries);
    }

    static TestEntry performTest(const int testNum, const int subTestsCount, const int size, const ldouble bounds) {
        auto entry = TestEntry(testNum, size, bounds);
        std::list<SubTestEntry> subEntries;
        for (int i = 0; i < subTestsCount; i++) {
            const auto matrix = MatrixUtil::generateRandomCalculatingF(size, bounds);
            const auto coefMatrix = new Matrix(*matrix);
            coefMatrix->multipleByCoefs(MatrixUtil::generateRandomVector(size, bounds));

            const auto solution = matrix->solve();
            const auto coefSolution = coefMatrix->solve();

            const auto relativeError = calcRelativeError(coefSolution, solution);
            const auto accuracyEstimate = calcAccuracyEstimate(solution);
            const auto subEntry = SubTestEntry(relativeError, accuracyEstimate);
            subEntries.insert(subEntries.end(), subEntry);
            //
            // printVector(coefSolution);
            // std::cout << std::endl << std::endl;
            // printVector(solution);
            // std::cout << std::endl << std::endl;
        }
        collapseSubEntries(entry, subEntries);
        return entry;
    }

    static ldouble calcAccuracyEstimate(const matrixVector& solution) {
        ldouble diff = 0;
        for (const auto s : solution) {
            diff = std::max(diff, std::abs(s - 1));
        }
        return diff;
    }

    static ldouble calcRelativeError(const matrixVector& coefVector, const matrixVector& solution) {
        if (coefVector.size() != solution.size()) {
            throw std::invalid_argument("vectors size mismatch");
        }

        ldouble diff = 0;
        for (auto i = 0; i < solution.size(); i++) {
            if (std::abs(coefVector[i]) > EPS) {
                diff = std::max(diff, std::abs((solution[i] - coefVector[i]) / coefVector[i]));
            } else {
                diff = std::max(diff, std::abs(solution[i] - coefVector[i]));
            }
        }
        return diff;
    }

    static void collapseSubEntries(TestEntry& collapseTo, std::list<SubTestEntry> subEntries) {
        collapseTo.avgRelativeError = 0.0;
        collapseTo.avgAccuracyEstimate = 0.0;

        for (const auto entry : subEntries) {
            collapseTo.avgAccuracyEstimate += entry.accuracyEstimate;
            collapseTo.avgRelativeError += entry.relativeError;
        }

        collapseTo.avgAccuracyEstimate /= subEntries.size();
        collapseTo.avgRelativeError /= subEntries.size();
    }

    static void printVector(const matrixVector& vec) {
        for (const auto v : vec) {
            std::cout << v << " ";
        }
    }

    static void printTestEntries(const std::list<TestEntry>& entries) {
        std::cout << " #\t|\tSIZE\t|\tBOUNDS\t|\tAVG RELATIVE ERROR\t|\tAVG ACCURACY ESTIMATE\t\n";
        for (const auto e : entries) {
            std::cout << " " << e.num << "\t|\t " << e.size << "\t|\t" << e.bounds << "\t|\t   "
                << e.avgRelativeError << "     \t|\t  " << e.avgAccuracyEstimate << "\t\n";
        }
    }

};

#endif //MATRIXTEST_H

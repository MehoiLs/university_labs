#ifndef MATRIXTEST_H
#define MATRIXTEST_H
#include <list>
#include <map>
#include <thread>

#include "Matrix.h"
#include "MatrixUtil.h"

#define EPS 1.0E-9

#define FREEZE_PRINT std::this_thread::sleep_for(std::chrono::milliseconds(200))

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

class MatrixTest final {
    private:

    static TestEntry performTestLoggingFirst(const int testNum, const int subTestsCount, const int size, const ldouble bounds) {

        std::list<SubTestEntry> subEntries;
        auto entry = TestEntry(testNum, size, bounds);

        {
            std::cerr << "\tGenerating a random matrix...\n\n";
            FREEZE_PRINT;
            const auto matrix = MatrixUtil::generateRandomCalculatingF(size, bounds);
            matrix->print();
            FREEZE_PRINT;

            std::cerr << "\n\tMatrix as vectors: \n";
            FREEZE_PRINT;
            matrix->printAsVectors();
            std::cout << std::endl;

            FREEZE_PRINT;
            std::cerr << "\n\tCopying a matrix & multiplying it by a random vector...\n\n";
            FREEZE_PRINT;
            const auto coefMatrix = new Matrix(*matrix);
            const auto coefVector = MatrixUtil::generateRandomVector(size, bounds);
            coefMatrix->multipleByCoefs(coefVector);
            coefMatrix->print();
            FREEZE_PRINT;

            std::cerr << "\n\tThe 'x' vector:\n";
            std::cout << "x = ";
            FREEZE_PRINT;
            for (const auto x : coefVector) {
                std::cout << x << "  ";
            }

            std::cerr << "\n\n\tCopied matrix as vectors: \n";
            FREEZE_PRINT;
            coefMatrix->printAsVectors();
            std::cout << std::endl;

            FREEZE_PRINT;
            std::cerr << "\n\tSolving the initial matrix...\n\n";
            FREEZE_PRINT;
            const auto solution = matrix->solveLogging();

            FREEZE_PRINT;
            std::cerr << "\tSolving the multiplied matrix...\n\n";
            FREEZE_PRINT;
            const auto coefSolution = coefMatrix->solveLogging();

            FREEZE_PRINT;
            std::cerr << "\tCalculating the relative error & accuracy estimate...\n\n";
            const auto relativeError = calcRelativeError(coefSolution, solution);
            const auto accuracyEstimate = calcAccuracyEstimate(solution);

            std::cerr << "Relative error:\t\t "<< relativeError << std::endl;
            std::cerr << "Accuracy estimate:\t " << accuracyEstimate << std::endl << std::endl;

            const auto subEntry = SubTestEntry(relativeError, accuracyEstimate);
            subEntries.insert(subEntries.end(), subEntry);
        }

        for (int i = 1; i < subTestsCount; i++) {
            const auto matrix = MatrixUtil::generateRandomCalculatingF(size, bounds);
            const auto coefMatrix = new Matrix(*matrix);
            coefMatrix->multipleByCoefs(MatrixUtil::generateRandomVector(size, bounds));

            const auto solution = matrix->solve();
            const auto coefSolution = coefMatrix->solve();

            const auto relativeError = calcRelativeError(coefSolution, solution);
            const auto accuracyEstimate = calcAccuracyEstimate(solution);
            const auto subEntry = SubTestEntry(relativeError, accuracyEstimate);
            subEntries.insert(subEntries.end(), subEntry);
        }
        collapseSubEntries(entry, subEntries);
        return entry;
    }

    static TestEntry performTest(const int testNum, const int subTestsCount, const int size, const ldouble bounds) {
        std::list<SubTestEntry> subEntries;
        auto entry = TestEntry(testNum, size, bounds);
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
        }
        collapseSubEntries(entry, subEntries);
        return entry;
    }

public:
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
            std::cout << " " << e.num << "\t|\t " << e.size << "\t|\t" << e.bounds << "\t|\t    "
                << e.avgRelativeError << "     \t|\t  " << e.avgAccuracyEstimate << "\t\n";
        }
    }

public:
    
    static void performDefaultTests() {
        std::list<TestEntry> allEntries;
        int testNum = 1;

        // Test 1
        auto entry1 = performTest(testNum++, SUB_TESTS_COUNT, 10, 10);
        allEntries.insert(allEntries.end(), entry1);

        //todo
        //  Test 2
        auto entry2 = performTestLoggingFirst(testNum++, SUB_TESTS_COUNT, 10, 100);
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


};

#endif //MATRIXTEST_H

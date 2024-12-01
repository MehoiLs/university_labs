#ifndef MATRIXTEST_H
#define MATRIXTEST_H
#include "Matrix.h"

struct TestEntry {
    Matrix initialMatrix;
    matrixVector matrixSolution;
};

class MatrixTest {
    public:

    static void performDefaultTests() {

        const int SIZE_TEST_10 = 10;
        for (int i = 0; i < 10; i++) {
            const auto matrix = Matrix::generateRandom(SIZE_TEST_10);
            auto solutionBySum = matrix->calculateVectorF();
            auto solutionByAlgorithm = matrix->solveWithLogging();
            printTwoVectorsAsColumns(solutionBySum, solutionByAlgorithm);
        }

    }

    static void printTwoVectorsAsColumns(const matrixVector &a, const matrixVector &b) {
        for (int i = 0; i < std::min(a.size(), b.size()); i++) {
            std::cout << a[i] << "\t" << b[i] << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif //MATRIXTEST_H

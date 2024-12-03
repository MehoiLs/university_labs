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

        const int SIZE_TEST_10 = 1000;
        for (int i = 0; i < 10; i++) {
            const auto matrix = Matrix::generateRandomCalculatingF(SIZE_TEST_10);
            const auto solution = matrix->solve();
            printVector(solution);
        }

    }

    static void printVector(const matrixVector& vec) {
        for (const auto v : vec) {
            std::cout << v << " ";
        }
    }

    // TODO: посчитать для кажд тестов 10 оцен точ, разделить на 10 (найти среднее) => добавить в отчет
    // оценка точности для конкр матрицы
    static ldouble calc(const matrixVector& solution) {
        ldouble diff = 0;
        for (const auto s : solution) {
            diff = std::max(diff, std::abs(s - 1));
        }
        return diff;
    }

};

#endif //MATRIXTEST_H

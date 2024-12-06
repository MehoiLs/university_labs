#include <iostream>

#include "Matrix.h"
#include "MatrixTest.h"

int main()
{
    const auto path = R"(C:\Users\MehoiL\Documents\GitHub\university_labs\semester_5\numerical_analysis\lab_1\matrix.txt)";

    // TODO: см. calcAccuracyEstimate()

    // TODO: вывод одного рандомного теста: исходной и решенной матрицы (дробная), вектор x-ов, все другие вектора (a, b..) и остальное (ПОЛНЫЙ ВЫВОД)
    //  и доделать отчёт!

    
    std::cout << "1 - from file; 2 - perform the tests; e - exit\n";
    char command;
    while (std::cin >> command && command != 'e') {
        switch (command) {
            case '1': {
                const auto matrix = MatrixUtil::fromFile(path, false);
                const auto f = matrix->getF();
                std::cout << "INITIAL MATRIX: " << std::endl << std::endl;
                matrix->print();
                const auto solution = matrix->solve();
                std::cout << "SOLVED MATRIX: " << std::endl << std::endl;
                std::cout << "Оценка точности: " << MatrixTest::calcAccuracyEstimate(solution)<< std::endl;
                // std::cout << "Оценка точности: " << MatrixTest::calcRelativeError(f, solution);
                matrix->print();
                break;
            }
            case '2': {
                MatrixTest::performDefaultTests();
                break;
            }
            case 'e': break;
            default: {
                std::cerr << "Invalid command\n";
                break;
            }
        }
    
    }

    return 0;
}

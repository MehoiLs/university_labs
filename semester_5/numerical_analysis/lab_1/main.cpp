#include <iostream>

#include "Matrix.h"
#include "MatrixTest.h"

int main()
{
    const auto path = R"(C:\Users\mehoil\Documents\GitHub\university_labs\semester_5\numerical_analysis\lab_1\matrix.txt)";

    // const auto matrix = Matrix::fromFile(path, true);
    // const auto matrix = Matrix::generateRandom(12);
    // matrix->solveWithLogging();

    MatrixTest::performDefaultTests();

    return 0;
}

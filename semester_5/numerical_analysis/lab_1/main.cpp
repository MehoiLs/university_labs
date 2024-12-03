#include <iostream>

#include "Matrix.h"
#include "MatrixTest.h"

int main()
{
    const auto path = R"(C:\Users\mehoil\Documents\GitHub\university_labs\semester_5\numerical_analysis\lab_1\matrix.txt)";

    // const auto matrix = Matrix::fromFile(path, true);
    // matrix->solveWithLogging();

    // TODO: ЧМ: перенести тест из мудла (слева рабочий стол) в прогу!

    MatrixTest::performDefaultTests();


    return 0;
}

#include <iostream>

#include "Matrix.h"

int main()
{
    const auto path = R"(C:\Users\mehoil\Documents\GitHub\university_labs\semester_5\numerical_analysis\lab_1\matrix.txt)";
    const auto matrix = Matrix::fromFile(path);
    matrix->print();
    return 0;
}

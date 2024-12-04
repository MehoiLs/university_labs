#include <iostream>

#include "Matrix.h"
#include "MatrixTest.h"

int main()
{
    const auto path = R"(C:\Users\MehoiL\Documents\GitHub\university_labs\semester_5\numerical_analysis\lab_1\matrix.txt)";

    std::cout << "1 - from file; 2 - perform the tests; e - exit\n";
    char command;
    while (std::cin >> command && command != 'e') {
        switch (command) {
            case '1': {
                const auto matrix = MatrixUtil::fromFile(path, true);
                std::cout << "INITIAL MATRIX: " << std::endl << std::endl;
                matrix->print();
                matrix->solve();
                std::cout << "SOLVED MATRIX: " << std::endl << std::endl;
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

#ifndef MATRIX_H
#define MATRIX_H

#define ldouble long double
#define matrixVector std::vector<ldouble>

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>

class Matrix {
    private:

    const size_t size, k;
    matrixVector a, b, c, p, q;
    matrixVector f;

    public:

    Matrix(
        const size_t size,
        const size_t k,
        const matrixVector& a,
        const matrixVector& b,
        const matrixVector& c,
        const matrixVector& p,
        const matrixVector& q,
        const matrixVector& f
    ) : size(size), k(k), a(a), b(b), c(c), p(p), q(q), f(f) {
        if (size <= 1) {
            throw std::invalid_argument("Matrix size must be greater than 1");
        }
    }

    void solve() {

    }

    void normalizeMainDiagonal() {
        for (auto i = 0; i < size; i++) {
            auto coef = b[i];

            // b & q - always match by indeces
            b[i] /= coef;
            q[i] /= coef;

            // a & c - always smaller than b by one index
            if (i < size - 2) {
                if (i - 1 >= 0) {
                    // index of 'a' is always (b - 1)
                    a[i] /= coef;
                }
                c[i] /= coef;
            }
            // if 'i' matches with 'k' then it's 'p' => must divide the whole row
            if (k - 1 == i) {
                for (auto ip = 0; ip < size; ip++) {
                    p[i] /= coef;
                }
            }

        }
    }

    static Matrix *fromFile(const std::string &filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            throw std::runtime_error("Error while opening the file: " + filename);
        }

        size_t n = 0;
        size_t k = 0;
        matrixVector a, b, c, p, q, f;

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream inputStream(line);
            std::string key;
            inputStream >> key;
            key = key.substr(0, key.find('='));

            std::string inputNoKey = inputStream.str().substr(2, inputStream.str().size() - 1);
            std::istringstream valueStream(inputNoKey);

            if (key == "n") {
                n = static_cast<size_t>(std::stoi(valueStream.str()));
            } else if (key == "k") {
                k = static_cast<size_t>(std::stoi(valueStream.str()));
            } else if (key == "a" || key == "b" || key == "c" || key == "p" || key == "q" || key == "f") {
                matrixVector vector;
                ldouble vectorValue;
                while (valueStream >> vectorValue) {
                    vector.push_back(vectorValue);
                }
                switch (key[0]) {
                    case 'a': a = std::move(vector); break;
                    case 'b': b = std::move(vector); break;
                    case 'c': c = std::move(vector); break;
                    case 'p': p = std::move(vector); break;
                    case 'q': q = std::move(vector); break;
                    case 'f': f = std::move(vector); break;
                    default: throw std::invalid_argument("Unknown key: " + key);
                }
            }
        }

        inputFile.close();

        if (a.size() != n || b.size() != n || c.size() != n || p.size() != n || q.size() != n) {
            std::cerr << "Some of the vectors don't match with the matrix size (n): " << n << std::endl;
            throw std::invalid_argument("Some of the vectors don't match with the matrix size (n=" + n + ')');
        }
        return new Matrix(n, k, a, b, c, p, q, f);
    }

    static void assertMatrixIntersections() {

    }

    static double round(const ldouble x) {
        return std::round(x * 1000) / 1000;
    }

    void print() {
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size; j++) {
                // reached horizontal vector 'p'
                if (i == k - 1) {
                    std::cout << p[j] << "\t";
                    continue;
                }

                if (j == i - 1 && i - 1 >= 0 && i <= size - 1) {
                    std::cout << round(a[i - 1]) << "\t";
                }
                else if (j == i) {
                    std::cout << round(b[j]) << "\t";
                    if (i == j && j == size - 1) {
                        break;
                    }
                    std::cout<< round(c[j]) << "\t";
                    j++; // double print
                }
                // 'q' (k-1) always matches with 'b' (ddIndex) index
                else if (j == k - 1) {
                    std::cout << round(q[i]) << "\t";
                }
                else {
                    std::cout << round(0.0) << "\t";
                }
            }
            std::cout << "|" << round(f[i]) << std::endl;
        }
    }
};

#endif //MATRIX_H

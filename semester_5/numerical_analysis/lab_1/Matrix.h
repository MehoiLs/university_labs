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

    static ldouble round(const ldouble x) {
        return std::round(x * 1000.0L) / 1000.0L;
    }

    void assertMatrixIntersections() const {
        if (q[k-1] != p[k-1] || q[k-1] != b[k-1] || p[k-1] != b[k-1]) {
            throwInvalidArgumentOnIntersectionPos(k, k, "b, p, q");
        }
        if (q[k-2] != c[k-2]) {
            throwInvalidArgumentOnIntersectionPos(k, k-1, "c, q");
        }
        if (p[k-2] != a[k-2]) {
            throwInvalidArgumentOnIntersectionPos(k-1, k, "a, p");
        }
        // intersections in the bottom right corner
        if (k < size && q[k] != a[k-1]) {
            throwInvalidArgumentOnIntersectionPos(k-1, k, "a, q");
        }
        if (k < size && p[k] != c[k-1]) {
            throwInvalidArgumentOnIntersectionPos(k, k-1, "c, p");
        }
    }

    void throwInvalidArgumentOnIntersectionPos(const size_t x, const size_t y, const std::string& vectors) const {
        throw std::invalid_argument("Some intersected values are not equal on (" +
            std::to_string(x) + ';' + std::to_string( y) +
            ") (vectors: " + vectors + ")");
    }

    void assertNormalizedMainDiagonal() const {
        for (const auto _b : b) {
            if (_b != 1) {
                throw std::invalid_argument("Main diagonal is not normalized (invoke->normalizeMainDiagonal())");
            }
        }
    }

    static void forceOverride(const size_t k, matrixVector& a, matrixVector& b, matrixVector& c, matrixVector& p, matrixVector& q) {
        p[k-2] = a[k-2];
        p[k-1] = b[k-1];
        p[k] = c[k-1];
        q[k-2] = c[k-2];
        q[k-1] = b[k-1];
        q[k] = a[k-1];
    }

    // Solving
    void normalizeMainAndSubDiagonal() {
        for (auto i = 0; i < size; i++) {
            const ldouble coef = b[i];

            // b & q - always match by indices
            b[i] /= coef;
            q[i] /= coef;
            f[i] /= coef;

            // a & c - always less than 'b' by length
            if (i < size - 2) {
                if (i - 1 >= 0) {
                    // index of 'a' is always (b - 1)
                    a[i] /= coef;
                }
                // whether 'q' intersects 'c' or not
                if (k - 2 == i) {
                    c[i] = q[i];
                } else {
                    c[i] /= coef;
                }
            }
            // if 'i' matches with 'k' then it's 'p' => must divide the whole row
            if (k - 1 == i) {
                for (auto ip = 0; ip < size; ip++) {
                    p[ip] /= coef;
                }
                // normalize 'p' & 'q' (synchronize with 'b' intersections upon division)
                p[i] = b[i];
                q[i] = b[i];
            }

            // transforming sub-diagonal
            if (i < size - 1) {
                const auto coef2 = a[i];
                a[i] -= coef2 * b[i];
                b[i+1] -= coef2 * c[i];
                f[i+1] -= coef2 * f[i];
                // whether 'q' intersects 'a' or not
                if (k - 1 == i) {
                    q[i+1] = a[i];
                } else {
                    q[i+1] -= coef2 * q[i];
                }
                // normalize 'p' (synchronize with 'a' & 'b' intersections upon subtraction)
                if (k - 1 == i + 1) {
                    p[i] = a[i];
                    p[i+1] = b[i+1];
                }
            }
        }
        assertMatrixIntersections();
    }

    void normalizeUpperDiagonal() {
        assertNormalizedMainDiagonal();
        for (auto i = 0; i < size; i++) {
            const auto coef = a[i];

            a[i] -= coef * b[i];
            b[i+1] -= coef * c[i];
            q[i+1] -= coef * q[i];
            f[i+1] -= coef * f[i];
        }
    }

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
        if (k < 1 || k > size) {
            throw std::invalid_argument("The 'k' variable must be greater than 0 and not be greater than n (size)");
        }
        if (a.size() != size || b.size() != size || c.size() != size || p.size() != size || q.size() != size) {
            throw std::invalid_argument("Some of the vectors don't match with the matrix size (n=" + size + ')');
        }
        assertMatrixIntersections();
    }

    void solve() {
        normalizeMainAndSubDiagonal();
    }

    static Matrix *fromFile(const std::string &filename, const bool forceOverrideValues = false) {
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

        if (forceOverrideValues) {
            forceOverride(k, a, b, c, p, q);
        }

        return new Matrix(n, k, a, b, c, p, q, f);
    }

    void print() const {
        std::cout << std::setprecision(3);
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
                // 'q' (k-1) always matches with 'b' index
                else if (j == k - 1) {
                    std::cout << round(q[i]) << "\t";
                }
                else {
                    std::cout << round(0.0) << "\t";
                }
            }
            std::cout << "| " << round(f[i]) << std::endl << std::endl;
        }
    }
};

#endif //MATRIX_H

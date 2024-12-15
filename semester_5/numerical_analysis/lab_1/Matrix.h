#ifndef MATRIX_H
#define MATRIX_H

#define ldouble long double
#define matrixVector std::vector<ldouble>

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <random>

class Matrix {
private:

    const size_t size, k;
    matrixVector a, b, c, p, q;
    matrixVector f;

    static ldouble round(const ldouble x) {
        return std::round(x * 100.0L) / 100.0L;
    }

    [[nodiscard]]
    bool isIntersectionBPQ(const int index) const {
        return index == k - 1;
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

    static void throwInvalidArgumentOnIntersectionPos(const size_t x, const size_t y, const std::string& vectors) {
        throw std::invalid_argument("Some intersected values are not equal on (" +
            std::to_string(x) + ';' + std::to_string( y) +
            ") (vectors: " + vectors + ")");
    }

    void assertNormalizedMainAndSubDiagonals(const bool skipIntersection = true) const {
        for (auto i = 0; i < size; i++) {
            if (skipIntersection && i == k - 1) {
                continue;
            }
            if (b[i] != 1) {
                throw std::invalid_argument("Main diagonal is not normalized");
            }
        }
    }

    // Solving
    void transformMainAndSubDiagonal() {
        for (auto i = 0; i < size; i++) {
            if (isIntersectionBPQ(i)) {
                continue;
            }
            const auto coef = b[i];

            b[i] = 1;
            q[i] /= coef;
            f[i] /= coef;

            if (i < size - 1) {
                c[i] /= coef;

                // 'p' & 'q' intersections
                if (i == k - 2) {
                    q[i] = c[i];
                }
                if (i == k - 1) {
                    p[i+1] = c[i];
                }
            }
            if (i > 0) {
                a[i-1] /= coef;

                // 'p' & 'q' intersections
                if (i == k - 2) {
                    p[i] = a[i];
                }
                if (i == k - 1) {
                    q[i+1] = a[i];
                }
            }

            // transforming the sub-diagonal element to zero
            if (i < size - 1 && i != k - 2) {
                const auto coef2 = a[i];

                a[i] = 0.0;
                b[i+1] -= c[i] * coef2;
                q[i+1] -= q[i] * coef2;
                f[i+1] -= f[i] * coef2;

                if (i + 1 == k - 2) {
                    c[i+1] = q[i+1];
                }
            }
        }
        assertMatrixIntersections();
    }

    void transformUpperDiagonal() {
        assertNormalizedMainAndSubDiagonals();
        for (int i = size - 1; i > 0; i--) {
            if (isIntersectionBPQ(i) || i == k) {
                continue;
            }
            const auto coef = c[i-1];

            c[i-1] = 0.0;
            q[i-1] -= coef * q[i];
            f[i-1] -= coef * f[i];

            // 'a' & 'q' intersection
            if (i - 1 == k) {
                a[i-2] = q[i-1];
            }
        }
    }

    void transformRowK() {
        assertNormalizedMainAndSubDiagonals();
        for (auto i = 0; i < size; i++) {
            if (isIntersectionBPQ(i)) {
                continue;
            }
            const auto coef = p[i];

            p[i] = 0.0;
            f[k-1] -= coef * f[i];
            // 'p[k-1]' is constantly changed because it intersects the 'q' vector
            p[k-1] = b[k-1] = q[k-1] -= coef * q[i];
        }
        // dividing the left 'p' element by itself, therefore all intersections are set to '1'
        f[k-1] /= p[k-1];
        p[k-1] = q[k-1] = b[k-1] = 1;
    }

    void transformColumnK() {
        assertNormalizedMainAndSubDiagonals();
        for (auto i = 0; i < size; i++) {
            if (isIntersectionBPQ(i)) {
                continue;
            }
            const auto coef = q[i];

            q[i] = 0;
            f[i] -= coef * f[k-1];

            // 'c' & 'q' intersection
            if (i == k - 2) {
                c[i] = q[i];
            }
            // 'a' & 'q' intersection
            if (i == k) {
                a[i-1] = q[i];
            }
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
        if (k < 2 || k >= size) {
            throw std::invalid_argument("The 'k' variable must be greater than 1 and less than n (size)");
        }
        if (a.size() != size - 1 || b.size() != size || c.size() != size - 1 || p.size() != size || q.size() != size) {
            throw std::invalid_argument("Some of the vectors don't match with the matrix size (n=" + size + ')');
        }
        assertMatrixIntersections();
    }

    Matrix(const Matrix& other) = default;

    [[nodiscard]]
    matrixVector getF() const {
        return f;
    }

    void setF(const matrixVector& vec) {
        f = vec;
    }

    matrixVector solve() {
        transformMainAndSubDiagonal();
        transformUpperDiagonal();
        transformRowK();
        transformColumnK();
        return f;
    }

    matrixVector solveLogging() {
        std::cout << "\t\t[TRANSFORMING MAIN & SUB DIAGONALS]\n";
        transformMainAndSubDiagonal();
        print();

        std::cout << "\t\t[TRANSFORMING UPPER DIAGONAL]\n";
        transformUpperDiagonal();
        print();

        std::cout << "\t\t[TRANSFORMING K-ROW]\n";
        transformRowK();
        print();

        std::cout << "\t\t[TRANSFORMING K-COLUMN]\n";
        transformColumnK();
        print();

        return f;
    }

    // void multipleFByCoefs(const matrixVector& coefs) {
    //     for (auto i = 0; i < size; i++) {
    //         f[i] *= coefs[i];
    //     }
    // }

    void multipleByCoefs(const matrixVector& coefs) {
        for (auto i = 0; i < size; i++) {
            if (i == k - 1) {
                for (auto ip = 0; ip < size; ip++) {
                    p[ip] *= coefs[ip];
                }
                // sync
                a[i-1] = p[i-1];
                b[i] = q[i] = p[i];
                c[i] = p[i+1];
                // f[i] *= coefs[i];
                continue;
            }
    
            b[i] *= coefs[i];
            q[i] *= coefs[k-1];
            // f[i] *= coefs[i];
    
            if (i < size - 1) {
                c[i] *= coefs[i+1];
            }
            if (i > 0) {
                a[i-1] *= coefs[i-1];
            }
        }
        assertMatrixIntersections();
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
                    std::cout << round(c[j]) << "\t";
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
            std::cout << "|  " << round(f[i]);
            std::cout << std::endl << std::endl;
        }
    }

    void printAsVectors() const {
        std::cout << std::setprecision(3);

        std::cout << "n = " << size << "; k = " << k << std::endl;

        std::cout << "a = ";
        for (const auto _a : a) {
            std::cout << _a << "  ";
        }

        std::cout << "\nb = ";
        for (const auto _b : b) {
            std::cout << _b << "  ";
        }

        std::cout << "\nc = ";
        for (const auto _c : c) {
            std::cout << _c << "  ";
        }


        std::cout << "\np = ";
        for (const auto _p : p) {
            std::cout << _p << "  ";
        }

        std::cout << "\nq = ";
        for (const auto _q : q) {
            std::cout << _q << "  ";
        }


        std::cout << "\nf = ";
        for (const auto _f : f) {
            std::cout << _f << "  ";
        }
    }

    void recalculateVectorFAsSum() {
        for (auto i = 0; i < size; i++) {
            ldouble val = 0;

            // it's vector 'p', therefore must sum up all its elements
            if (i == k - 1) {
                for (const auto _p: p) {
                    val += _p;
                }
                f[i] = val;
                continue;
            }

            val += b[i] + q[i];

            // 'a' must be within bounds and must not intersect with 'q'
            if (i > 0 && i != k) {
                val += a[i-1];
            }

            // 'c' must be within bounds and must not intersect with 'q'
            if (i < size - 1 && i != k - 2) {
                val += c[i];
            }

            f[i] = val;
        }
    }

};

#endif //MATRIX_H

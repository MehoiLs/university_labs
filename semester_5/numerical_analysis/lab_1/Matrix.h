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
#include <random>

constexpr ldouble RANDOM_MIX_MAX = 1000.0L;

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

    bool isIntersectionBPQ(const int index) const {
        return index == k - 1;
    }

    static void throwInvalidArgumentOnIntersectionPos(const size_t x, const size_t y, const std::string& vectors) {
        throw std::invalid_argument("Some intersected values are not equal on (" +
            std::to_string(x) + ';' + std::to_string( y) +
            ") (vectors: " + vectors + ")");
    }

    void assertNormalizedMainAndSubDiagonals(bool skipIntersection = true) const {
        for (auto i = 0; i < size; i++) {
            if (skipIntersection && i == k - 1) {
                continue;
            }
            if (b[i] != 1) {
                throw std::invalid_argument("Main diagonal is not normalized");
            }
        }
    }

    static void forceOverride(const size_t k, const matrixVector& a, const matrixVector& b, const matrixVector& c, matrixVector& p, matrixVector& q) {
        p[k-2] = a[k-2];
        q[k-2] = c[k-2];
        p[k-1] = b[k-1];
        q[k-1] = b[k-1];
        p[k] = c[k-1];
        q[k] = a[k-1];
    }

    // // Solving
    // void transformMainAndSubDiagonal() {
    //
    //     // TODO:
    //     //  FIND OUT WHERE IF FAILS TO SYNC 'c' & 'q' INTERSECTION!!!
    //
    //     for (auto i = 0; i < size; i++) {
    //         if (isIntersectionBPQ(i)) {
    //             continue;
    //         }
    //         const auto coef = b[i];
    //
    //         // b & q - always match by indices
    //         b[i] /= coef;
    //         q[i] /= coef;
    //         f[i] /= coef;
    //
    //         // a & c - always less than 'b' by length
    //         if (i < size - 1) {
    //             c[i] /= coef;
    //             if (i == k - 2) {
    //                 q[i] = c[i];
    //             }
    //             // we skip intersection, therefore on this pos 'a' was not transformed to 0.
    //             if (i == k) {
    //                 a[i-1] /= coef;
    //                 q[i] = a[i-1];
    //             }
    //         }
    //
    //         // q[k-2] = c[k-2];
    //         // q[k] = a[k-1];
    //
    //         print();
    //         std::cout << std::endl;
    //         // normalizing the sub-diagonal along to avoid any changes in 'b' later
    //         if (i < size - 1 && i != k - 2) {
    //             const auto coef2 = a[i];
    //
    //             a[i] -= b[i] * coef2;
    //             b[i+1] -= c[i] * coef2;
    //             q[i+1] -= q[i] * coef2;
    //             f[i+1] -= f[i] * coef2;
    //
    //             // todo: sync c[k-2] & q[k-2]
    //
    //             // when 'q' is changed and intersects 'c'
    //             // if (i + 1 == k - 2) {
    //             //     c[i+1] = q[i+1];
    //             // }
    //         }
    //         print();
    //         std::cout << std::endl;
    //     }
    //     assertMatrixIntersections();
    // }

    void transformMainAndSubDiagonal() {
        for (auto i = 0; i < size; i++) {
            if (isIntersectionBPQ(i)) {
                continue;
            }
            const auto coef = b[i];

            b[i] = 1;
            // b[i] /= coef;
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

            // sub
            if (i < size - 1 && i != k - 2) {
                const auto coef2 = a[i];

                // a[i] -= b[i] * coef2;
                a[i] = +0.0;
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
            // c[i-1] -= coef * b[i];
            q[i-1] -= coef * q[i];
            f[i-1] -= coef * f[i];

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
            p[k-1] = b[k-1] = q[k-1] -= coef * q[i];
        }
        // p[k-1] is always divided by itself in the end, therefore it always equals 1.
        f[k-1] /= p[k-1];
        p[k-1] = 1;
        q[k-1] = 1;
        b[k-1] = 1;
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

            if (i == k - 2) {
                c[i] = q[i];
            }
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

    matrixVector solveWithLogging() {
        std::cout << std::endl << "\t[INITIAL MATRIX]\n" << std::endl;
        print();
        std::cout << std::endl << "\t[TRANSFORMING MAIN & SUB DIAGONALS]\n" << std::endl;
        transformMainAndSubDiagonal();
        print();
        std::cout << std::endl << "\t[TRANSFORMING UPPER-DIAGONAL]\n" << std::endl;
        transformUpperDiagonal();
        print();
        std::cout << std::endl << "\t[TRANSFORMING k-ROW]\n" << std::endl;
        transformRowK();
        print();
        std::cout << std::endl << "\t[TRANSFORMING k-COLUMN]\n" << std::endl;
        transformColumnK();
        print();
        std::cout << std::endl << "\t[SOLUTION]\n" << std::endl;
        printVectorAsColumn(f);
        return f;
    }

    matrixVector solve() {
        transformMainAndSubDiagonal();
        transformUpperDiagonal();
        transformRowK();
        transformColumnK();
        return f;
    }

    static matrixVector calculateVectorF(
        const size_t size,
        const size_t k,
        const ldouble coef,
        const matrixVector &a,
        const matrixVector &b,
        const matrixVector &c,
        const matrixVector &p,
        const matrixVector &q
    ) {
        matrixVector f(size);
        for (auto i = 0; i < size; i++) {
            ldouble val = 0;
            if (i == k - 1) {
                for (const auto _p: p) {
                    val += _p * coef;
                }
                f[i] = val;
                continue;
            }
            val += b[i] * coef + q[i] * coef;
            // 'a' must be within bounds and must not intersect with 'q' (k-1)
            if (i > 0 && i != k) {
                val += a[i-1] * coef;
            }
            // 'c' must be within bounds and must not intersect with 'q' (k-2)
            if (i < size - 1 && i != k - 2) {
                val += c[i] * coef;
            }
            f[i] = val;
        }
        return f;
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

        if (k < 1 || k >= n) {
            throw std::invalid_argument("The 'k' variable must be greater/equal than 0 and not be greater than n (size)");
        }

        a.resize(n - 1);
        c.resize(n - 1);

        inputFile.close();

        if (forceOverrideValues) {
            forceOverride(k, a, b, c, p, q);
        }

        return new Matrix(n, k, a, b, c, p, q, f);
    }

    static Matrix* generateRandom(const size_t size) {
        if (size <= 1) {
            throw std::invalid_argument("The size must be greater than 1");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution urd(-RANDOM_MIX_MAX, RANDOM_MIX_MAX);
        std::uniform_int_distribution<size_t> uid(2, size - 1);

        const size_t k = uid(gen);;
        matrixVector a(size-1), b(size), c(size-1), p(size), q(size), f(size);

        for (size_t i = 0; i < size; ++i) {
            if (i < size - 1) {
                a[i] = urd(gen);
                c[i] = urd(gen);
            }
            b[i] = urd(gen);
            p[i] = urd(gen);
            q[i] = urd(gen);
            f[i] = urd(gen);
        }
        forceOverride(k, a, b, c, p, q);

        return new Matrix(size, k, a, b, c, p, q, f);
    }

    static Matrix* generateRandomCalculatingF(const size_t size, const ldouble coef = 1) {
        if (size <= 1) {
            throw std::invalid_argument("The size must be greater than 1");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution urd(-RANDOM_MIX_MAX, RANDOM_MIX_MAX);
        std::uniform_int_distribution<size_t> uid(2, size - 1);

        const size_t k = uid(gen);;
        matrixVector a(size-1), b(size), c(size-1), p(size), q(size);

        for (size_t i = 0; i < size; ++i) {
            if (i < size - 1) {
                a[i] = urd(gen);
                c[i] = urd(gen);
            }
            b[i] = urd(gen);
            p[i] = urd(gen);
            q[i] = urd(gen);
        }
        forceOverride(k, a, b, c, p, q);
        const auto matrix = new Matrix(size, k, a, b, c, p, q, {});
        matrix->f = calculateVectorF(size, k, coef, a, b, c, p, q);
        return matrix;
    }

    matrixVector getF() const {
        return f;
    }

    void print() const {
        std::cout << std::setprecision(3);
        const auto debug_vec = calculateVectorF(size, k, 1, a, b, c, p, q);
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
            std::cout << "| " << round(f[i]);
            std::cout << " \t\t||| " << round(debug_vec[i]);
            std::cout << std::endl << std::endl;
        }
    }

    static void printVectorAsColumn(const matrixVector &vector) {
        std::cout << std::setprecision(3);
        for (const auto &v : vector) {
            std::cout << v << std::endl;
        }
    }
};

#endif //MATRIX_H

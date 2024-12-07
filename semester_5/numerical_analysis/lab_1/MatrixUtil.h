#ifndef MATRIXUTIL_H
#define MATRIXUTIL_H

#include "Matrix.h"

#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <random>

constexpr ldouble RANDOM_MIX_MAX = 100.0L;
constexpr ldouble RANDOM_VEC_BOUNDS = 100.0L;

class MatrixUtil final {
public:

    static void forceOverrideVectorsPQ(const size_t k, const matrixVector& a, const matrixVector& b, const matrixVector& c, matrixVector& p, matrixVector& q) {
        p[k-2] = a[k-2];
        q[k-2] = c[k-2];
        p[k-1] = b[k-1];
        q[k-1] = b[k-1];
        p[k] = c[k-1];
        q[k] = a[k-1];
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

            // it's vector 'p', therefore must sum up all its elements
            if (i == k - 1) {
                for (const auto _p: p) {
                    val += _p * coef;
                }
                f[i] = val;
                continue;
            }

            val += b[i] * coef + q[i] * coef;

            // 'a' must be within bounds and must not intersect with 'q'
            if (i > 0 && i != k) {
                val += a[i-1] * coef;
            }

            // 'c' must be within bounds and must not intersect with 'q'
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
            forceOverrideVectorsPQ(k, a, b, c, p, q);
        }

        return new Matrix(n, k, a, b, c, p, q, f);
   }

   static Matrix* generateRandomCalculatingF(
        const size_t size,
        const ldouble bounds = RANDOM_MIX_MAX,
        const ldouble coef = 1.0
   ) {
        if (size <= 1) {
            throw std::invalid_argument("The size must be greater than 1");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution urd(-bounds, bounds);
        std::uniform_int_distribution<size_t> uid(2, size - 1);

        const size_t k = uid(gen);;
        matrixVector a(size-1), b(size), c(size-1), p(size), q(size);

        for (auto i = 0; i < size; ++i) {
            if (i < size - 1) {
                a[i] = urd(gen);
                c[i] = urd(gen);
            }
            b[i] = urd(gen);
            p[i] = urd(gen);
            q[i] = urd(gen);
        }
        forceOverrideVectorsPQ(k, a, b, c, p, q);

        matrixVector f(size);
        f = calculateVectorF(size, k, coef, a, b, c, p, q);

        return new Matrix(size, k, a, b, c, p, q, f);
   }

   static matrixVector generateRandomVector(const size_t size, const ldouble bounds = RANDOM_VEC_BOUNDS) {
        if (size < 1) {
            throw std::invalid_argument("size must be bigger than 0");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution urd(-bounds, bounds);

        matrixVector vec(size);
        for (auto i = 0; i < size; i++) {
            vec[i] = urd(gen);
        }

        return vec;
   }

};

#endif //MATRIXUTIL_H

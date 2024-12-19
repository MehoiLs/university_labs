#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <iomanip>
#include <mutex>

static constexpr int MAX_THREADS_COUNT = 12;

double f(const double x) {
    if (x < -20) {
        return 0.1 * x;
    }
    if (x >= -20 && x < -5) {
        return 0.5 * sin(0.25 * x) + 2.2 * cos(0.01 * x);
    }
    return pow(x, 5) - pow(x, 4) + pow(x, 2) - x + 1;
}

std::mutex mtx;

double globalMin = INFINITY;
double globalMax = -INFINITY;
double globalIntegral = 0.0;

void threadFunction(const double a, const double b, const double h, const int numSamples, const int threadNum) {
    // Calculate local integral using Trapezoidal Rule
    double integral = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < numSamples; ++i) {
        const double x = a + i * h;
        integral += f(x);
    }
    integral *= h;

    // Calculate local min and max by sampling points
    double localMin = f(a);
    double localMax = f(a);
    for (int i = 0; i <= numSamples; ++i) {
        const double x = a + i * h;
        const double fx = f(x);
        if (fx < localMin) {
            localMin = fx;
        }
        if (fx > localMax) {
            localMax = fx;
        }
    }

    // Update global variables
    std::lock_guard lock(mtx);
    std::cout << std::setw(4);
    std::cout << "#" << threadNum + 1 << ":\t Local min = " << localMin << ";\t Local max = " << localMax
        << ";\t Integral = " << integral << ";\n";
    globalMin = std::min(globalMin, localMin);
    globalMax = std::max(globalMax, localMax);
    globalIntegral += integral;
}

int main() {
    constexpr int N = MAX_THREADS_COUNT; // Number of subintervals and threads
    constexpr int numSamples = 1000000; // Number of sample points per subinterval for min/max

    constexpr double A = -25.0;
    constexpr double B = 5.0;
    constexpr double h = (B - A) / N;

    std::vector<std::thread> threads;

    std::cout << "[THREADS]\n";
    // Create and launch threads
    for (int i = 0; i < N; ++i) {
        double a = A + i * h;
        double b = A + (i + 1) * h;
        threads.emplace_back(threadFunction, a, b, h / numSamples, numSamples, i);
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Output the results
    std::cout << "\n[GLOBAL]\n";
    std::cout << "Global Minimum: " << globalMin << std::endl;
    std::cout << "Global Maximum: " << globalMax << std::endl;
    std::cout << "Integral: " << globalIntegral << std::endl;

    return 0;
}
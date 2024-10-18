#include <iostream>
#include <thread>
#include <ctime>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>

#define timestamp std::chrono::time_point<std::chrono::system_clock>&

const int MAX_THREADS_COUNT = 8;
const int PARTITION_ARRAY_SIZE = 100000;

/**
 * Default quick sort own implementation.
 *
 * @tparam Iterator - iterator type
 * @param begin - iterator to the first element
 * @param end - iterator to the last element
 */
template<typename Iterator>
void quickSortImpl(Iterator begin, Iterator end) {
    if (begin == end) {
        return;
    }

    auto pivot = *std::next(begin, std::distance(begin, end) / 2);
    auto left = begin;
    auto right = std::prev(end);

    while (left <= right) {
        while (*left < pivot) {
            ++left;
        }

        while (*right > pivot) {
            --right;
        }

        if (left <= right) {
            std::iter_swap(left, right);
            ++left;
            --right;
        }
    }

    quickSortImpl(begin, right + 1);
    quickSortImpl(left, end);
}

/**
 * Multi-thread quick sort own implementation.
 *
 * @tparam Iterator - iterator type
 * @param begin - iterator to the first element
 * @param end - iterator to the last element
 * @param threadLimit - limit of threads (when exceeded, algorithm keeps working in the same thread)
 */
template<typename Iterator>
void quickSortMT(Iterator begin, Iterator end, const int threadLimit = MAX_THREADS_COUNT) {
    if (begin == end || std::distance(begin, end) <= 1) {
        return;
    }

    auto pivot = *std::next(begin, std::distance(begin, end) / 2);
    Iterator middle1 = std::partition(begin, end, [pivot](const auto& em) {
        return em < pivot;
    });
    Iterator middle2 = std::partition(middle1, end, [pivot](const auto& em) {
        return pivot >= em;
    });

    if (threadLimit <= 1) {
        quickSortImpl(begin, middle1);
        quickSortImpl(middle2, end);
        return;
    }

    const int THREADS_COUNT = 2;
    std::thread threads[THREADS_COUNT];
    int threadNum = 0;

    if (std::distance(begin, middle1) > PARTITION_ARRAY_SIZE) {
        threads[threadNum++] = std::thread(quickSortMT<Iterator>, begin, middle1, threadLimit / 2);
    } else {
        quickSortImpl(begin, middle1);
    }

    if (std::distance(begin, middle1) > PARTITION_ARRAY_SIZE) {
        threads[threadNum++] = std::thread(quickSortMT<Iterator>, middle2, end, threadLimit / 2);
    } else {
        quickSortImpl(middle2, end);
    }

    for (int i = 0; i < threadNum; i++) {
        threads[i].join();
    }
}

/**
 * Creates a random integer array.
 * Uses [std::random_device] and [std::uniform_int_distribution] for better randomness.
 *
 * @param size - array size
 * @param minVal - minimal random value
 * @param maxVal - maximum random value
 * @return - random integer array
 */
std::vector<int> createRandomIntArray(const int size, const int minVal, const int maxVal) {
    std::vector<int> array(size);

    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::random_device rd;

    for (int i = 0; i < size; i++) {
        array[i] = dist(rd);
    }
    return array;
}

/**
 * Wrapper for [std::chrono::high_resolution_clock::now()].
 * @return - current time
 */
auto now() {
    return std::chrono::high_resolution_clock::now();
}

/**
 * Calculates the duration between two timestamps in milliseconds.
 *
 * @param startTime - start time
 * @param endTime - end time
 * @return - duration in milliseconds
 */
long long getDurationInMillis(const timestamp startTime, const timestamp endTime) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

/**
 * Casts the timestamp to a string with the format [HH:MM:SS].
 *
 * @param time - timestamp
 * @return - string with the format [HH:MM:SS]
 */
auto castTime(const timestamp time) {
    std::time_t start_time_t = std::chrono::system_clock::to_time_t(time);
    return std::put_time(std::localtime(&start_time_t), "%H:%M:%S");
}

/**
 * Prints the statistics of the sorting algorithm.
 *
 * @param startTime - start time
 * @param endTime - end time
 * @param arraySize - array size
 * @param implName - implementation name
 */
void printStatistics(
        const timestamp startTime,
        const timestamp endTime,
        const size_t arraySize,
        const std::string &implName
) {
    std::cout << std::endl;
    std::cout << "\t" << implName << std::endl;
    std::cout << "- Started at: " << castTime(startTime) << std::endl;
    std::cout << "- Ended at: " << castTime(endTime) << std::endl;
    std::cout << "- Array size: " << arraySize << std::endl;
    std::cout << "- Time: " << getDurationInMillis(startTime, endTime) << " ms" << std::endl;
    std::cout << std::endl;
}

/**
 * Tests the regular quick sort implementation.
 *
 * @param initArray - initial array to perform the sorting on
 */
void testQuickSortDefaultImpl(const std::vector<int> &initArray) {
    std::cout << "Performing a regular quick sort implementation..." << std::endl;
    auto array = std::vector<int>(initArray);

    auto startTime = now();
    quickSortImpl(array.begin(), array.end());
    auto endTime = now();

    printStatistics(startTime, endTime, array.size(), "REGULAR QUICK SORT");
}

/**
 * Tests the multi-thread quick sort implementation.
 *
 * @param initArray - initial array to perform the sorting on
 */
void testQuickSortMTImpl(const std::vector<int> &initArray) {
    std::cout << "Performing a multi-thread quick sort implementation..." << std::endl;
    auto array = std::vector<int>(initArray);

    auto startTime = now();
    quickSortMT(array.begin(), array.end());
    auto endTime = now();

    printStatistics(startTime, endTime, array.size(), "MULTI-THREAD QUICK SORT");
}

/**
 * Main function.
 */
int main() {
    const int ARRAY_SIZE = 100000000; // 100.000.000
    const int MIN_VAL = 0;
    const int MAX_VAL = 10000000; // 10.000.000

    std::cout << "Creating a random array..." << std::endl;
    const auto initArray = createRandomIntArray(ARRAY_SIZE, MIN_VAL, MAX_VAL);

    testQuickSortDefaultImpl(initArray);
    testQuickSortMTImpl(initArray);

    return 0;
}

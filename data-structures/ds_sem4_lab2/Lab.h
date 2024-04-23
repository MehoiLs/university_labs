#ifndef DS_SEM4_LAB2_LAB_H
#define DS_SEM4_LAB2_LAB_H

#include <iostream>
#include <vector>

using namespace std;

class Lab {
private:
    static vector<int> findAllProductsCombinations(const vector<int>& elements, vector<int>& current, int size, int index) {
        vector<int> products;

        if (current.size() == size) {
            int product = 1;
            for (int num : current) {
                product *= num;
            }
            products.push_back(product);
            return products;
        }

        for (int i = index; i < elements.size(); ++i) {
            current.push_back(elements[i]);
            vector<int> subProducts = findAllProductsCombinations(elements, current, size, i + 1);
            products.insert(products.end(), subProducts.begin(), subProducts.end());
            current.pop_back();
        }

        return products;
    }

    static vector<int> findAllProductsCombinations(const vector<int>& elements, int size, int index = 0) {
        vector<int> current;
        return findAllProductsCombinations(elements, current, size, index);
    }


public:
    static int performComparison(int number, const vector<int> &comparingDivisors) {
        const auto size = comparingDivisors.size();
        int result = 0;
        for (int combinationCount = 1; combinationCount <= size; ++combinationCount) {
            auto allCombinations = findAllProductsCombinations(comparingDivisors, combinationCount);
            auto currentResult = 0;
            for (int combinationProduct : allCombinations) {
                currentResult += (number / combinationProduct);
            }
            const auto sign = (combinationCount % 2 == 0) ? -1 : 1;
            result += sign * currentResult;
        }

        return (number - result);
    }

    static int calculate() {
        int m, k;
        cout << "Enter m: ";
        cin >> m;
        cout << "Enter k: ";
        cin >> k;
        vector<int> numbers(k);
        cout << "Enter " << k << " numbers: ";
        for (int i = 0; i < k; ++i) {
            cin >> numbers[i];
        }
        int result = performComparison(m, numbers);
        cout << "Result: " << result << endl;

        return 0;
    }
};

/**
 * Написать программу для формулы включения и исключения. С её помощью определить количество
 * натуральных чисел меньше или равных m, не делящихся ни на одно из заданных k чисел n_1, n_2, ..., n_k.
 * */

#endif //DS_SEM4_LAB2_LAB_H
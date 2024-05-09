#ifndef DS_SEM4_LAB2_INCLUSIONEXCLUSIONCALCULATOR_H
#define DS_SEM4_LAB2_INCLUSIONEXCLUSIONCALCULATOR_H

#include <iostream>
#include <vector>

using namespace std;

/** Реализация задачи
 *
 * @author MehoiLs (Dorokhov Mikhail)
 * */
class InclusionExclusionCalculator {
private:
    /** Статический рекурсивный метод, подсчитывающий всевозможные комбинации,
     *  и возвращающий их произведения.
     *
     *  @param elements - вектор элементов, из которых составляются комбинации
     *  @param currentCombo - вектор для хранения текущей комбинации
     *  @param comboSize - размер комбинации
     *  @param currentIndex - текущий индекс
     * */
    static vector<int> findAllProductsCombinations(const vector<int>& elements, vector<int>& currentCombo, int comboSize, int currentIndex) {
        vector<int> products;

        // Если текущее комбо достигло нужного размера, то считаем произведение, добавляем его в вектор и сворачиваемся из рекурсии
        if (currentCombo.size() == comboSize) {
            int product = 1;
            for (int num : currentCombo) {
                product *= num;
            }
            products.push_back(product);
            return products;
        }

        // Перебираем все элементы, начиная с текущего индекса
        for (int i = currentIndex; i < elements.size(); ++i) {
            currentCombo.push_back(elements[i]); // Добавляем элемент в текущую комбинацию
            // Рекурсивно вызываем метод для поиска (под)комбинаций произведений со следующего индекса
            vector<int> subProducts = findAllProductsCombinations(elements, currentCombo, comboSize, i + 1);
            // Добавляем все найденные комбинации произведений в вектор
            products.insert(products.end(), subProducts.begin(), subProducts.end());
            currentCombo.pop_back(); // Удаляем последний элемент из текущей комбинации
        }

        return products;
    }

    /** Обёрточный метод для `findAllProductsCombinations` */
    static vector<int> findAllProductsCombinations(const vector<int>& elements, int comboSize, int currentIndex = 0) {
        vector<int> current;
        return findAllProductsCombinations(elements, current, comboSize, currentIndex);
    }


public:
    /** Статический метод, выполняющий сравнение числа с заданными делителями.
     *
     * @param number - число, с которым производится сравнение
     * @param comparingDivisors - вектор делителей
     * @return результат сравнения
     */
    static int performComparison(int number, const vector<int> &comparingDivisors) {
        const auto size = comparingDivisors.size(); // (чтобы не вызывать .size() каждую итерацию)
        int result = 0;
        for (int combinationCount = 1; combinationCount <= size; ++combinationCount) {
            // Находим все возможные комбинации произведений делителей для текущего количества комбинаций
            auto allCombinations = findAllProductsCombinations(comparingDivisors, combinationCount);
            auto currentResult = 0;
            // Считаем количество чисел, делящихся на произведения делителей.
            // Если число делится на произведение делителей, то оно делится и на каждый делитель в отдельности.
            for (int combinationProduct : allCombinations) {
                // Используем целочисленное деление, а не деление по модулю потому
                // что нам нужно количество чисел, делящихся на произведение делителей, а не остаток от деления.
                currentResult += (number / combinationProduct);
            }
            // Подсчитываем результат с учётом знака.
            // Вот он, тот самый принцип Включений-Исключений! :)
            const auto sign = (combinationCount % 2 == 0) ? -1 : 1;
            result += sign * currentResult;
        }

        // Возвращаем разницу между общим количеством чисел и числами, делящимися на произведения делителей.
        // Это и будет число, не делящихся ни на одно из заданных чисел.
        return (number - result);
    }

    /** Статический метод, выполняющий ввод данных и вывод результата.
     *
     * @return результат выполнения программы
     */
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

#endif //DS_SEM4_LAB2_INCLUSIONEXCLUSIONCALCULATOR_H
# ПП. Лабораторная Работа №1

## Задание
Написать алгоритм быстрой сортировки.
Сделать его многопоточную реализацию.

- Сравнить время сортировки однопоточной и
многопоточной версий на мелком массиве (<100 элементов).

- Сравнить время сортировки однопоточной и
многопоточной версий на крупном массиве (>10000 элементов).

Сделать выводы.

## Краткое описание реализации
Было реализовано два варианта алгоритма быстрой сортировки:
- Однопоточный (`quickSortImpl`)
- Многопоточный (`quickSortMT`)

По сути, многопоточный метод использует однопоточный метод,
но разбивает массив на части и запускает каждую часть 
в отдельном потоке в зависимости от количества доступных потоков
(определяется константой `MAX_THREADS_COUNT`).

Если количество потоков превышает `MAX_THREADS_COUNT`, 
то сортировка выполняется в одном (текущем) потоке.

Новый поток создаётся при разбиении массива на части и условии того,
что размер этой части массива больше чем `PARTITION_ARRAY_SIZE` (константа).

Отслеживание времени выполнения происходит простым образом с помощью библиотеки `chrono`.


## Разбор многопоточной реализации

### **Условие выхода из рекурсии:**
```cpp
if (begin == end || std::distance(begin, end) <= 1) {
    return;
}
```
Если массив пустой или содержит только один элемент - выходим.


### **Определение середины массива (опорный элемент):**
```cpp
auto pivot = *std::next(begin, std::distance(begin, end) / 2);
```


### **Разделение массива на две части:**
```cpp
Iterator middle1 = std::partition(begin, end, [pivot](const auto& em) {
    return em < pivot;
});
Iterator middle2 = std::partition(middle1, end, [pivot](const auto& em) {
    return pivot >= em;
});
```
`std::partition` - разбивает массив на две части и возвращает итератор,
в зависимости от условия; в данном случае разбивает относительно опорного элемента, 
где:
- `middle1` - первый элемент меньше опорного, 
- `middle2` - первый элемент больше/равный опорного


### **Ограничение количества потоков:**
```cpp
if (threadLimit <= 1) {
    quickSortImpl(begin, middle1);
    quickSortImpl(middle2, end);
    return;
}
```
Если ограничение было превышено, то выполняем сортировку в одном (этом же) потоке.


### **Объявление массива потоков:**
```cpp
const int THREADS_COUNT = 2;
std::thread threads[THREADS_COUNT];
int threadNum = 0;
```
Поскольку алгоритм всегда делит массив на две части,
то и максимальное количество потоков на итерацию всегда равно 2.


### **Создаём поток, если текущий части размер массива больше чем** `PARTITION_ARRAY_SIZE`**:**
```cpp
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
```
В противном случае - выполняем сортировку в текущем потоке.
В поток передаём этот же метод, начало и конец массива, 
и ограничение потоков, уменьшенное вдвое (т.к. массив разбивается на две части).


### **Ожидаем завершения всех потоков:**
```cpp
for (int i = 0; i < threadNum; i++) {
    threads[i].join();
}
```
`thread.join()` - блокирует текущий поток до тех пор, пока поток `thread` не завершится.
Таким образом, главный поток будет ждать завершения всех созданных потоков.


## Пример работы

### **Массив размера 100**
```
Creating a random array...
Performing a regular quick sort implementation...

        REGULAR QUICK SORT
- Started at: 22:13:25
- Ended at: 22:13:25
- Array size: 100
- Time: 0 ms

Performing a multi-thread quick sort implementation...

        MULTI-THREAD QUICK SORT
- Started at: 22:13:25
- Ended at: 22:13:25
- Array size: 100
- Time: 0 ms
```

### **Массив размера 10.000**
```
Creating a random array...
Performing a regular quick sort implementation...

        REGULAR QUICK SORT
- Started at: 22:14:36
- Ended at: 22:14:36
- Array size: 10000
- Time: 3 ms

Performing a multi-thread quick sort implementation...

        MULTI-THREAD QUICK SORT
- Started at: 22:14:36
- Ended at: 22:14:36
- Array size: 10000
- Time: 3 ms
```

### **Массив размера 100.000**
```
Creating a random array...
Performing a regular quick sort implementation...

        REGULAR QUICK SORT
- Started at: 22:15:12
- Ended at: 22:15:12
- Array size: 100000
- Time: 41 ms

Performing a multi-thread quick sort implementation...

        MULTI-THREAD QUICK SORT
- Started at: 22:15:12
- Ended at: 22:15:12
- Array size: 100000
- Time: 46 ms
```

### **Массив размера 10.000.000**
```
Creating a random array...
Performing a regular quick sort implementation...

        REGULAR QUICK SORT
- Started at: 22:15:47
- Ended at: 22:15:52
- Array size: 10000000
- Time: 5007 ms

Performing a multi-thread quick sort implementation...

        MULTI-THREAD QUICK SORT
- Started at: 22:15:52
- Ended at: 22:15:55
- Array size: 10000000
- Time: 2953 ms
```

### **Массив размера 100.000.000**
```
Creating a random array...
Performing a regular quick sort implementation...

        REGULAR QUICK SORT
- Started at: 22:21:37
- Ended at: 22:22:31
- Array size: 100000000
- Time: 53915 ms

Performing a multi-thread quick sort implementation...

        MULTI-THREAD QUICK SORT
- Started at: 22:22:32
- Ended at: 22:22:58
- Array size: 100000000
- Time: 26647 ms
```
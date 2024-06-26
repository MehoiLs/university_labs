## Лабораторная работа 2.

### Вариант 23
"Написать программу для формулы включения и исключения. 
С её помощью определить количество натуральных чисел меньше или
равных `m`, не делящихся ни на одно из заданных `k` чисел
`n_1, n_2, ..., n_k`".

### Описание структуры программы

- ds_sem4_lab2/**main.cpp** - точка запуска программы
- ds_sem4_lab2/**InclusionExclusionCalculator.h** - 
реализация задачи
- ds_sem_4_lab2/test/**TestInclusionExclusionCalculator.h** -
базовая реализация тестов для класса **InclusionExclusionCalculator.h**

### Описание работы программы

В данной программе **принцип включений и исключений** 
используется следующим образом:  
- Для каждого числа из заданных делителей находятся все возможные комбинации 
произведений делителей для текущего количества комбинаций. Это делается с 
помощью рекурсивного метода `findAllProductsCombinations`
- Затем, для каждого произведения делителей, подсчитывается количество чисел, 
которые делятся на это произведение. Это делается путем целочисленного 
деления числа на произведение делителей.
- Результаты суммируются с учетом знака. 
  - Если количество делителей в произведении нечетное, то результат добавляется; 
  - иначе - вычитается. 
  - **Это соответствует принципу включений и исключений. Вместо сравнения всех
чисел (от 1 до `m`), как требует условие, мы пользуемся этим принципом для
подсчета количества чисел, которые делятся на заданные.**
- В конце из общего количества чисел вычитается полученный результат. Полученное число - это количество чисел, которые не делятся ни на одно из заданных чисел.

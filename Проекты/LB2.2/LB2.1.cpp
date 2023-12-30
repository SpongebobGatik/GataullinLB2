#include <stdio.h>
#include <locale.h>

// Функция для нахождения разницы между двумя числами
int findDifference(int a, int b) {
    return a > b ? a - b : b - a;
}

// Функция для вывода подмножеств и их разницы
void printSubsets(int set[], int subsets[], int n, int subsetSize) {
    int i, j;
    int sumSubset1 = 0, sumSubset2 = 0;
    int minDifference = -1;

    // Вычисляем сумму каждого подмножества и находим минимальную разницу
    for (i = 0; i < n; i++) {
        if (subsets[i] == 1) {
            sumSubset1 += set[i];
        }
        else {
            sumSubset2 += set[i];
        }
    }
    minDifference = findDifference(sumSubset1, sumSubset2);

    // Выводим подмножества и разницу их сумм
    printf("Первое подмножество: ");
    for (i = 0; i < n; i++) {
        if (subsets[i] == 1) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");

    printf("Второе подмножество: ");
    for (i = 0; i < n; i++) {
        if (subsets[i] == 0) {
            printf("%d ", set[i]);
        }
    }
    printf("\n");

    printf("Разница: %d\n", minDifference);
}

// Функция для разбиения множества на непересекающиеся подмножества
void divideIntoSubsets(int set[], int subsets[], int subsetSize, int n, int current, int count) {
    // Если достигли конца подмножества
    if (current == subsetSize) {
        printSubsets(set, subsets, n, subsetSize);
        return;
    }

    // Если все элементы рассмотрены
    if (count == n) {
        return;
    }

    // Включаем текущий элемент в подмножество
    subsets[count] = 1;
    divideIntoSubsets(set, subsets, subsetSize, n, current + 1, count + 1);

    // Исключаем текущий элемент из подмножества
    subsets[count] = 0;
    divideIntoSubsets(set, subsets, subsetSize, n, current, count + 1);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int set[] = { 5, 8, 1, 14, 7 };
    const int n = sizeof(set) / sizeof(set[0]);

    int subsets[n];

    // Инициализируем все элементы подмножеств нулями
    for (int i = 0; i < n; i++) {
        subsets[i] = 0;
    }

    // Размер каждого подмножества
    int subsetSize = n / 2;

    divideIntoSubsets(set, subsets, subsetSize, n, 0, 0);

    return 0;
}
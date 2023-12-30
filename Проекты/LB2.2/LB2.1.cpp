#include <stdio.h>
#include <locale.h>
#include <limits.h>

// Функция для нахождения разницы между двумя числами
int findDifference(int a, int b) {
    return a > b ? a - b : b - a;
}

// Глобальные переменные для хранения подмножеств с минимальной разницей
int minDifference = INT_MAX;
int minSubset1[100], minSubset2[100];
int minSubsetSize1 = 0, minSubsetSize2 = 0;

// Функция для вывода подмножеств и их разницы
void printSubsets(int set[], int subsets[], int n, int subsetSize) {
    int i, j;
    int sumSubset1 = 0, sumSubset2 = 0;

    // Вычисляем сумму каждого подмножества и находим минимальную разницу
    for (i = 0; i < n; i++) {
        if (subsets[i] == 1) {
            sumSubset1 += set[i];
        }
        else {
            sumSubset2 += set[i];
        }
    }
    int difference = findDifference(sumSubset1, sumSubset2);

    // Если разница меньше минимальной, сохраняем подмножества
    if (difference < minDifference) {
        minDifference = difference;
        minSubsetSize1 = 0;
        minSubsetSize2 = 0;
        for (i = 0; i < n; i++) {
            if (subsets[i] == 1) {
                minSubset1[minSubsetSize1++] = set[i];
            }
            else {
                minSubset2[minSubsetSize2++] = set[i];
            }
        }
    }
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

    // Выводим подмножества с минимальной разницей
    printf("Первое подмножество: ");
    for (int i = 0; i < minSubsetSize1; i++) {
        printf("%d ", minSubset1[i]);
    }
    printf("\n");

    printf("Второе подмножество: ");
    for (int i = 0; i < minSubsetSize2; i++) {
        printf("%d ", minSubset2[i]);
    }
    printf("\n");

    printf("Минимальная разница: %d\n", minDifference);

    return 0;
}

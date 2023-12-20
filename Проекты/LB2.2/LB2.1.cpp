#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

#define N 5 // Константа для количества элементов в массиве
#define SUMTOTAL 35 // Предполагаемая константа для общей суммы элементов массива

// Функция для вычисления абсолютной разницы между суммами двух подмножеств
int findMin(const int arr[], int n) {
    // Создаем массив для хранения результатов подзадач
    int dp[N + 1][SUMTOTAL + 1];

    // Инициализируем первую колонку как истинную, 0 сумма достижима всеми подмножествами
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;

    // Инициализируем верхнюю строку, кроме dp[0][0], как ложную
    for (int i = 1; i <= SUMTOTAL; i++)
        dp[0][i] = 0;

    // Заполняем массив dp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= SUMTOTAL; j++) {
            // Если i-е число больше, чем сумма, то копируем значение из строки выше
            if (arr[i - 1] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
        }
    }

    // Находим минимальную разницу
    int diff = INT_MAX;
    for (int j = SUMTOTAL / 2; j >= 0; j--) {
        if (dp[n][j] == 1) {
            diff = SUMTOTAL - 2 * j;
            break;
        }
    }
    return diff;
}

int main() {
    setlocale(LC_ALL, "Rus");
    const int arr[N] = { 5, 8, 1, 14, 7 }; // Инициализация массива как константы
    printf("Минимальная разница: %d\n", findMin(arr, N));
    return 0;
}

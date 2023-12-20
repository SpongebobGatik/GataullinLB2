#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

// Функция match проверяет, соответствует ли строка sequence шаблону pattern
bool match(char* sequence, char* pattern) {
    // Если шаблон пуст, возвращаем true, если строка тоже пуста
    if (*pattern == '\0') return *sequence == '\0';

    // Если в шаблоне встречается '*', проверяем оставшуюся часть строки
    if (*pattern == '*') {
        pattern++; // Пропускаем символ '*'
        if (*pattern == '\0') return true; // Если после '*' ничего нет, возвращаем true
        // Продолжаем проверку до конца строки или пока не найдем соответствие
        while (*sequence != '\0' && !match(sequence, pattern)) {
            sequence++;
        }
        return *sequence != '\0';
    }
    // Если в шаблоне '?', или символы совпадают, проверяем следующие символы
    else if (*pattern == '?' || *pattern == *sequence) {
        return match(sequence + 1, pattern + 1);
    }

    // Если ни одно условие не выполнено, возвращаем false
    return false;
}

int main() {
    setlocale(LC_ALL, "Rus"); // Установка русской локализации

    // Проверка соответствия строки шаблону с использованием функции match
    char sequence[] = "meow@stud.nstu.ru";
    char pattern[] = "*@stud.nstu.ru";
    if (match(sequence, pattern)) {
        printf("Последовательность \"%s\" соответствует шаблону \"%s\".\n", sequence, pattern);
    }
    else {
        printf("Последовательность \"%s\" не соответствует шаблону \"%s\".\n", sequence, pattern);
    }

    // Проверка другой строки и шаблона
    char sequence2[] = "hello";
    char pattern2[] = "h?lo";
    if (match(sequence2, pattern2)) {
        printf("Последовательность \"%s\" соответствует шаблону \"%s\".\n", sequence2, pattern2);
    }
    else {
        printf("Последовательность \"%s\" не соответствует шаблону \"%s\".\n", sequence2, pattern2);
    }

    return 0;
}
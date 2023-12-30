#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXOP 100 // Макс. размер операнда или оператора
#define NUMBER '0' // Сигнал, что обнаружено число

int getop(char[]);
void push(double);
double pop(void);

// Обратная польская запись

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("%.8g\n", pop());
            if (pop() != 0.0 || pop() != 0.0) printf("Problems\n");
            else printf("Its OK\n");
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100 // Максимальная глубина стека

int sp = 0; // Следующая свободная позиция в стеке
double val[MAXVAL]; // Стек

// push: положить значение f в стек
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

// pop: взять значение с вершины стека
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

// getop: получить следующий оператор или операнд
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; // Не число
    i = 0;
    if (isdigit(c)) // Накапливаем целую часть
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.') // Накапливаем дробную часть
        while (isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    return NUMBER;
}
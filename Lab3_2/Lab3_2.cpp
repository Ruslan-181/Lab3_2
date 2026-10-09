#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <locale.h>

#include "func.h"





int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "uk_UA.UTF-8");

    double a = 1.0, b = 2.0;
    double eps = 0.00001;
    int max_iter = 10;
    int choice;
    int debug = 0;

    while (1) {
        printf("\n==================================================\n");
        printf("  f(x) = x^3 - x - 4 = 0  на проміжку [%.1f, %.1f]\n", a, b);
        printf("==================================================\n");
        printf("1. Метод половинного ділення\n");
        printf("2. Метод хорд\n");
        printf("3. Порівняти обидва методи\n");
        printf("4. Змінити параметри (a, b, eps, max_iter)\n");
        printf("5. Переключити режим налагодження (зараз: %s)\n", debug ? "УВІМКНЕНО" : "ВИМКНЕНО");
        printf("0. Вихід\n");
        printf("--------------------------------------------------\n");
        printf("Оберіть пункт: ");

        system("cls");
    }

    return 0;
}
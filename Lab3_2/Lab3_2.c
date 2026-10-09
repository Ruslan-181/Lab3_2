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
        if (scanf("%d", &choice) != 1) {
            printf("Помилка вводу! Будь ласка, введіть число.\n");
            clear_input_buffer();
            continue;
        }
        switch (choice) {
        case 1:
            solve_bisection(a, b, eps, max_iter, debug);
            break;
        case 2:
            solve_chord(a, b, eps, max_iter, debug);
            break;
        case 3:
            printf("\n--- ВИКОНАННЯ МЕТОДУ ПОЛОВИННОГО ДІЛЕННЯ ---");
            solve_bisection(a, b, eps, max_iter, debug);
            printf("\n--- ВИКОНАННЯ МЕТОДУ ХОРД ---");
            solve_chord(a, b, eps, max_iter, debug);
            break;
        case 4:
            printf("Введіть a: ");
            if (scanf("%lf", &a) != 1) { clear_input_buffer(); break; }

            printf("Введіть b: ");
            if (scanf("%lf", &b) != 1) { clear_input_buffer(); break; }

            printf("Введіть точність eps (наприклад 0.00001): ");
            if (scanf("%lf", &eps) != 1) { clear_input_buffer(); break; }

            printf("Введіть max_iter: ");
            if (scanf("%d", &max_iter) != 1) { clear_input_buffer(); break; }

            printf("Параметри успішно оновлено.\n");
            break;
        case 5:
            debug = !debug;
            printf("Режим налагодження %s.\n", debug ? "увімкнено" : "вимкнено");
            break;
        case 0:
            printf("Завершення роботи програми. До побачення!\n");
            return 0;
        default:
            printf("Некоректний вибір. Спробуйте ще раз.\n");
        }
       

    return 0;
}
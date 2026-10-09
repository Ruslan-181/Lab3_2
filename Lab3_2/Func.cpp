#ifndef FUNCS_H
#define FUNCS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <time.h>

// Функція рівняння: f(x) = x^3 - x - 4
double f(double x) {
    return x * x * x - x - 4.0;
}

// Похідна функції: f'(x) = 3x^2 - 1
double df(double x) {
    return 3.0 * x * x - 1.0;
}

// Допоміжна функція обробки перевищення ітерацій
// Повертає: 1 - продовжити ще на max_iter, 2 - до кінця, 0 - перервати
int handle_max_iter(int current_iter, double current_x, double current_f) {
    int choice;
    printf("\n[УВАГА] Перевищено ліміт ітерацій (%d)!\n", current_iter);
    printf("Поточне наближення кореня x = %.8lf, f(x) = %.8e\n", current_x, current_f);
    printf("Оберіть дію:\n");
    printf("  1. Продовжити ще на стільки ж ітерацій\n");
    printf("  2. Виконати до кінця (поки не досягнемо eps)\n");
    printf("  3. Перервати обчислення та вивести поточний результат\n");
    printf("Ваш вибір: ");
    if (scanf("%d", &choice) != 1) return 0;

    if (choice == 1) return 1;
    if (choice == 2) return 2;
    return 0;
}

// Метод половинного ділення
void solve_bisection(double a, double b, double eps, int max_iter, int debug) {
    clock_t start_time = clock();

    if (f(a) * f(b) >= 0) {
        printf("\nПомилка: f(a) та f(b) повинні мати різні знаки на проміжку [%.2f, %.2f]!\n", a, b);
        return;
    }

    double c = a;
    int iter = 0;
    int total_limit = max_iter;
    int run_to_end = 0;

    if (debug) {
        printf("\n--- Налагодження: Метод половинного ділення ---\n");
        printf("Ітер |       a       |       b       |       c       |     f(c)     \n");
        printf("------------------------------------------------------------------\n");
    }

    while (1) {
        iter++;
        c = (a + b) / 2.0;

        if (debug) {
            printf("%4d | %13.8lf | %13.8lf | %13.8lf | %12.4e\n", iter, a, b, c, f(c));
        }

        if (fabs(f(c)) < eps || (b - a) / 2.0 < eps) {
            break;
        }

        if (f(a) * f(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }

        // Перевірка перевищення кількості ітерацій
        if (!run_to_end && iter >= total_limit) {
            int action = handle_max_iter(iter, c, f(c));
            if (action == 1) {
                total_limit += max_iter;
            }
            else if (action == 2) {
                run_to_end = 1;
            }
            else {
                printf("\nОбчислення примусово зупинено користувачем.\n");
                break;
            }
        }
    }

    clock_t end_time = clock();
    double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n=== Результат (Метод половинного ділення) ===\n");
    printf("Корінь x*          = %.8lf\n", c);
    printf("Значення f(x*)     = %.8e\n", f(c));
    printf("Кількість ітерацій = %d\n", iter);
    printf("Затрачений час     = %.6f сек.\n", cpu_time);
}

// Метод хорд
void solve_chord(double a, double b, double eps, int max_iter, int debug) {
    clock_t start_time = clock();

    if (f(a) * f(b) >= 0) {
        printf("\nПомилка: f(a) та f(b) повинні мати різні знаки на проміжку [%.2f, %.2f]!\n", a, b);
        return;
    }

    double x_prev = a;
    double x_curr = b;
    double x_next = x_curr;
    int iter = 0;
    int total_limit = max_iter;
    int run_to_end = 0;

    if (debug) {
        printf("\n--- Налагодження: Метод хорд ---\n");
        printf("Ітер |       x_curr      |     f(x_curr)    |       |x_next - x_curr|\n");
        printf("---------------------------------------------------------------------\n");
    }

    while (1) {
        iter++;

        // Формула хорд
        x_next = x_curr - f(x_curr) * (x_curr - x_prev) / (f(x_curr) - f(x_prev));

        if (debug) {
            printf("%4d | %17.8lf | %16.4e | %22.8lf\n", iter, x_next, f(x_next), fabs(x_next - x_curr));
        }

        if (fabs(f(x_next)) < eps || fabs(x_next - x_curr) < eps) {
            break;
        }

        x_prev = x_curr;
        x_curr = x_next;

        // Перевірка перевищення кількості ітерацій
        if (!run_to_end && iter >= total_limit) {
            int action = handle_max_iter(iter, x_next, f(x_next));
            if (action == 1) {
                total_limit += max_iter;
            }
            else if (action == 2) {
                run_to_end = 1;
            }
            else {
                printf("\nОбчислення примусово зупинено користувачем.\n");
                break;
            }
        }
    }

    clock_t end_time = clock();
    double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n=== Результат (Метод хорд) ===\n");
    printf("Корінь x*          = %.8lf\n", x_next);
    printf("Значення f(x*)     = %.8e\n", f(x_next));
    printf("Кількість ітерацій = %d\n", iter);
    printf("Затрачений час     = %.6f сек.\n", cpu_time);
}

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#endif
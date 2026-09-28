#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
    double a, b, c;
    double x_start, x_end, dx;

    printf("Введите a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Ошибка ввода коэффициентов.\n");
        return EXIT_FAILURE;
    }

    printf("Введите Xнач, Xкон, dx: ");
    if (scanf("%lf %lf %lf", &x_start, &x_end, &dx) != 3) {
        fprintf(stderr, "Ошибка ввода параметров интервала.\n");
        return EXIT_FAILURE;
    }

    if (dx == 0.0) {
        fprintf(stderr, "Ошибка: dx не может быть равен нулю.\n");
        return EXIT_FAILURE;
    }

    if ((x_start < x_end && dx < 0.0) ||
        (x_start > x_end && dx > 0.0)) {
        fprintf(stderr, "Ошибка: знак dx не соответствует направлению интервала.\n");
        return EXIT_FAILURE;
    }

    if (a < INT_MIN || a > INT_MAX ||
        b < INT_MIN || b > INT_MAX ||
        c < INT_MIN || c > INT_MAX) {
        fprintf(stderr, "Ошибка: целые части a, b, c выходят за диапазон int.\n");
        return EXIT_FAILURE;
    }

    int ac = (int)a;
    int bc = (int)b;
    int cc = (int)c;

    // НЕ(Ац ИЛИ Вц ИЛИ Сц) != 0
    int is_real = ~(ac | bc | cc) != 0;

    printf("\n+------------+------------+\n");
    printf("|     X      |     F      |\n");
    printf("+------------+------------+\n");

    for (int i = 0; ; ++i) {
        double x = x_start + i * dx;

        if ((dx > 0.0 && x > x_end) ||
            (dx < 0.0 && x < x_end)) {
            break;
        }

        double f;

        if (x < 0.0 && b != 0.0) {
            f = -a * x * x + b;
        }
        else if (x > 0.0 && b == 0.0) {
            if (x == c) {
                printf("| %10.4f |   ERROR    |\n", x);
                continue;
            }

            f = x / (x - c) + 5.5;
        }
        else {
            if (c == 0.0) {
                printf("| %10.4f |   ERROR    |\n", x);
                continue;
            }

            f = -x / c;
        }

        if (is_real) {
            printf("| %10.4f | %10.4f |\n", x, f);
        }
        else {
            if (f < INT_MIN || f > INT_MAX) {
                printf("| %10.4f |   ERROR    |\n", x);
            }
            else {
                printf("| %10.4f | %10d |\n", x, (int)f);
            }
        }
    }

    printf("+------------+------------+\n");

    return EXIT_SUCCESS;
}
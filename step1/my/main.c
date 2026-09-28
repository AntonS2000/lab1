#include <stdio.h>

int main() {
    double a, b, c;
    double x_start, x_end, dx;
    double x, F;

    printf("Введите значения a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    printf("Введите значения Xнач, Xкон, dx: ");
    if (scanf("%lf %lf %lf", &x_start, &x_end, &dx) != 3) {
        printf("Ошибка ввода параметров интервала!\n");
        return 1;
    }

    if (dx == 0) {
        printf("dx не может быть равен нулю!\n");
        return 1;
    }

    if ((x_start < x_end && dx < 0) ||
        (x_start > x_end && dx > 0)) {
        printf("Неправильное направление dx!\n");
        return 1;
    }

    int Ac = (int)a;
    int Bc = (int)b;
    int Cc = (int)c;

    // НЕ(Ac ИЛИ Bc ИЛИ Cc)
    int condition = ~(Ac | Bc | Cc);

    printf("\n=========================\n");
    printf("|   X       |   F       |\n");
    printf("=========================\n");

    int i = 0;

    while (1) {
        x = x_start + i * dx;

        if ((dx > 0 && x > x_end) ||
            (dx < 0 && x < x_end)) {
            break;
        }

        int error = 0;

        if (x < 0 && b != 0) {
            F = -a * x * x + b;
        }
        else if (x > 0 && b == 0) {
            if (x == c) {
                error = 1;
            }
            else {
                F = x / (x - c) + 5.5;
            }
        }
        else {
            if (c == 0) {
                error = 1;
            }
            else {
                F = -x / c;
            }
        }

        if (error) {
            printf("| %-9.2f | ERROR     |\n", x);
        }
        else if (condition != 0) {
            printf("| %-9.2f | %-9.2f |\n", x, F);
        }
        else {
            printf("| %-9.2f | %-9d |\n", x, (int)F);
        }

        i++;
    }

    printf("=========================\n");

    return 0;
}
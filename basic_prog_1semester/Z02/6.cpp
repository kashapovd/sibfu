#include <iostream>
#include <math.h>

int main() {
        double a, b, c, d, x1, x2;

        printf("a, b, c: ");
        scanf("%lf, %lf, %lf", &a, &b, &c);

        d = b * b - 4 * a * c;

        if ( a == 0 && b == 0 ) {
            printf("the equation no has root\n");
        }
        else if ( d == 0 ) {
                x1 =  -b / (2 * a);
                printf("x1 = %.1f\n", x1);
        }
        else if ( d > 0 ) {
                x1 = ( -b + sqrt(d)) / 2 * a;
                x2 = ( -b - sqrt(d)) / 2 * a;
                printf("x1 = %.1f, x2 = %.1f\n", x1, x2);
        }
        else if ( d < 0 ) printf("the equation no has root\n");
}

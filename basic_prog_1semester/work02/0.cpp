#include <iostream>

int main()
{
    int a, b, cmp, dif;
    long sum;
    float avr;

    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("\n");

    sum = a + b;
    dif = a - b;
    cmp = a * b;
    avr = ( (float)a + (float)b ) / 2;

    printf("sum(%%ld) = %ld\n", sum);
    printf("sum(%%10ld) = %10ld\n", sum);
    printf("sum(%%-10ld) = %-10ld\n", sum);
    printf("\n");

    printf("dif(%%d) = %d\n", dif);
    printf("dif(%%10d) = %10d\n", dif);
    printf("dif(%%-10d) = %-10d\n", dif);
    printf("\n");

    printf("cmp(%%d) = %d\n", cmp);
    printf("cmp(%%10d) = %10d\n", cmp);
    printf("cmp(%%-10d) = %-10d\n", cmp);
    printf("\n");

    printf("avr(%%f) = %f\n", avr);
    printf("avr(%%15.4f) = %15.4f\n", avr);
    printf("avr(%%-15.4f) = %-15.4f\n", avr);
    printf("avr(%%0.15f) = %0.15f\n", avr);
    printf("avr(%%30.15f) = %30.15f\n", avr);

}

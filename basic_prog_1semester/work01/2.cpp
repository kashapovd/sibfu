#include <iostream>

int main()
{
    double oneDollar_rub, oneEuro_rub, sum_rub, dollar, euro;


    printf("1 dollar(rub) = ");
    scanf("%lf", &oneDollar_rub);
    printf("1 euro(rub) = ");
    scanf("%lf", &oneEuro_rub);
    printf("How much money do you have?(rub): ");
    scanf("%lf", &sum_rub);

    dollar = sum_rub / oneDollar_rub;
    euro = sum_rub / oneEuro_rub;

    printf("For %.1lf rubles you can buy %.1f dollar(s) "
            "or %.1lf euro\n", sum_rub, dollar, euro);
}

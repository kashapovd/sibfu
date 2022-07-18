#include <iostream>

int main()
{
        float x;
        int a, b, c, d;

        printf("a, b, c, d: ");
        scanf("%d, %d, %d, %d", &a, &b, &c, &d);
        printf("x:  ");
        scanf("%f", &x);

        if ( (a <= x && x <= b) || (c <= x && x <= b) ) {
                printf("x ∈ [%d; %d] ∪ [%d; %d]\n", a, b, c, d);
        }
        else printf("x ∉ [%d; %d] ∪ [%d; %d]\n", a, b, c, d);
}

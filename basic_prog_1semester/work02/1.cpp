#include <iostream>
#include <math.h>
int main()
{
    int V1, V2, S1, S2, T, S, St;

    printf("V1 = ");
    scanf("%d", &V1);
    printf("V2 = ");
    scanf("%d", &V2);
    printf("S = ");
    scanf("%d", &S);
    printf("T = ");
    scanf("%d", &T);

    S1 = V1 * T;
    S2 = V2 * T;
    St = abs(S - ( S1 + S2 ));

    printf("Distance after %d hour(s) = %dkm\n", T, St);
}

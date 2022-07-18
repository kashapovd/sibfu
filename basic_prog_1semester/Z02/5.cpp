#include <iostream>

int main() {
        float a1, a2, b1, b2;

        printf("A[a1, a2] | a1, a2: ");
        scanf("%f, %f", &a1, &a2);
        printf("B[b1, b2] | b1, b2: ");
        scanf("%f, %f", &b1, &b2);

        if( a1 == b1 && a2 == b2 ) {
            printf("A = B\n");
        }
        else if( a1 >= b1 && a2 <= b2) {
            printf("A inside B\n");
        }
        else if( a1 <= b1 && a2 >= b2 ) {
            printf("B inside A\n");
        }
        else if(( b1 >= a1 && b1 <= a2) || (b2 <= a2 && b2 >= a1 )) {
            printf("other intersection\n");
        }
        else printf("no intersection\n");
}

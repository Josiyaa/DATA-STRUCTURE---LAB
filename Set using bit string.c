#include <stdio.h>

typedef unsigned int BitSet;

/* Function to insert an element into a bitset */
BitSet insert(BitSet set, int element) {
    return set | (1 << element);
}

/* Function to print a set */
void printSet(BitSet set) {
    printf("{ ");
    for (int i = 0; i < 32; i++) {
        if (set & (1 << i))
            printf("%d ", i);
    }
    printf("}");
}

/* Bitwise Union */
BitSet setUnion(BitSet A, BitSet B) {
    return A | B;
}

/* Bitwise Intersection */
BitSet setIntersection(BitSet A, BitSet B) {
    return A & B;
}

/* Bitwise Difference: A - B */
BitSet setDifference(BitSet A, BitSet B) {
    return A & (~B);
}

int main() {
    BitSet A = 0, B = 0;
    int n1, n2, x;

    printf("Enter number of elements in Set A: ");
    scanf("%d", &n1);

    printf("Enter elements of Set A:\n");
    for (int i = 0; i < n1; i++) {
        scanf("%d", &x);
        A = insert(A, x);
    }

    printf("Enter number of elements in Set B: ");
    scanf("%d", &n2);

    printf("Enter elements of Set B:\n");
    for (int i = 0; i < n2; i++) {
        scanf("%d", &x);
        B = insert(B, x);
    }

    printf("\nSet A = ");
    printSet(A);

    printf("\nSet B = ");
    printSet(B);

    BitSet U = setUnion(A, B);
    BitSet I = setIntersection(A, B);
    BitSet D = setDifference(A, B);

    printf("\n\nUnion (A ∪ B) = ");
    printSet(U);

    printf("\nIntersection (A ∩ B) = ");
    printSet(I);

    printf("\nDifference (A − B) = ");
    printSet(D);

    printf("\n");
    return 0;
}

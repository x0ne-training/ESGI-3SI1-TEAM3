#include <stdio.h>

float func_addition() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 + nb2;
}

float func_soustraction() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 - nb2;
}

float func_multiplication() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 * nb2;
}

float func_division() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);

    do {
        printf("Entrez le deuxième nombre : ");
        scanf("%f", &nb2);
        if (nb2 == 0) {
            printf("Impossible : division par zéro. Veuillez entrer un autre nombre.\n");
        }
    } while (nb2 == 0);

    return nb1 / nb2;
}


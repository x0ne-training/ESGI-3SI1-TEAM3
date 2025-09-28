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
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    if (nb2 == 0) {
        printf("Erreur : division par zéro !\n");
        return 0;
    }
    return nb1 / nb2;
}

#include <stdio.h>
#include "fonction.h"

int main() {
    char choix;
    printf("Sélectionner l'option que vous voulez utiliser :\n");
    printf("1 : Addition\n2 : Soustraction\n3 : Multiplication\n4 : Division\n");
    scanf(" %c", &choix);

    switch (choix) {
        case '1':
            printf("Résultat : %f\n", func_addition());
            break;
        case '2':
            printf("Résultat : %f\n", func_soustraction());
            break;
        case '3':
            printf("Résultat : %f\n", func_multiplication());
            break;
        case '4':
            printf("Résultat : %f\n", func_division());
            break;
        default:
            printf("Option invalide.\n");
    }

    return 0;
}

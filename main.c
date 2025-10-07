#include <stdio.h>
#include "fonction.h"

int main() {
    char choix;
    printf("Sélectionner l'option que vous voulez utiliser :\n");
    printf("1 : Addition\n2 : Soustraction\n3 : Multiplication\n4 : Division\n" 
           "5 : Carré\n6 : Racine carrée\n7 : Puissance\n8 : Modulus\n9 : Factorielle\n"
           "a : Logarithme\nb : Exponentielle\nc : Sinus\nd : Cosinus\ne : Tangente\n");
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
        case '5':
            printf("Résultat : %f\n", func_square());
            break;
        case '6':
            printf("Résultat : %f\n", func_square_root());
            break;
        case '7':
            printf("Résultat : %f\n", func_power());
            break;
        case '8':
            printf("Résultat : %f\n", func_modulus());
            break;
        case '9':
            printf("Résultat : %f\n", func_factorial());
            break;
        case 'a':
            printf("Résultat : %lf\n", func_logarithm());
            break;
        case 'b':
            printf("Résultat : %f\n", func_exponential());
            break;
        case 'c':
            printf("Résultat : %f\n", func_sine());
            break;
        case 'd':
            printf("Résultat : %f\n", func_cosine());
            break;
        case 'e':
            printf("Résultat : %f\n", func_tangent());
            break;
        default:
            printf("Option invalide.\n");
    }

    return 0;
}

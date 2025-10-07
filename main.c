#include <stdio.h>
#include "fonction.h"

int main() {
    char choix;
    char continuer = 'r';

    while (continuer == 'r') {


        // Ce contenu devra être remplacer par les points 1 et 2 du github :
        // Fonction pour parser l'entrée et Fonction pour évaluer l'expression parser.
        printf("Sélectionner l'option que vous voulez utiliser :\n");
        printf("1 : Addition\n2 : Soustraction\n3 : Multiplication\n4 : Division\n");
        printf("Entrez votre choix (1-4) : ");
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
                break;
        }

        printf("\nSouhaitez-vous recommencer (r) ou quitter (q) ? ");
        scanf(" %c", &continuer);

        while (continuer != 'r' && continuer != 'q') {
            printf("Entrée invalide. Tapez 'r' pour recommencer ou 'q' pour quitter : ");
            scanf(" %c", &continuer);
        }
    }

    printf("Merci d'avoir utilisé la calculatrice !\n");
    return 0;
}

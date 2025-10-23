/*#include <stdio.h>
#include "fonction.h"

int main() {
    char choix;
    char continuer = 'r';

    while (continuer == 'r') {
        printf("Sélectionner l'option que vous voulez utiliser :\n");
        printf("1 : Addition\n2 : Soustraction\n3 : Multiplication\n4 : Division\n" 
               "5 : Carré\n6 : Racine carrée\n7 : Puissance\n8 : Modulus\n9 : Factorielle\n"
               "a : Logarithme\nb : Exponentielle\nc : Sinus\nd : Cosinus\ne : Tangente\n");
        printf("Entrez votre choix : ");
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
*/


/*
 * ============================================================================
 * Fichier: main.c
 * Description: Programme principal de la calculatrice scientifique.
 *              Supporte deux modes d'utilisation:
 *              1. Mode interactif (sans arguments)
 *              2. Mode ligne de commande (avec arguments)
 * 
 * Compilation:
 *   gcc main.c fonction.c affichage.c -o calculatrice -lm
 * 
 * Utilisation:
 *   Mode interactif: ./calculatrice
 *   Mode ligne de commande: ./calculatrice <operation> <nb1> [nb2] [precision]
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"
#include "affichage.h"

/*
 * ============================================================================
 * FONCTION: mode_ligne_commande
 * ============================================================================
 */
int mode_ligne_commande(int argc, char *argv[]) {
    // Variables pour stocker les opérandes et le résultat
    double nb1, nb2, resultat;
    
    // Variable pour stocker la précision d'affichage
    int precision = PRECISION_DEFAUT;
    
    // Buffer pour construire l'expression mathématique textuelle
    char expression[256];
    
    /*
     * ETAPE 1: VALIDATION DU NOMBRE D'ARGUMENTS
     * ------------------------------------------
     * Un minimum de 3 arguments est requis:
     * argv[0] = nom du programme
     * argv[1] = opération
     * argv[2] = au moins un nombre
     */
    if (argc < 3) {
        afficher_erreur_stylee("Nombre d'arguments insuffisant");
        afficher_aide(argv[0]);
        return 1;
    }
    
    /*
     * ETAPE 2: EXTRACTION DU PREMIER NOMBRE
     * --------------------------------------
     * atof() convertit une chaîne de caractères en double
     * Exemple: "3.14" devient 3.14
     */
    nb1 = atof(argv[2]);
    
    /*
     * ETAPE 3: DETERMINATION DE LA PRECISION
     * ---------------------------------------
     * La précision peut être spécifiée comme dernier argument.
     * On vérifie si le dernier argument est un nombre entre 0 et 10.
     */
    char* dernier_arg = argv[argc - 1];
    int derniere_valeur = atoi(dernier_arg);
    
    // Si le dernier argument est un nombre valide (0-10) et différent du premier nombre
    if (derniere_valeur >= 0 && derniere_valeur <= 10 && argc > 3) {
        // On vérifie que ce n'est pas le premier nombre converti par erreur
        if (strcmp(dernier_arg, argv[2]) != 0) {
            precision = derniere_valeur;
        }
    }
    
    /*
     * ETAPE 4: IDENTIFICATION ET EXECUTION DE L'OPERATION
     * ----------------------------------------------------
     * Utilisation de strcmp() pour comparer les chaînes de caractères.
     * strcmp() retourne 0 si les chaînes sont identiques.
     */
    
    // =======================================================================
    // OPERATIONS BINAIRES (nécessitent deux nombres)
    // =======================================================================
    
    if (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "addition") == 0) {
        /*
         * ADDITION: nb1 + nb2
         * Vérifie qu'un second nombre est fourni
         */
        if (argc < 4) {
            afficher_erreur_stylee("L'addition nécessite deux nombres");
            return 1;
        }
        nb2 = atof(argv[3]);
        resultat = nb1 + nb2;
        // Construction de l'expression pour l'affichage
        sprintf(expression, "%.10g + %.10g", nb1, nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "sub") == 0 || strcmp(argv[1], "soustraction") == 0) {
        /*
         * SOUSTRACTION: nb1 - nb2
         */
        if (argc < 4) {
            afficher_erreur_stylee("La soustraction nécessite deux nombres");
            return 1;
        }
        nb2 = atof(argv[3]);
        resultat = nb1 - nb2;
        sprintf(expression, "%.10g - %.10g", nb1, nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "mul") == 0 || strcmp(argv[1], "multiplication") == 0) {
        /*
         * MULTIPLICATION: nb1 * nb2
         */
        if (argc < 4) {
            afficher_erreur_stylee("La multiplication nécessite deux nombres");
            return 1;
        }
        nb2 = atof(argv[3]);
        resultat = nb1 * nb2;
        sprintf(expression, "%.10g × %.10g", nb1, nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "div") == 0 || strcmp(argv[1], "division") == 0) {
        /*
         * DIVISION: nb1 / nb2
         * Vérifie que le diviseur n'est pas zéro
         */
        if (argc < 4) {
            afficher_erreur_stylee("La division nécessite deux nombres");
            return 1;
        }
        nb2 = atof(argv[3]);
        
        // Protection contre la division par zéro
        if (nb2 == 0) {
            afficher_erreur_stylee("Division par zéro impossible");
            return 1;
        }
        
        resultat = nb1 / nb2;
        sprintf(expression, "%.10g ÷ %.10g", nb1, nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "pow") == 0 || strcmp(argv[1], "puissance") == 0) {
        /*
         * PUISSANCE: nb1 ^ nb2
         * Utilise la fonction pow() de math.h
         */
        if (argc < 4) {
            afficher_erreur_stylee("La puissance nécessite deux nombres (base et exposant)");
            return 1;
        }
        nb2 = atof(argv[3]);
        resultat = pow(nb1, nb2);
        sprintf(expression, "%.10g ^ %.10g", nb1, nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "mod") == 0 || strcmp(argv[1], "modulo") == 0) {
        /*
         * MODULO: nb1 % nb2
         * Fonctionne uniquement avec des entiers
         */
        if (argc < 4) {
            afficher_erreur_stylee("Le modulo nécessite deux nombres entiers");
            return 1;
        }
        nb2 = atof(argv[3]);
        
        // Protection contre le modulo par zéro
        if ((int)nb2 == 0) {
            afficher_erreur_stylee("Modulo par zéro impossible");
            return 1;
        }
        
        // Conversion en entiers pour l'opération modulo
        resultat = (int)nb1 % (int)nb2;
        sprintf(expression, "%d %% %d", (int)nb1, (int)nb2);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    // =======================================================================
    // OPERATIONS UNAIRES (nécessitent un seul nombre)
    // =======================================================================
    
    else if (strcmp(argv[1], "square") == 0 || strcmp(argv[1], "carre") == 0) {
        /*
         * CARRE: nb1^2
         * Multiplie le nombre par lui-même
         */
        resultat = nb1 * nb1;
        sprintf(expression, "(%.10g)²", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "sqrt") == 0 || strcmp(argv[1], "racine") == 0) {
        /*
         * RACINE CARREE: √nb1
         * Vérifie que le nombre est positif
         */
        if (nb1 < 0) {
            afficher_erreur_stylee("Impossible de calculer la racine carrée d'un nombre négatif");
            return 1;
        }
        resultat = sqrt(nb1);
        sprintf(expression, "√(%.10g)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "fact") == 0 || strcmp(argv[1], "factorielle") == 0) {
        /*
         * FACTORIELLE: nb1!
         * Vérifie que le nombre est un entier positif
         * Calcule le produit de tous les entiers de 1 à nb1
         */
        if (nb1 < 0) {
            afficher_erreur_stylee("La factorielle n'est définie que pour les entiers positifs");
            return 1;
        }
        
        // Calcul de la factorielle
        unsigned long long fact = 1;
        for (int i = 1; i <= (int)nb1; i++) {
            fact *= i;
        }
        resultat = (double)fact;
        sprintf(expression, "%d!", (int)nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "ln") == 0 || strcmp(argv[1], "log") == 0) {
        /*
         * LOGARITHME NATUREL: ln(nb1)
         * Vérifie que le nombre est strictement positif
         */
        if (nb1 <= 0) {
            afficher_erreur_stylee("Le logarithme n'est défini que pour les nombres strictement positifs");
            return 1;
        }
        resultat = log(nb1);
        sprintf(expression, "ln(%.10g)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "exp") == 0 || strcmp(argv[1], "exponentielle") == 0) {
        /*
         * EXPONENTIELLE: e^nb1
         * Calcule e (nombre d'Euler ≈ 2.718) élevé à la puissance nb1
         */
        resultat = exp(nb1);
        sprintf(expression, "e^(%.10g)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "sin") == 0 || strcmp(argv[1], "sinus") == 0) {
        /*
         * SINUS: sin(nb1)
         * L'argument doit être en radians
         */
        resultat = sin(nb1);
        sprintf(expression, "sin(%.10g rad)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "cos") == 0 || strcmp(argv[1], "cosinus") == 0) {
        /*
         * COSINUS: cos(nb1)
         * L'argument doit être en radians
         */
        resultat = cos(nb1);
        sprintf(expression, "cos(%.10g rad)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    else if (strcmp(argv[1], "tan") == 0 || strcmp(argv[1], "tangente") == 0) {
        /*
         * TANGENTE: tan(nb1)
         * L'argument doit être en radians
         * Attention: indéfinie pour π/2 + kπ
         */
        resultat = tan(nb1);
        sprintf(expression, "tan(%.10g rad)", nb1);
        afficher_resultat_stylee(expression, resultat, precision);
        return 0;
    }
    
    // =======================================================================
    // OPERATION INCONNUE
    // =======================================================================
    else {
        /*
         * Si l'opération n'est reconnue dans aucun des cas ci-dessus,
         * afficher un message d'erreur et l'aide
         */
        char message_erreur[256];
        sprintf(message_erreur, "Opération inconnue: '%s'", argv[1]);
        afficher_erreur_stylee(message_erreur);
        afficher_aide(argv[0]);
        return 1;
    }
}


/*
 * ============================================================================
 * FONCTION: mode_interactif
 * ============================================================================
 */
void mode_interactif(void) {
    char choix;
    char continuer = 'r';
    float resultat;
    char expression[256];
    
    /*
     * DEMANDE DE LA PRECISION AU DEBUT
     * ---------------------------------
     * L'utilisateur choisit une fois la précision qui sera utilisée
     * pour tous les calculs de la session
     */
    int precision = obtenir_precision_utilisateur();
    
    /*
     * AFFICHAGE DU TITRE DE LA CALCULATRICE
     * --------------------------------------
     * Utilise la fonction d'affichage stylisé pour un en-tête visuellement attractif
     */
    printf("\n");
    afficher_titre("CALCULATRICE SCIENTIFIQUE - MODE INTERACTIF");
    printf("\n");
    
    /*
     * BOUCLE PRINCIPALE DU MODE INTERACTIF
     * -------------------------------------
     * Continue tant que l'utilisateur choisit 'r' (recommencer)
     */
    while (continuer == 'r') {
        /*
         * AFFICHAGE DU MENU DES OPERATIONS
         * ---------------------------------
         * Affiche toutes les opérations disponibles avec leurs codes
         */
        printf("Sélectionner l'option que vous voulez utiliser :\n");
        printf("  1 : Addition\n  2 : Soustraction\n  3 : Multiplication\n  4 : Division\n");
        printf("  5 : Carré\n  6 : Racine carrée\n  7 : Puissance\n  8 : Modulus\n  9 : Factorielle\n");
        printf("  a : Logarithme\n  b : Exponentielle\n  c : Sinus\n  d : Cosinus\n  e : Tangente\n");
        printf("\nEntrez votre choix : ");
        scanf(" %c", &choix);
        
        /*
         * TRAITEMENT DU CHOIX DE L'UTILISATEUR
         * -------------------------------------
         * Chaque cas appelle la fonction correspondante du fichier fonction.c
         * et affiche le résultat de manière stylisée
         */
        switch (choix) {
            case '1':
                /*
                 * ADDITION
                 * La fonction func_addition() demande les nombres et retourne le résultat
                 */
                resultat = func_addition();
                sprintf(expression, "Addition");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '2':
                /*
                 * SOUSTRACTION
                 */
                resultat = func_soustraction();
                sprintf(expression, "Soustraction");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '3':
                /*
                 * MULTIPLICATION
                 */
                resultat = func_multiplication();
                sprintf(expression, "Multiplication");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '4':
                /*
                 * DIVISION
                 */
                resultat = func_division();
                sprintf(expression, "Division");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '5':
                /*
                 * CARRE
                 */
                resultat = func_square();
                sprintf(expression, "Carré");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '6':
                /*
                 * RACINE CARREE
                 */
                resultat = func_square_root();
                sprintf(expression, "Racine carrée");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '7':
                /*
                 * PUISSANCE
                 */
                resultat = func_power();
                sprintf(expression, "Puissance");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '8':
                /*
                 * MODULUS
                 */
                resultat = func_modulus();
                sprintf(expression, "Modulus");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case '9':
                /*
                 * FACTORIELLE
                 */
                resultat = func_factorial();
                sprintf(expression, "Factorielle");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case 'a':
                /*
                 * LOGARITHME NATUREL
                 * Note: func_logarithm() retourne un double
                 */
                resultat = (float)func_logarithm();
                sprintf(expression, "Logarithme naturel");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case 'b':
                /*
                 * EXPONENTIELLE
                 */
                resultat = func_exponential();
                sprintf(expression, "Exponentielle");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case 'c':
                /*
                 * SINUS
                 */
                resultat = func_sine();
                sprintf(expression, "Sinus");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case 'd':
                /*
                 * COSINUS
                 */
                resultat = func_cosine();
                sprintf(expression, "Cosinus");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            case 'e':
                /*
                 * TANGENTE
                 */
                resultat = func_tangent();
                sprintf(expression, "Tangente");
                afficher_resultat_stylee(expression, resultat, precision);
                break;
                
            default:
                /*
                 * CHOIX INVALIDE
                 * Si le choix ne correspond à aucune option, afficher une erreur
                 */
                afficher_erreur_stylee("Option invalide. Veuillez choisir une option du menu.");
                break;
        }
        
        /*
         * DEMANDE DE CONTINUATION
         * -----------------------
         * Demande à l'utilisateur s'il souhaite effectuer un autre calcul
         * ou quitter le programme
         */
        printf("\nSouhaitez-vous recommencer (r) ou quitter (q) ? ");
        scanf(" %c", &continuer);
        
        /*
         * VALIDATION DE L'ENTREE
         * ----------------------
         * Tant que l'utilisateur n'entre pas 'r' ou 'q', redemander
         */
        while (continuer != 'r' && continuer != 'q') {
            printf("Entrée invalide. Tapez 'r' pour recommencer ou 'q' pour quitter : ");
            scanf(" %c", &continuer);
        }
        
        // Ligne vide pour espacer visuellement les calculs
        printf("\n");
    }
    
    /*
     * MESSAGE DE FIN
     * --------------
     * Affiche un message de remerciement stylisé quand l'utilisateur quitte
     */
    afficher_bordure('=');
    printf("  Merci d'avoir utilisé la calculatrice scientifique !\n");
    afficher_bordure('=');
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION PRINCIPALE: main
 * ============================================================================
 */
int main(int argc, char *argv[]) {
    /*
     * DETERMINATION DU MODE D'EXECUTION
     * ---------------------------------
     * argc = 1 signifie qu'il n'y a que le nom du programme (pas d'arguments)
     * argc > 1 signifie qu'il y a des arguments supplémentaires
     */
    
    if (argc > 1) {
        /*
         * MODE LIGNE DE COMMANDE
         * ----------------------
         * Des arguments ont été fournis, on lance le mode ligne de commande
         * Exemple: ./calculatrice add 5 3
         */
        
        // Vérification si l'utilisateur demande l'aide
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "--help") == 0 || 
            strcmp(argv[1], "-h") == 0) {
            afficher_aide(argv[0]);
            return 0;
        }
        
        // Exécution du calcul en mode ligne de commande
        return mode_ligne_commande(argc, argv);
        
    } else {
        mode_interactif();
        return 0;
    }
}
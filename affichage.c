/*
 * ============================================================================
 * Fichier: affichage.c
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "affichage.h"

/*
 * ============================================================================
 * CODES COULEURS ANSI POUR TERMINAL
 * ============================================================================
 */

#define COULEUR_RESET   "\033[0m"      // Réinitialise toutes les couleurs
#define COULEUR_ROUGE   "\033[1;31m"   // Rouge gras pour les erreurs
#define COULEUR_VERT    "\033[1;32m"   // Vert gras pour les succès
#define COULEUR_JAUNE   "\033[1;33m"   // Jaune gras pour les avertissements
#define COULEUR_BLEU    "\033[1;34m"   // Bleu gras pour les titres
#define COULEUR_CYAN    "\033[1;36m"   // Cyan gras pour les résultats


/*
 * ============================================================================
 * FONCTION: afficher_bordure
 * ============================================================================
 */
void afficher_bordure(char caractere) {
    // Boucle pour afficher LARGEUR_BORDURE fois le caractère
    for (int i = 0; i < LARGEUR_BORDURE; i++) {
        printf("%c", caractere);
    }
    // Retour à la ligne après la bordure
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION: afficher_titre
 * ============================================================================
 */
void afficher_titre(const char* titre) {
    // Bordure supérieure pour encadrer le titre
    afficher_bordure('=');
    
    // Calcul du nombre d'espaces pour centrer le titre
    // strlen(titre) donne la longueur du titre
    // (LARGEUR_BORDURE - strlen(titre)) / 2 calcule les espaces à gauche
    int espaces = (LARGEUR_BORDURE - strlen(titre)) / 2;
    
    // Affichage des espaces de centrage
    for (int i = 0; i < espaces; i++) {
        printf(" ");
    }
    
    // Affichage du titre en bleu gras
    printf("%s%s%s\n", COULEUR_BLEU, titre, COULEUR_RESET);
    
    afficher_bordure('=');
}


/*
 * ============================================================================
 * FONCTION: afficher_resultat_stylee
 * ============================================================================
 */
void afficher_resultat_stylee(const char* expression, double resultat, int precision) {
    // Si precision est -1 ou invalide, utiliser la précision par défaut
    // Cela permet de ne pas spécifier la précision à chaque appel
    if (precision < 0 || precision > 10) {
        precision = PRECISION_DEFAUT;
    }
    
    // Ligne de séparation avant le résultat pour le mettre en évidence
    afficher_bordure('-');
    
    // Affichage de l'expression calculée
    printf("  Expression calculée : \"%s\"\n", expression);
    
    // Le résultat est affiché en cyan pour le mettre en valeur
    printf("  %sRésultat%s            : %s%.*f%s\n", 
           COULEUR_VERT,          
           COULEUR_RESET,         
           COULEUR_CYAN,          
           precision,             
           resultat,              
           COULEUR_RESET);        
    
    afficher_bordure('-');
    
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION: afficher_erreur_stylee
 * ============================================================================
 */
void afficher_erreur_stylee(const char* message) {
    // Bordure supérieure avec des étoiles pour signaler une erreur
    printf("\n");
    afficher_bordure('*');
    
    // Affichage du message d'erreur en rouge gras
    printf("%s  ERREUR: %s%s\n", 
           COULEUR_ROUGE,    
           message,          
           COULEUR_RESET);   
    
    // Bordure inférieure pour fermer l'encadrement d'erreur
    afficher_bordure('*');
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION: obtenir_precision_utilisateur
 * ============================================================================
 */
int obtenir_precision_utilisateur(void) {
    int precision;
    int entree_valide = 0;  // Flag pour vérifier si l'entrée est correcte
    
    // Boucle jusqu'à obtenir une entrée valide
    do {
        // Affichage du prompt en couleur jaune pour attirer l'attention
        printf("\n%sChoisissez la précision d'affichage (0-10 décimales)%s\n", 
               COULEUR_JAUNE, COULEUR_RESET);
        printf("Précision souhaitée (défaut: %d) : ", PRECISION_DEFAUT);
        
        // Lecture de l'entrée utilisateur
        // scanf retourne 1 si la lecture a réussi
        if (scanf("%d", &precision) == 1) {
            // Vérification que la précision est dans la plage acceptable
            if (precision >= 0 && precision <= 10) {
                entree_valide = 1;  // Entrée correcte, on sort de la boucle
            } else {
                // Message d'erreur si la valeur est hors limites
                printf("%sErreur: La précision doit être entre 0 et 10.%s\n", 
                       COULEUR_ROUGE, COULEUR_RESET);
                // Vider le buffer d'entrée pour éviter les lectures erronées
                while(getchar() != '\n');
            }
        } else {
            // Message d'erreur si l'entrée n'est pas un nombre
            printf("%sErreur: Veuillez entrer un nombre entier.%s\n", 
                   COULEUR_ROUGE, COULEUR_RESET);
            // Vider le buffer d'entrée
            while(getchar() != '\n');
        }
    } while (!entree_valide);  // Continue tant que l'entrée n'est pas valide
    
    
    return precision;
}


/*
 * ============================================================================
 * FONCTION: afficher_aide
 * ============================================================================
 */
void afficher_aide(const char* nom_programme) {
    // Affichage du titre de l'aide
    afficher_titre("AIDE - UTILISATION EN LIGNE DE COMMANDE");
    
    printf("\n%sSYNTAXE:%s\n", COULEUR_VERT, COULEUR_RESET);
    printf("  %s <operation> <nombre1> [nombre2] [precision]\n\n", nom_programme);
    
    printf("%sOPERATIONS DISPONIBLES:%s\n", COULEUR_VERT, COULEUR_RESET);
    printf("  Operations binaires (nécessitent 2 nombres):\n");
    printf("    add          : Addition (ex: add 5 3)\n");
    printf("    sub          : Soustraction (ex: sub 10 4)\n");
    printf("    mul          : Multiplication (ex: mul 6 7)\n");
    printf("    div          : Division (ex: div 20 4)\n");
    printf("    pow          : Puissance (ex: pow 2 8)\n");
    printf("    mod          : Modulo (ex: mod 17 5)\n\n");
    
    printf("  Operations unaires (nécessitent 1 nombre):\n");
    printf("    sqrt         : Racine carrée (ex: sqrt 16)\n");
    printf("    square       : Carré (ex: square 5)\n");
    printf("    fact         : Factorielle (ex: fact 5)\n");
    printf("    ln           : Logarithme naturel (ex: ln 2.718)\n");
    printf("    exp          : Exponentielle (ex: exp 1)\n");
    printf("    sin          : Sinus (en radians) (ex: sin 1.57)\n");
    printf("    cos          : Cosinus (en radians) (ex: cos 3.14)\n");
    printf("    tan          : Tangente (en radians) (ex: tan 0.785)\n\n");
    
    printf("%sPRECISION (optionnelle):%s\n", COULEUR_VERT, COULEUR_RESET);
    printf("  Ajoutez un nombre entre 0 et 10 comme dernier argument\n");
    printf("  pour spécifier le nombre de décimales à afficher.\n");
    printf("  Par défaut: %d décimales\n\n", PRECISION_DEFAUT);
    
    printf("%sEXEMPLES D'UTILISATION:%s\n", COULEUR_VERT, COULEUR_RESET);
    printf("  %s add 15 27          # Addition: 15 + 27\n", nom_programme);
    printf("  %s sqrt 144           # Racine carrée de 144\n", nom_programme);
    printf("  %s div 10 3 4         # Division avec 4 décimales: 10 / 3\n", nom_programme);
    printf("  %s sin 1.5708 6       # Sinus de π/2 avec 6 décimales\n", nom_programme);
    printf("  %s pow 2 10           # 2 puissance 10\n\n", nom_programme);
    
    printf("%sNOTE:%s Sans arguments, le programme lance le mode interactif.\n\n", 
           COULEUR_JAUNE, COULEUR_RESET);
    
    afficher_bordure('=');
}
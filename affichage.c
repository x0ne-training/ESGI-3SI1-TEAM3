/*
 * ============================================================================
 * Fichier: affichage.c
 * Auteur: [Votre nom]
 * Description: Implémentation des fonctions d'affichage stylisé pour la
 *              calculatrice. Fournit des fonctions pour formatter les résultats
 *              avec des couleurs, bordures et une précision configurable.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "affichage.h"

/*
 * ============================================================================
 * CODES COULEURS ANSI POUR TERMINAL
 * ============================================================================
 * Ces codes permettent de colorer le texte dans les terminaux compatibles.
 * Note: Fonctionne sur Linux/Mac et Windows 10+ avec support ANSI.
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
 * Affiche une ligne horizontale décorative de longueur LARGEUR_BORDURE.
 * Cette fonction est utilisée pour créer des séparateurs visuels entre
 * les différentes sections de l'affichage.
 * 
 * Algorithme:
 *   1. Boucle de 0 à LARGEUR_BORDURE
 *   2. Affiche le caractère spécifié à chaque itération
 *   3. Termine par un retour à la ligne
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
 * Affiche un titre centré et encadré avec des bordures supérieure et inférieure.
 * Le titre est affiché en couleur bleue pour le mettre en évidence.
 * 
 * Algorithme:
 *   1. Affiche une bordure supérieure avec le caractère '='
 *   2. Centre le titre en calculant les espaces nécessaires
 *   3. Affiche le titre en couleur bleue
 *   4. Affiche une bordure inférieure
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
    
    // Bordure inférieure pour fermer l'encadrement
    afficher_bordure('=');
}


/*
 * ============================================================================
 * FONCTION: afficher_resultat_stylee
 * ============================================================================
 * Fonction principale d'affichage stylisé des résultats de calcul.
 * Elle formate le résultat avec l'expression qui a été calculée, utilise
 * des couleurs pour améliorer la lisibilité et respecte la précision demandée.
 * 
 * Paramètres détaillés:
 *   - expression: L'expression mathématique sous forme de texte (ex: "5 + 3")
 *   - resultat: La valeur numérique calculée (ex: 8.0)
 *   - precision: Nombre de décimales à afficher (-1 = utiliser la valeur par défaut)
 * 
 * Algorithme:
 *   1. Vérifie et ajuste la précision si nécessaire
 *   2. Affiche une ligne de séparation
 *   3. Affiche l'expression entre guillemets
 *   4. Affiche le résultat avec la précision spécifiée en couleur cyan
 *   5. Affiche une ligne de séparation finale
 */
void afficher_resultat_stylee(const char* expression, double resultat, int precision) {
    // Si precision est -1 ou invalide, utiliser la précision par défaut
    // Cela permet de ne pas spécifier la précision à chaque appel
    if (precision < 0 || precision > 10) {
        precision = PRECISION_DEFAUT;
    }
    
    // Ligne de séparation avant le résultat pour le mettre en évidence
    afficher_bordure('-');
    
    // Affichage de l'expression calculée entre guillemets
    // Le format %s permet d'insérer la chaîne de caractères
    printf("  Expression calculée : \"%s\"\n", expression);
    
    // Affichage du résultat avec la précision spécifiée
    // %.*f permet d'utiliser une précision variable:
    //   - * signifie que la précision est donnée comme argument
    //   - f indique un nombre à virgule flottante
    // Le résultat est affiché en cyan pour le mettre en valeur
    printf("  %sRésultat%s            : %s%.*f%s\n", 
           COULEUR_VERT,          // Début de la couleur verte pour "Résultat"
           COULEUR_RESET,         // Fin de la couleur
           COULEUR_CYAN,          // Début de la couleur cyan pour la valeur
           precision,             // Nombre de décimales
           resultat,              // La valeur à afficher
           COULEUR_RESET);        // Fin de la couleur
    
    // Ligne de séparation après le résultat
    afficher_bordure('-');
    
    // Ligne vide pour espacer visuellement les calculs successifs
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION: afficher_erreur_stylee
 * ============================================================================
 * Affiche un message d'erreur de manière visible et claire avec des couleurs
 * rouge vif pour attirer l'attention de l'utilisateur.
 * 
 * Algorithme:
 *   1. Affiche une bordure d'avertissement avec des '*'
 *   2. Affiche le message d'erreur en rouge gras
 *   3. Affiche une bordure de fermeture
 */
void afficher_erreur_stylee(const char* message) {
    // Bordure supérieure avec des étoiles pour signaler une erreur
    printf("\n");
    afficher_bordure('*');
    
    // Affichage du message d'erreur en rouge gras
    // Préfixe "ERREUR:" pour identifier clairement le type de message
    printf("%s  ERREUR: %s%s\n", 
           COULEUR_ROUGE,    // Active la couleur rouge
           message,          // Le message d'erreur
           COULEUR_RESET);   // Désactive la couleur
    
    // Bordure inférieure pour fermer l'encadrement d'erreur
    afficher_bordure('*');
    printf("\n");
}


/*
 * ============================================================================
 * FONCTION: obtenir_precision_utilisateur
 * ============================================================================
 * Demande à l'utilisateur de choisir la précision d'affichage des résultats.
 * Valide l'entrée pour s'assurer qu'elle est dans une plage acceptable (0-10).
 * 
 * Algorithme:
 *   1. Affiche un prompt demandant la précision
 *   2. Lit l'entrée de l'utilisateur
 *   3. Vérifie que la valeur est dans la plage [0, 10]
 *   4. Redemande si l'entrée est invalide
 *   5. Retourne la précision validée
 * 
 * Retour: int - La précision choisie (garantie entre 0 et 10)
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
    
    // Retourne la précision validée
    return precision;
}


/*
 * ============================================================================
 * FONCTION: afficher_aide
 * ============================================================================
 * Affiche l'aide pour l'utilisation du programme en ligne de commande.
 * Explique la syntaxe et donne des exemples concrets d'utilisation.
 * 
 * Cette fonction est appelée quand l'utilisateur lance le programme avec
 * des arguments invalides ou demande explicitement l'aide.
 * 
 * Format de la ligne de commande:
 *   ./programme <operation> <nombre1> [nombre2] [precision]
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
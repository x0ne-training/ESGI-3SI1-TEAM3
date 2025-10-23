/*
 * ============================================================================
 * Fichier: affichage.h
 * Auteur: [Votre nom]
 * Description: Header contenant les prototypes des fonctions d'affichage
 *              stylisé pour la calculatrice. Permet de gérer la précision
 *              et de formater les résultats de manière claire et élégante.
 * ============================================================================
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/*
 * ============================================================================
 * CONSTANTES GLOBALES
 * ============================================================================
 */

// Précision par défaut pour l'affichage des nombres (nombre de décimales)
#define PRECISION_DEFAUT 2

// Largeur maximale pour les bordures et séparateurs visuels
#define LARGEUR_BORDURE 60


/*
 * ============================================================================
 * PROTOTYPES DES FONCTIONS D'AFFICHAGE STYLISÉ
 * ============================================================================
 */

/*
 * Fonction: afficher_resultat_stylee
 * -----------------------------------
 * Affiche le résultat d'un calcul de manière stylisée et formatée.
 * Utilise des bordures, des couleurs (ANSI) et une présentation claire.
 * 
 * Paramètres:
 *   - expression: chaîne de caractères contenant l'expression calculée
 *                 (ex: "3 + 2", "sqrt(16)", "sin(3.14)")
 *   - resultat: la valeur numérique du résultat à afficher
 *   - precision: nombre de chiffres après la virgule (si -1, utilise PRECISION_DEFAUT)
 * 
 * Retour: void
 * 
 * Exemple d'utilisation:
 *   afficher_resultat_stylee("3 + 2", 5.0, 2);
 *   // Affichera: Résultat de l'expression "3 + 2" : 5.00
 */
void afficher_resultat_stylee(const char* expression, double resultat, int precision);


/*
 * Fonction: afficher_bordure
 * ---------------------------
 * Affiche une ligne de séparation décorative (bordure).
 * Utilisée pour délimiter visuellement les sections de l'affichage.
 * 
 * Paramètres:
 *   - caractere: le caractère à utiliser pour la bordure (ex: '=', '-', '*')
 * 
 * Retour: void
 * 
 * Exemple d'utilisation:
 *   afficher_bordure('=');
 *   // Affichera: ============================================================
 */
void afficher_bordure(char caractere);


/*
 * Fonction: afficher_titre
 * -------------------------
 * Affiche un titre centré et encadré pour améliorer la lisibilité.
 * Utilisé pour les en-têtes de section ou messages importants.
 * 
 * Paramètres:
 *   - titre: la chaîne de caractères à afficher comme titre
 * 
 * Retour: void
 * 
 * Exemple d'utilisation:
 *   afficher_titre("CALCULATRICE SCIENTIFIQUE");
 */
void afficher_titre(const char* titre);


/*
 * Fonction: afficher_erreur_stylee
 * ---------------------------------
 * Affiche un message d'erreur de manière visible et claire.
 * Utilise des couleurs (rouge) et un formatage spécial pour alerter l'utilisateur.
 * 
 * Paramètres:
 *   - message: le message d'erreur à afficher
 * 
 * Retour: void
 * 
 * Exemple d'utilisation:
 *   afficher_erreur_stylee("Division par zéro impossible");
 */
void afficher_erreur_stylee(const char* message);


/*
 * Fonction: obtenir_precision_utilisateur
 * ----------------------------------------
 * Demande à l'utilisateur de spécifier la précision d'affichage souhaitée.
 * Valide l'entrée pour s'assurer qu'elle est dans une plage raisonnable.
 * 
 * Paramètres: aucun
 * 
 * Retour: int - le nombre de décimales souhaité (entre 0 et 10)
 * 
 * Exemple d'utilisation:
 *   int prec = obtenir_precision_utilisateur();
 *   // L'utilisateur sera invité à entrer une valeur
 */
int obtenir_precision_utilisateur(void);


/*
 * Fonction: afficher_aide
 * ------------------------
 * Affiche l'aide pour l'utilisation en ligne de commande.
 * Explique comment passer des calculs directement via les arguments du programme.
 * 
 * Paramètres:
 *   - nom_programme: le nom du programme (argv[0])
 * 
 * Retour: void
 * 
 * Exemple d'utilisation:
 *   afficher_aide(argv[0]);
 */
void afficher_aide(const char* nom_programme);


#endif /* AFFICHAGE_H */
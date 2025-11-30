#ifndef HISTORY_H
#define HISTORY_H

// Initialise l'historique
void init_history(void);

// Ajoute une nouvelle entrée
void add_history(const char *entry);

// Affiche l’historique
void print_history(void);

// Libère la mémoire allouée
void free_history(void);

#endif

# ============================================================
# Makefile - Projet C complet avec dépendances automatiques
# ============================================================

# Nom de l'exécutable final
EXEC = calculatrice

# Compilateur 	
CC = gcc

# Options de compilation standard
# -Wall: Active tous les avertissements
# -Wextra: Active des avertissements supplémentaires
# -std=c11: Utilise le standard C11 (plus moderne que C99)
CFLAGS = -Wall -Wextra -std=c11

# Bibliothèques à lier
# -lm: Bibliothèque mathématique (OBLIGATOIRE pour sqrt, pow, sin, cos, log, exp, etc.)
LDFLAGS = -lm

# Liste des fichiers sources (recherche automatique de tous les .c)
SRC = $(wildcard *.c)

# Liste des fichiers objets générés à partir des .c
OBJ = $(SRC:.c=.o)

# Liste des fichiers d'en-tête
HEADERS = $(wildcard *.h)

# ============================================================
# Règle par défaut : compilation complète
# ============================================================
all: $(EXEC)
	@echo "✅ Compilation terminée avec succès !"

# ============================================================
# Règle pour construire l'exécutable
# ============================================================
$(EXEC): $(OBJ)
	@echo "🔧 Édition des liens..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "📦 Exécutable créé : $(EXEC)"

# ============================================================
# Règle de compilation des fichiers .c en .o
# $< : premier fichier dépendance (le .c)
# $@ : nom de la cible (le .o)
# ============================================================
%.o: %.c $(HEADERS)
	@echo "🧩 Compilation de $< ..."
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================
# Règle pour exécuter le programme compilé
# ============================================================
run: $(EXEC)
	@echo "🚀 Exécution du programme :"
	@./$(EXEC)

# ============================================================
# Règle de compilation en mode debug
# -g: Ajoute les symboles de débogage (pour gdb)
# -O0: Désactive les optimisations
# -DDEBUG: Définit la macro DEBUG
# ============================================================
debug: CFLAGS += -g -O0 -DDEBUG
debug: clean all
	@echo "🐞 Compilation en mode débogage terminée."
	@echo "💡 Utilisez 'gdb ./$(EXEC)' pour déboguer"

# ============================================================
# Règle de compilation optimisée (release)
# -O2: Active les optimisations de niveau 2
# -DNDEBUG: Désactive les assertions
# ============================================================
release: CFLAGS += -O2 -DNDEBUG
release: clean all
	@echo "🚀 Version optimisée compilée avec succès !"

# ============================================================
# Règle pour nettoyer les fichiers générés
# ============================================================
clean:
	@echo "🧹 Nettoyage des fichiers objets et exécutables..."
	@rm -f $(OBJ) $(EXEC)
	@echo "✨ Nettoyage terminé !"

# ============================================================
# Règle pour tout reconstruire depuis zéro
# ============================================================
rebuild: clean all
	@echo "🔄 Reconstruction complète terminée !"

# Alternative : re (raccourci)
re: rebuild

# ============================================================
# Règle pour vérifier la syntaxe sans compiler
# ============================================================
check:
	@echo "🔍 Vérification de la syntaxe..."
	$(CC) $(CFLAGS) -fsyntax-only $(SRC)
	@echo "✅ Vérification terminée !"

# ============================================================
# Règle pour afficher les informations de compilation
# ============================================================
info:
	@echo "════════════════════════════════════════"
	@echo "📋 Informations du projet"
	@echo "════════════════════════════════════════"
	@echo "Compilateur    : $(CC)"
	@echo "Flags          : $(CFLAGS)"
	@echo "Bibliothèques  : $(LDFLAGS)"
	@echo "Sources        : $(SRC)"
	@echo "Objets         : $(OBJ)"
	@echo "Headers        : $(HEADERS)"
	@echo "Exécutable     : $(EXEC)"
	@echo "════════════════════════════════════════"

# ============================================================
# Règle pour afficher l'aide
# ============================================================
help:
	@echo "════════════════════════════════════════"
	@echo "📖 Commandes disponibles"
	@echo "════════════════════════════════════════"
	@echo "make          - Compile le projet"
	@echo "make run      - Compile et exécute"
	@echo "make debug    - Compile en mode debug"
	@echo "make release  - Compile en mode optimisé"
	@echo "make clean    - Supprime les fichiers générés"
	@echo "make rebuild  - Nettoie et recompile tout"
	@echo "make check    - Vérifie la syntaxe"
	@echo "make info     - Affiche les infos du projet"
	@echo "make help     - Affiche cette aide"
	@echo "════════════════════════════════════════"

# ============================================================
# Déclare les cibles qui ne sont pas des fichiers
# ============================================================
.PHONY: all run debug release clean rebuild re check info help

# ============================================================
# Fin du Makefile
# ============================================================
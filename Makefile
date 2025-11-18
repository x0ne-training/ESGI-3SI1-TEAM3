# Makefile - Projet Calculatrice en C

# Configuration du projet
EXEC     = calculatrice
CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11
LDFLAGS  = -lm

# Recherche automatique des fichiers
SRC      = $(wildcard *.c)
OBJ      = $(SRC:.c=.o)
HEADERS  = $(wildcard *.h)

# Couleurs pour l'affichage (optionnel)
RESET    = \033[0m
BOLD     = \033[1m
GREEN    = \033[32m
BLUE     = \033[34m
YELLOW   = \033[33m
RED      = \033[31m

# RÈGLES PRINCIPALES

# Règle par défaut : compilation complète
all: $(EXEC)
	@echo "$(GREEN)✅ Compilation terminée avec succès !$(RESET)"

# Construction de l'exécutable
$(EXEC): $(OBJ)
	@echo "$(BLUE)🔧 Édition des liens...$(RESET)"
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "$(GREEN)📦 Exécutable créé : $(EXEC)$(RESET)"

# Compilation des fichiers .c en .o
%.o: %.c $(HEADERS)
	@echo "$(YELLOW)🧩 Compilation de $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# RÈGLES D'EXÉCUTION

# Exécuter le programme
run: $(EXEC)
	@echo "$(BLUE)🚀 Exécution du programme :$(RESET)"
	@./$(EXEC)

# MODES DE COMPILATION

# Mode debug avec symboles
debug: CFLAGS += -g -O0 -DDEBUG
debug: clean all
	@echo "$(GREEN)🐞 Compilation en mode débogage terminée.$(RESET)"
	@echo "$(YELLOW)💡 Utilisez 'gdb ./$(EXEC)' pour déboguer$(RESET)"

# Mode release optimisé
release: CFLAGS += -O2 -DNDEBUG
release: clean all
	@echo "$(GREEN)🚀 Version optimisée compilée avec succès !$(RESET)"

# RÈGLES DE NETTOYAGE

# Nettoyage standard
clean:
	@echo "$(YELLOW)🧹 Nettoyage des fichiers générés...$(RESET)"
	@rm -f $(OBJ) $(EXEC)
	@echo "$(GREEN)✨ Nettoyage terminé !$(RESET)"

# Reconstruction complète
rebuild: clean all
	@echo "$(GREEN)🔄 Reconstruction complète terminée !$(RESET)"

# Alias pour rebuild
re: rebuild

# RÈGLES UTILITAIRES

# Vérification syntaxique
check:
	@echo "$(BLUE)🔍 Vérification de la syntaxe...$(RESET)"
	@$(CC) $(CFLAGS) -fsyntax-only $(SRC)
	@echo "$(GREEN)✅ Vérification terminée !$(RESET)"

# Affichage des informations
info:
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"
	@echo "$(BOLD)📋 Informations du projet$(RESET)"
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"
	@echo "Compilateur    : $(CC)"
	@echo "Flags          : $(CFLAGS)"
	@echo "Bibliothèques  : $(LDFLAGS)"
	@echo "Sources        : $(SRC)"
	@echo "Objets         : $(OBJ)"
	@echo "Headers        : $(HEADERS)"
	@echo "Exécutable     : $(EXEC)"
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"

# Affichage de l'aide
help:
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"
	@echo "$(BOLD)📖 Commandes disponibles$(RESET)"
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)make$(RESET)          - Compile le projet"
	@echo "$(GREEN)make run$(RESET)      - Compile et exécute"
	@echo "$(GREEN)make debug$(RESET)    - Compile en mode debug"
	@echo "$(GREEN)make release$(RESET)  - Compile en mode optimisé"
	@echo "$(GREEN)make clean$(RESET)    - Supprime les fichiers générés"
	@echo "$(GREEN)make rebuild$(RESET)  - Nettoie et recompile tout"
	@echo "$(GREEN)make check$(RESET)    - Vérifie la syntaxe"
	@echo "$(GREEN)make info$(RESET)     - Affiche les infos du projet"
	@echo "$(GREEN)make help$(RESET)     - Affiche cette aide"
	@echo "$(BOLD)════════════════════════════════════════$(RESET)"

# DÉCLARATION DES CIBLES PHONY
.PHONY: all run debug release clean rebuild re check info help


# FIN DU MAKEFILE
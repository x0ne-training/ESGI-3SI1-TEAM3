#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fonction.h"

// Variables globales pour l'interface
GtkWidget *window;
GtkWidget *entry_display;
GtkWidget *grid;
double current_value = 0.0;
double previous_value = 0.0;
char current_operation = '\0';
gboolean new_number = TRUE;

// Fonctions de callback pour les boutons
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *button_text = (const char *)data;
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry_display));
    char new_text[256];
    
    if (strcmp(button_text, "C") == 0) {
        // Clear
        gtk_entry_set_text(GTK_ENTRY(entry_display), "0");
        current_value = 0.0;
        previous_value = 0.0;
        current_operation = '\0';
        new_number = TRUE;
    }
    else if (strcmp(button_text, "=") == 0) {
        // Calcul
        if (current_operation != '\0') {
            double result = 0.0;
            double entry_value = atof(current_text);
            
            switch (current_operation) {
                case '+': result = previous_value + entry_value; break;
                case '-': result = previous_value - entry_value; break;
                case '*': result = previous_value * entry_value; break;
                case '/': 
                    if (entry_value != 0) result = previous_value / entry_value;
                    else {
                        gtk_entry_set_text(GTK_ENTRY(entry_display), "Erreur");
                        new_number = TRUE;
                        return;
                    }
                    break;
            }
            
            snprintf(new_text, sizeof(new_text), "%.10g", result);
            gtk_entry_set_text(GTK_ENTRY(entry_display), new_text);
            current_value = result;
            current_operation = '\0';
            new_number = TRUE;
        }
    }
    else if (strlen(button_text) == 1 && (button_text[0] == '+' || button_text[0] == '-' || 
                                          button_text[0] == '*' || button_text[0] == '/')) {
        // Opérations
        if (current_operation != '\0') {
            // Calcul en cours
            on_button_clicked(widget, "=");
        }
        previous_value = atof(current_text);
        current_operation = button_text[0];
        new_number = TRUE;
    }
    else if (strcmp(button_text, ".") == 0) {
        // Point décimal
        if (new_number) {
            gtk_entry_set_text(GTK_ENTRY(entry_display), "0.");
            new_number = FALSE;
        }
        else if (!strchr(current_text, '.')) {
            snprintf(new_text, sizeof(new_text), "%s.", current_text);
            gtk_entry_set_text(GTK_ENTRY(entry_display), new_text);
        }
    }
    else {
        // Chiffres
        if (new_number) {
            gtk_entry_set_text(GTK_ENTRY(entry_display), button_text);
            new_number = FALSE;
        }
        else {
            snprintf(new_text, sizeof(new_text), "%s%s", current_text, button_text);
            gtk_entry_set_text(GTK_ENTRY(entry_display), new_text);
        }
    }
}

// Fonctions scientifiques
void on_scientific_clicked(GtkWidget *widget, gpointer data) {
    const char *operation = (const char *)data;
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry_display));
    double value = atof(current_text);
    double result = 0.0;
    char result_text[256];
    
    if (strcmp(operation, "sqrt") == 0) {
        if (value >= 0) result = sqrt(value);
        else {
            gtk_entry_set_text(GTK_ENTRY(entry_display), "Erreur");
            return;
        }
    }
    else if (strcmp(operation, "square") == 0) {
        result = value * value;
    }
    else if (strcmp(operation, "sin") == 0) {
        result = sin(value);
    }
    else if (strcmp(operation, "cos") == 0) {
        result = cos(value);
    }
    else if (strcmp(operation, "tan") == 0) {
        result = tan(value);
    }
    else if (strcmp(operation, "log") == 0) {
        if (value > 0) result = log(value);
        else {
            gtk_entry_set_text(GTK_ENTRY(entry_display), "Erreur");
            return;
        }
    }
    else if (strcmp(operation, "exp") == 0) {
        result = exp(value);
    }
    else if (strcmp(operation, "fact") == 0) {
        if (value >= 0 && value <= 20) {
            result = 1.0;
            for (int i = 1; i <= (int)value; i++) {
                result *= i;
            }
        }
        else {
            gtk_entry_set_text(GTK_ENTRY(entry_display), "Erreur");
            return;
        }
    }
    
    snprintf(result_text, sizeof(result_text), "%.10g", result);
    gtk_entry_set_text(GTK_ENTRY(entry_display), result_text);
    new_number = TRUE;
}

// Création de l'interface
void create_calculator_gui() {
    // Fenêtre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculatrice Scientifique");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    
    // Grid principal
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    
    // Affichage
    entry_display = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_display), "0");
    gtk_entry_set_alignment(GTK_ENTRY(entry_display), 1.0); // Alignement à droite
    gtk_widget_set_sensitive(entry_display, FALSE); // Non-éditable directement
    gtk_grid_attach(GTK_GRID(grid), entry_display, 0, 0, 5, 1);
    
    // Boutons numériques
    const char *buttons[] = {
        "7", "8", "9", "/", "C",
        "4", "5", "6", "*", "sqrt",
        "1", "2", "3", "-", "square",
        "0", ".", "=", "+", "sin"
    };
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = i * 5 + j;
            GtkWidget *button = gtk_button_new_with_label(buttons[index]);
            
            if (strcmp(buttons[index], "sqrt") == 0 || strcmp(buttons[index], "square") == 0 || 
                strcmp(buttons[index], "sin") == 0 || strcmp(buttons[index], "cos") == 0 || 
                strcmp(buttons[index], "tan") == 0 || strcmp(buttons[index], "log") == 0 || 
                strcmp(buttons[index], "exp") == 0 || strcmp(buttons[index], "fact") == 0) {
                g_signal_connect(button, "clicked", G_CALLBACK(on_scientific_clicked), (gpointer)buttons[index]);
            }
            else {
                g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)buttons[index]);
            }
            
            gtk_grid_attach(GTK_GRID(grid), button, j, i + 1, 1, 1);
        }
    }
    
    // Deuxième rangée de fonctions scientifiques
    const char *scientific_buttons[] = {"cos", "tan", "log", "exp", "fact"};
    for (int i = 0; i < 5; i++) {
        GtkWidget *button = gtk_button_new_with_label(scientific_buttons[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_scientific_clicked), (gpointer)scientific_buttons[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i, 6, 1, 1);
    }
    
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    // Signaux
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    create_calculator_gui();
    
    gtk_main();
    
    return 0;
}

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Variables globales
GtkWidget *entry;
double current_number = 0.0;
double previous_number = 0.0;
char operation = '\0';
gboolean new_input = TRUE;

// Fonction pour mettre à jour l'affichage
void update_display(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(entry), text);
}

// Fonction appelée quand on clique sur un bouton
void on_button_clicked(GtkWidget *widget, gpointer data) {
    const char *label = (const char *)data;
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strcmp(label, "C") == 0) {
        update_display("0");
        current_number = 0.0;
        previous_number = 0.0;
        operation = '\0';
        new_input = TRUE;
    }
    else if (strcmp(label, "=") == 0) {
        if (operation != '\0') {
            double result = 0.0;
            double value = atof(current_text);
            
            switch (operation) {
                case '+': result = previous_number + value; break;
                case '-': result = previous_number - value; break;
                case '*': result = previous_number * value; break;
                case '/': 
                    if (value != 0) result = previous_number / value;
                    else {
                        update_display("Erreur");
                        return;
                    }
                    break;
            }
            
            char result_text[50];
            snprintf(result_text, sizeof(result_text), "%.10g", result);
            update_display(result_text);
            current_number = result;
            operation = '\0';
            new_input = TRUE;
        }
    }
    else if (strlen(label) == 1 && (label[0] == '+' || label[0] == '-' || 
                                   label[0] == '*' || label[0] == '/')) {
        if (operation != '\0') {
            // Calculer l'opération précédente
            on_button_clicked(widget, "=");
        }
        previous_number = atof(current_text);
        operation = label[0];
        new_input = TRUE;
    }
    else if (strcmp(label, ".") == 0) {
        if (new_input) {
            update_display("0.");
            new_input = FALSE;
        }
        else if (!strchr(current_text, '.')) {
            char new_text[100];
            snprintf(new_text, sizeof(new_text), "%s.", current_text);
            update_display(new_text);
        }
    }
    else {
        // Chiffres
        if (new_input) {
            update_display(label);
            new_input = FALSE;
        }
        else {
            char new_text[100];
            snprintf(new_text, sizeof(new_text), "%s%s", current_text, label);
            update_display(new_text);
        }
    }
}

// Fonctions scientifiques
void on_scientific_clicked(GtkWidget *widget, gpointer data) {
    const char *op = (const char *)data;
    const char *current_text = gtk_entry_get_text(GTK_ENTRY(entry));
    double value = atof(current_text);
    double result = 0.0;
    char result_text[50];
    
    if (strcmp(op, "sqrt") == 0) {
        if (value >= 0) result = sqrt(value);
        else { update_display("Erreur"); return; }
    }
    else if (strcmp(op, "square") == 0) {
        result = value * value;
    }
    else if (strcmp(op, "sin") == 0) {
        result = sin(value);
    }
    else if (strcmp(op, "cos") == 0) {
        result = cos(value);
    }
    else if (strcmp(op, "tan") == 0) {
        result = tan(value);
    }
    else if (strcmp(op, "log") == 0) {
        if (value > 0) result = log(value);
        else { update_display("Erreur"); return; }
    }
    else if (strcmp(op, "exp") == 0) {
        result = exp(value);
    }
    else if (strcmp(op, "fact") == 0) {
        if (value >= 0 && value <= 20) {
            result = 1.0;
            for (int i = 1; i <= (int)value; i++) {
                result *= i;
            }
        }
        else { update_display("Erreur"); return; }
    }
    
    snprintf(result_text, sizeof(result_text), "%.10g", result);
    update_display(result_text);
    new_input = TRUE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    // Créer la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculatrice");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    
    // Créer une grille pour organiser les widgets
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 8);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
    
    // Créer une boîte verticale pour centrer le contenu
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(vbox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(vbox, GTK_ALIGN_CENTER);
    
    // Créer l'affichage
    entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "0");
    gtk_entry_set_alignment(GTK_ENTRY(entry), 1.0);
    gtk_widget_set_sensitive(entry, FALSE);
    
    // Appliquer un style CSS pour l'affichage
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, 
        "entry {"
        "   background: #2b2b2b;"
        "   color: white;"
        "   border: 2px solid #555;"
        "   border-radius: 5px;"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "}"
        "button {"
        "   background: #404040;"
        "   color: white;"
        "   border: 1px solid #666;"
        "   border-radius: 3px;"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   padding: 8px;"
        "}"
        "button:hover {"
        "   background: #505050;"
        "}"
        "button:active {"
        "   background: #606060;"
        "}", -1, NULL);
    
    GtkStyleContext *style_context = gtk_widget_get_style_context(entry);
    gtk_style_context_add_provider(style_context, GTK_STYLE_PROVIDER(css_provider), 
                                 GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    // Appliquer le style à tous les boutons
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                             GTK_STYLE_PROVIDER(css_provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 4, 1);
    
    // Boutons de base
    const char *buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "0", ".", "=", "+"
    };
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int index = i * 4 + j;
            GtkWidget *button = gtk_button_new_with_label(buttons[index]);
            g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), (gpointer)buttons[index]);
            gtk_grid_attach(GTK_GRID(grid), button, j, i + 1, 1, 1);
        }
    }
    
    // Bouton Clear
    GtkWidget *clear_button = gtk_button_new_with_label("C");
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_button_clicked), "C");
    gtk_grid_attach(GTK_GRID(grid), clear_button, 0, 5, 4, 1);
    
    // Fonctions scientifiques
    const char *scientific[] = {"sqrt", "square", "sin", "cos", "tan", "log", "exp", "fact"};
    for (int i = 0; i < 8; i++) {
        GtkWidget *button = gtk_button_new_with_label(scientific[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_scientific_clicked), (gpointer)scientific[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, 6 + i / 4, 1, 1);
    }
    
    // Ajouter la grille à la boîte de centrage
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    
    // Ajouter la boîte à la fenêtre
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Connecter le signal de fermeture
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}

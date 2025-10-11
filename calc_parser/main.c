#include <stdio.h>
#include "parser.h"

/*int main() {
    printf("Hello, parser!\n");
    return 0;
}*/

int main() {
    char input[256];
    Token tokens[64];
    printf("Entrez une expression : ");
    fgets(input, sizeof(input), stdin);
    int count = tokenize(input, tokens, 64);
    for (int i = 0; i < count; i++) {
        if (tokens[i].type == TOKEN_NUMBER)
            printf("Nombre: %f\n", tokens[i].value);
        else if (tokens[i].type == TOKEN_OPERATOR)
            printf("Opérateur: %c\n", tokens[i].op);
        else if (tokens[i].type == TOKEN_PAREN_LEFT)
            printf("Parenthèse gauche\n");
        else if (tokens[i].type == TOKEN_PAREN_RIGHT)
            printf("Parenthèse droite\n");
    }
    return 0;
}

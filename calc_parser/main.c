#include <stdio.h>
#include "parser.h"

/*int main() {
    printf("Hello, parser!\n");
    return 0;
}*/

/*int main() {
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
    return 0;*/

void print_tree(Node *node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) printf("  ");
    if (node->type == NODE_NUMBER)
        printf("Nombre: %f\n", node->value);
    else {
        printf("Opérateur: %c\n", node->op);
        print_tree(node->left, depth + 1);
        print_tree(node->right, depth + 1);
    }
}

int main() {
    char input[256];
    Token tokens[64];
    printf("Entrez une expression : ");
    fgets(input, sizeof(input), stdin);
    int count = tokenize(input, tokens, 64);
    int pos = 0;
    Node *tree = parse_expression(tokens, &pos, count);
    double result = evaluate(tree);
    printf("Résultat : %f\n", result);
    free_tree(tree);
    return 0;
}



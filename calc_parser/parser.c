#include "parser.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ---------------- TOKENIZER ----------------

int tokenize(const char *expr, Token *tokens, int max_tokens) {
    int i = 0, j = 0;
    while (expr[i] != '\0' && j < max_tokens) {
        if (isdigit(expr[i]) || expr[i] == '.') {
            tokens[j].type = TOKEN_NUMBER;
            tokens[j].value = atof(&expr[i]);
            while (isdigit(expr[i]) || expr[i] == '.') i++;
            j++;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            tokens[j].type = TOKEN_OPERATOR;
            tokens[j].op = expr[i];
            i++; j++;
        } else if (expr[i] == '(') {
            tokens[j].type = TOKEN_PAREN_LEFT;
            i++; j++;
        } else if (expr[i] == ')') {
            tokens[j].type = TOKEN_PAREN_RIGHT;
            i++; j++;
        } else {
            i++; // ignore spaces
        }
    }
    return j;
}

// ---------------- PARSER ----------------

static Node* parse_primary(Token *tokens, int *pos, int count);
static Node* parse_factor(Token *tokens, int *pos, int count);
static Node* parse_term(Token *tokens, int *pos, int count);

Node* parse_expression(Token *tokens, int *pos, int count) {
    return parse_term(tokens, pos, count);
}

static Node* parse_term(Token *tokens, int *pos, int count) {
    Node *node = parse_factor(tokens, pos, count);
    while (*pos < count && (tokens[*pos].type == TOKEN_OPERATOR) &&
           (tokens[*pos].op == '+' || tokens[*pos].op == '-')) {
        char op = tokens[*pos].op;
        (*pos)++;
        Node *right = parse_factor(tokens, pos, count);
        Node *new_node = malloc(sizeof(Node));
        new_node->type = NODE_BINARY_OP;
        new_node->op = op;
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }
    return node;
}

static Node* parse_factor(Token *tokens, int *pos, int count) {
    Node *node = parse_primary(tokens, pos, count);
    while (*pos < count && (tokens[*pos].type == TOKEN_OPERATOR) &&
           (tokens[*pos].op == '*' || tokens[*pos].op == '/')) {
        char op = tokens[*pos].op;
        (*pos)++;
        Node *right = parse_primary(tokens, pos, count);
        Node *new_node = malloc(sizeof(Node));
        new_node->type = NODE_BINARY_OP;
        new_node->op = op;
        new_node->left = node;
        new_node->right = right;
        node = new_node;
    }
    return node;
}

static Node* parse_primary(Token *tokens, int *pos, int count) {
    if (tokens[*pos].type == TOKEN_NUMBER) {
        Node *node = malloc(sizeof(Node));
        node->type = NODE_NUMBER;
        node->value = tokens[*pos].value;
        (*pos)++;
        return node;
    } else if (tokens[*pos].type == TOKEN_PAREN_LEFT) {
        (*pos)++;
        Node *node = parse_expression(tokens, pos, count);
        if (tokens[*pos].type == TOKEN_PAREN_RIGHT) (*pos)++;
        return node;
    }
    return NULL;
}

void free_tree(Node *node) {
    if (!node) return;
    if (node->type == NODE_BINARY_OP) {
        free_tree(node->left);
        free_tree(node->right);
    }
    free(node);
}

double evaluate(Node *node) {
    if (node->type == NODE_NUMBER) return node->value;
    double left = evaluate(node->left);
    double right = evaluate(node->right);
    switch (node->op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}

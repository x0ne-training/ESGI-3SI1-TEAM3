#ifndef PARSER_H
#define PARSER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PAREN_LEFT,
    TOKEN_PAREN_RIGHT
} TokenType;

typedef struct {
    TokenType type;
    double value;
    char op;
} Token;

int tokenize(const char *expr, Token *tokens, int max_tokens);

typedef enum {
    NODE_NUMBER,
    NODE_BINARY_OP
} NodeType;

typedef struct Node {
    NodeType type;
    double value; // 
    char op;      // 
    struct Node *left;
    struct Node *right;
} Node;

Node* parse_expression(Token *tokens, int *pos, int count);
void free_tree(Node *node);
double evaluate(Node *node);

#endif

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

#endif

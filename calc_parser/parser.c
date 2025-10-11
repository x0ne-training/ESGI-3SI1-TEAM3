#include "parser.h"
#include <ctype.h>
#include <stdlib.h>

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
            i++; // ignore espace
        }
    }
    return j;
}

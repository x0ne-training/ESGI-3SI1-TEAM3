#include <stdio.h>

/*int main() {
    printf("Hello, parser!\n");
    return 0;
}*/

int main() {
    char input[256];
    printf("Entrez une expression : ");
    fgets(input, sizeof(input), stdin);
    printf("Vous avez entré : %s\n", input);
    return 0;
}

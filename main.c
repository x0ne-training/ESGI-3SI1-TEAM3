#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    char choix;
    printf("Séléctionner l'option que vous voulez utilisé :\n1 : Addition\n2 : Soustraction\n3 : Multiplication\n4 : Division\n");
    scanf("%c",&choix);

    switch(choix){
        case '1': printf("ToDo case1");
        case '2': printf("ToDo case2");
        case '3': printf("ToDo case3");
        case '4': printf("ToDo case4");
    }
}
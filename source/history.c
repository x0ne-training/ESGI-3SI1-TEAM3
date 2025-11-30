#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/history.h"

typedef struct HistoryNode {
    char *entry;
    struct HistoryNode *next;
} HistoryNode;

static HistoryNode *head = NULL;

void init_history(void) {
    head = NULL;
}

void add_history(const char *entry) {
    if (!entry) return;

    HistoryNode *new_node = malloc(sizeof(HistoryNode));
    if (!new_node) return;

    new_node->entry = malloc(strlen(entry) + 1);
    if (!new_node->entry) {
        free(new_node);
        return;
    }

    strcpy(new_node->entry, entry);
    new_node->next = NULL;

    if (!head) {
        head = new_node;
    } else {
        HistoryNode *tmp = head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

void print_history(void) {
    if (!head) {
        printf("Historique vide.\n");
        return;
    }

    HistoryNode *tmp = head;
    int index = 1;

    while (tmp) {
        printf("%d: %s\n", index++, tmp->entry);
        tmp = tmp->next;
    }
}

void free_history(void) {
    HistoryNode *tmp = head;
    while (tmp) {
        HistoryNode *next = tmp->next;
        free(tmp->entry);
        free(tmp);
        tmp = next;
    }
    head = NULL;
}

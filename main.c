#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[1000];
    struct Node *next;
    struct Node *prev;
} Node;


void append(Node **head, char *line) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->data, line);
    new_node->next = NULL;
    new_node->prev = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp;
    }
}


void printReverse(Node *head) {
    if (head == NULL) return;


    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }


    while (temp != NULL) {
        printf("%s", temp->data);
        temp = temp->prev;
    }
}


void freeList(Node *node) {
    while (node != NULL) {
        Node *temp = node;
        node = node->next;
        free(temp);
    }
}

int main() {
    FILE *file;
    char s[1000];
    Node *head = NULL;


    file = fopen("darshan.txt", "a");
    if (file == NULL) {
        puts("Cannot open file");
        return 1;
    }


    printf("Enter lines (enter an empty line to stop):\n");
    while (strlen(gets(s)) > 0) {
        fputs(s, file);
        fputs("\n", file);
    }
    fclose(file);


    file = fopen("darshan.txt", "r");
    if (file != NULL) {
        while (fgets(s, sizeof(s), file) != NULL) {
            append(&head, s);
        }
        fclose(file);
    } else {
        puts("Cannot open file");
        return 1;
    }


    printf("\nReversed content of the file:\n");
    printReverse(head);


    freeList(head);

    return 0;
}

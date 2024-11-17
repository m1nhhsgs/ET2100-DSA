#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

void initializeList(List *list) {
    list->head = list->tail = NULL;
}

Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void deleteHeadNode(List *list) {
    if (list->head != NULL) {
        Node *node = list->head;
        list->head = list->head->next;
        free(node);
        if (list->head == NULL) {
            list->tail = NULL;
        }
    }
}

void printList(const List *list) {
    Node *node = list->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void deleteTailNode(List *list) {
    if (list->head != NULL) {
        if (list->head == list->tail) {
            free(list->head);
            list->head = list->tail = NULL;
        } else {
            Node *node = list->head;
            while (node->next != list->tail) {
                node = node->next;
            }
            free(list->tail);
            list->tail = node;
            list->tail->next = NULL;
        }
    }
}

void deleteNodeAfter(List *list, Node *node) {
    if (node != NULL && node->next != NULL) {
        Node *temp = node->next;
        node->next = temp->next;
        if (temp == list->tail) {
            list->tail = node;
        }
        free(temp);
    }
}

void inputNodeFromKeyboard(List *list) {
    int data;
    printf("Enter node value: ");
    scanf("%d", &data);
    Node *node = createNode(data);
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
}

int main() {
    List list;
    initializeList(&list);
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        inputNodeFromKeyboard(&list);
    }
    printf("List after input: ");
    printList(&list);
    deleteHeadNode(&list);
    printf("List after deleting head node: ");
    printList(&list);
    deleteTailNode(&list);
    printf("List after deleting tail node: ");
    printList(&list);
    Node *node = list.head->next; 
    deleteNodeAfter(&list, node);
    printf("List after deleting node after the second node: ");
    printList(&list);

    return 0;
}
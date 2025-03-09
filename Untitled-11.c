#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct Node *getUnion(struct Node *head1, struct Node *head2) {
    struct Node *result = NULL;
    struct Node *t1 = head1, *t2 = head2;

    while (t1 != NULL) {
        push(&result, t1->data);
        t1 = t1->next;
    }

    while (t2 != NULL) {
        if (!isPresent(result, t2->data))
            push(&result, t2->data);
        t2 = t2->next;
    }

    return result;
}

struct Node *getIntersection(struct Node *head1, struct Node *head2) {
    struct Node *result = NULL;
    struct Node *t1 = head1;

    while (t1 != NULL) {
        if (isPresent(head2, t1->data))
            push(&result, t1->data);
        t1 = t1->next;
    }

    return result;
}

int isPresent(struct Node *head, int data) {
    struct Node *t = head;
    while (t != NULL) {
        if (t->data == data)
            return 1;
        t = t->next;
    }
    return 0;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    struct Node* intersecn = NULL;
    struct Node* unin = NULL;

    /* Start with the empty list */
    int n1, n2, i, data;

    printf("Enter the number of nodes in list 1: ");
    scanf("%d", &n1);
    printf("Enter the data for nodes of list 1\n");
    for(i = 0; i < n1; i++) {
        scanf("%d", &data);
        push(&head1, data);
    }

    printf("Enter the number of nodes in list 2: ");
    scanf("%d", &n2);
    printf("Enter the data for nodes of list 2\n");
    for(i = 0; i < n2; i++) {
        scanf("%d", &data);
        push(&head2, data);
    }

    unin = getUnion(head1, head2);
    intersecn = getIntersection(head1, head2);

    printf("\n First list is \n");
    printList(head1);

    printf("\n Second list is \n");
    printList(head2);

    printf("\n Union lists \n");
    printList(unin);

    printf("\n Intersection lists \n");
    printList(intersecn);

    return 0;
}

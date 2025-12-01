#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

// -------------------- INSERT AT END --------------------
void insertEnd(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

// -------------------- INSERT AT BEGINNING --------------------
void insertBeginning(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// -------------------- DELETE A NODE --------------------
void deleteNode(int value) {
    struct Node *temp = head, *prev = NULL;

    if (temp != NULL && temp->data == value) {
        head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found.\n", value);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

// -------------------- SEARCH ELEMENT --------------------
void search(int value) {
    struct Node* temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == value) {
            printf("Value %d found at position %d\n", value, pos);
            return;
        }
        pos++;
        temp = temp->next;
    }
    printf("Value %d not found.\n", value);
}

// -------------------- DISPLAY FORWARD --------------------
void displayForward() {
    struct Node* temp = head;
    printf("List (forward): ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// -------------------- DISPLAY REVERSE USING RECURSION --------------------
void displayReverseHelper(struct Node* node) {
    if (node == NULL) return;
    displayReverseHelper(node->next);
    printf("%d -> ", node->data);
}

void displayReverse() {
    printf("List (reverse): ");
    displayReverseHelper(head);
    printf("NULL\n");
}

// -------------------- MAIN MENU --------------------
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at End\n");
        printf("2. Insert at Beginning\n");
        printf("3. Delete a Value\n");
        printf("4. Display Forward\n");
        printf("5. Display Reverse\n");
        printf("6. Search\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertEnd(value);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertBeginning(value);
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;

            case 4:
                displayForward();
                break;

            case 5:
                displayReverse();
                break;

            case 6:
                printf("Enter value to search: ");
                scanf("%d", &value);
                search(value);
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

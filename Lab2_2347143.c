#include <stdio.h>
#include <stdlib.h>

// Node structure for a transaction (just including amount for this program)
typedef struct Transaction {
    float amount;
    struct Transaction *next;
    struct Transaction *prev;
} Transaction;

// Declaring Function prototypes (can include this in header files as in Lab 1)
Transaction* createTransaction(float amount);
Transaction* insertTransaction(Transaction *head, float amount, int position);
Transaction* deleteTransaction(Transaction *head, int position);
void displayTransactions(Transaction *head);

int main() {
    int choice, operation, position;
    Transaction *head = NULL;

    do {
        // Displaying the main menu
        printf("\nFinance Management System\n");
        printf("1. Singly Linked List\n");
        printf("2. Doubly Linked List\n");
        printf("3. Circular Linked List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
            case 3:
                do {
                    // Displaying the operations menu
                    printf("\nOperations Menu\n");
                    printf("1. Insert Transaction\n");
                    printf("2. Delete Transaction\n");
                    printf("3. Display Transactions\n");
                    printf("4. Back to Linked List Selection\n");
                    printf("Enter your choice: ");
                    scanf("%d", &operation);

                    switch (operation) {
                        case 1: {
                            float amount;
                            printf("Enter the amount for the new transaction: ");
                            scanf("%f", &amount);
                            printf("Enter position (1 for beginning, 2 for end, 3 for somewhere in between): ");
                            scanf("%d", &position);
                            head = insertTransaction(head, amount, position);
                            break;
                        }
                        case 2: {
                            printf("Enter the position to delete ((1 for beginning, 2 for end, 3 for somewhere in between), 1-based index): ");
                            scanf("%d", &position);
                            head = deleteTransaction(head, position);
                            break;
                        }
                        case 3:
                            if (choice == 3) {
                                displayCircularTransactions(head);
                            } else {
                                displayTransactions(head);
                            }
                            break;
                        case 4:
                            // Returning to the linked list selection menu
                            break;
                        default:
                            printf("Invalid choice! Please enter a valid option.\n");
                    }
                } while (operation != 4);
                break;
            case 4:
                printf("Exiting the Finance Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}

// Function to create a new transaction node
Transaction* createTransaction(float amount) {
    Transaction *newTransaction = (Transaction*)malloc(sizeof(Transaction));
    if (newTransaction == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newTransaction->amount = amount;
    newTransaction->next = NULL;
    newTransaction->prev = NULL;
    return newTransaction;
}

// Function to insert a transaction at the specified position
Transaction* insertTransaction(Transaction *head, float amount, int position) {
    Transaction *newTransaction = createTransaction(amount);
    int i;

    if (position == 1) {
        newTransaction->next = head;
        head = newTransaction;
    } else if (position == 2) {
        if (head == NULL) {
            head = newTransaction;
        } else {
            Transaction *temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newTransaction;
            newTransaction->prev = temp;
        }
    } else if (position == 3) {
        int index;
        printf("Enter the position to insert (1-based index): ");
        scanf("%d", &index);

        if (index <= 0) {
            printf("Invalid position! Please enter a valid position.\n");
            free(newTransaction);
            return head;
        }

        if (index == 1) {
            newTransaction->next = head;
            head->prev = newTransaction;
            head = newTransaction;
        } else {
            Transaction *temp = head;
            for (i = 1; i < index - 1 && temp != NULL; ++i) {
                temp = temp->next;
            }

            if (temp == NULL) {
                printf("Invalid position! Please enter a valid position.\n");
                free(newTransaction);
                return head;
            }

            newTransaction->next = temp->next;
            if (temp->next != NULL) {
                temp->next->prev = newTransaction;
            }
            temp->next = newTransaction;
            newTransaction->prev = temp;
        }
    } else {
        printf("Invalid position! Please enter a valid position.\n");
        free(newTransaction);
    }

    return head;
}

// Function to delete a transaction at the specified position
Transaction* deleteTransaction(Transaction *head, int position) {
	int i;
    if (head == NULL) {
        printf("Transaction list is empty. Cannot delete.\n");
        return head;
    }

    if (position == 1) {
        Transaction *temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        free(temp);
    } else {
        int index;
        printf("Enter the position to delete (1-based index): ");
        scanf("%d", &index);

        if (index <= 0) {
            printf("Invalid position! Please enter a valid position.\n");
            return head;
        }

        Transaction *temp = head;

        for (i = 1; i < index && temp != NULL; ++i) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Invalid position! Please enter a valid position.\n");
            return head;
        }

        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next;
        }

        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }

        free(temp);
    }

    return head;
}

// Function to display all transactions
void displayTransactions(Transaction *head) {
    printf("\nTransactions:\n");
    while (head != NULL) {
        printf("%.2f -> ", head->amount);
        head = head->next;
    }
    printf("NULL\n");
}

// Function to display all transactions in a circular linked list
void displayCircularTransactions(Transaction *head) {
    if (head == NULL) {
        printf("No transactions to display.\n");
        return;
    }

    Transaction *current = head;

    do {
        printf("%.2f -> ", current->amount);
        current = current->next;
    } while (current != NULL && current != head);

    printf(" (Back to the beginning)\n");

}

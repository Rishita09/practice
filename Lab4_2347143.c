#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int transactionId;
    float amount;
    char type[20];
} FinanceTransaction;

typedef struct Node {
    FinanceTransaction data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

void initializeQueue(Queue *q);
void enqueue(Queue *q, FinanceTransaction transaction);
FinanceTransaction dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void displayQueue(Queue *q);
void clearInputBuffer();

int main() {
    Queue normalQueue, priorityQueue, circularQueue;
    initializeQueue(&normalQueue);
    initializeQueue(&priorityQueue);
    initializeQueue(&circularQueue);

    int choice;
    do {
        printf("\nFinance Management Queue Operations:\n");
        printf("1. Enqueue (Normal Queue)\n");
        printf("2. Enqueue (Priority Queue)\n");
        printf("3. Enqueue (Circular Queue)\n");
        printf("4. Dequeue (Normal Queue)\n");
        printf("5. Dequeue (Priority Queue)\n");
        printf("6. Dequeue (Circular Queue)\n");
        printf("7. Display (Normal Queue)\n");
        printf("8. Display (Priority Queue)\n");
        printf("9. Display (Circular Queue)\n");
        printf("0. Exit\n");
        printf("\nEnter your choice: ");

        while (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a valid option: ");
        }

        switch (choice) {
            case 1:
                {
                    FinanceTransaction transaction;
                    printf("Enter transaction ID: ");
                    while (scanf("%d", &transaction.transactionId) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction ID: ");
                    }

                    printf("Enter transaction amount: ");
                    while (scanf("%f", &transaction.amount) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction amount: ");
                    }

                    printf("Enter transaction type (Deposit/Withdrawal): ");
                    clearInputBuffer();
                    fgets(transaction.type, sizeof(transaction.type), stdin);
                    transaction.type[strcspn(transaction.type, "\n")] = '\0';

                    enqueue(&normalQueue, transaction);
                    printf("Transaction enqueued successfully to Normal Queue.\n");
                }
                break;

            case 2:
                {
                    FinanceTransaction transaction;
                    printf("Enter transaction ID: ");
                    while (scanf("%d", &transaction.transactionId) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction ID: ");
                    }

                    printf("Enter transaction amount: ");
                    while (scanf("%f", &transaction.amount) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction amount: ");
                    }

                    printf("Enter transaction type (Deposit/Withdrawal): ");
                    clearInputBuffer();
                    fgets(transaction.type, sizeof(transaction.type), stdin);
                    transaction.type[strcspn(transaction.type, "\n")] = '\0';

                    enqueue(&priorityQueue, transaction);
                    printf("Transaction enqueued successfully to Priority Queue.\n");
                }
                break;

            case 3:
                {
                    FinanceTransaction transaction;
                    printf("Enter transaction ID: ");
                    while (scanf("%d", &transaction.transactionId) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction ID: ");
                    }

                    printf("Enter transaction amount: ");
                    while (scanf("%f", &transaction.amount) != 1) {
                        clearInputBuffer();
                        printf("Invalid input. Please enter a valid transaction amount: ");
                    }

                    printf("Enter transaction type (Deposit/Withdrawal): ");
                    clearInputBuffer();
                    fgets(transaction.type, sizeof(transaction.type), stdin);
                    transaction.type[strcspn(transaction.type, "\n")] = '\0';

                    enqueue(&circularQueue, transaction);
                    printf("Transaction enqueued successfully to Circular Queue.\n");
                }
                break;

            case 4:
                if (!isQueueEmpty(&normalQueue)) {
                    FinanceTransaction dequeuedTransaction = dequeue(&normalQueue);
                    printf("Dequeued transaction from Normal Queue - Transaction ID: %d, Amount: %.2f, Type: %s\n",
                           dequeuedTransaction.transactionId, dequeuedTransaction.amount, dequeuedTransaction.type);
                } else {
                    printf("Normal Queue is empty. Cannot dequeue.\n");
                }
                break;

            case 5:
                if (!isQueueEmpty(&priorityQueue)) {
                    FinanceTransaction dequeuedTransaction = dequeue(&priorityQueue);
                    printf("Dequeued transaction from Priority Queue - Transaction ID: %d, Amount: %.2f, Type: %s\n",
                           dequeuedTransaction.transactionId, dequeuedTransaction.amount, dequeuedTransaction.type);
                } else {
                    printf("Priority Queue is empty. Cannot dequeue.\n");
                }
                break;

            case 6:
                if (!isQueueEmpty(&circularQueue)) {
                    FinanceTransaction dequeuedTransaction = dequeue(&circularQueue);
                    printf("Dequeued transaction from Circular Queue - Transaction ID: %d, Amount: %.2f, Type: %s\n",
                           dequeuedTransaction.transactionId, dequeuedTransaction.amount, dequeuedTransaction.type);
                } else {
                    printf("Circular Queue is empty. Cannot dequeue.\n");
                }
                break;

            case 7:
                printf("\nNormal Queue:\n");
                displayQueue(&normalQueue);
                break;

            case 8:
                printf("\nPriority Queue:\n");
                displayQueue(&priorityQueue);
                break;

            case 9:
                printf("\nCircular Queue:\n");
                displayQueue(&circularQueue);
                break;

            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}

void initializeQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, FinanceTransaction transaction) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error. Unable to enqueue.\n");
        return;
    }

    newNode->data = transaction;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

FinanceTransaction dequeue(Queue *q) {
    FinanceTransaction emptyTransaction = {-1, 0.0};
    if (q->front == NULL) {
        return emptyTransaction;
    }

    Node *temp = q->front;
    FinanceTransaction dequeuedTransaction = temp->data;

    if (q->front == q->rear) {
        q->front = q->rear = NULL;
    } else {
        q->front = q->front->next;
    }

    free(temp);
    return dequeuedTransaction;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    Node *current = q->front;
    while (current != NULL) {
        printf("Transaction ID: %d, Amount: %.2f, Type: %s\n",
               current->data.transactionId, current->data.amount, current->data.type);
        current = current->next;
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


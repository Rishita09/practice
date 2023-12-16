#include <stdio.h>
#include <string.h>
#include "finances.h"

int i, r, del_id;

int getPositiveIntInput() {
    int input;
    do {
        printf("Enter a positive integer: ");
        if (scanf("%d", &input) != 1) {
            // Invalid input, clear the input buffer
            while (getchar() != '\n');
            printf("Please enter a valid positive integer.\n");
        } else if (input <= 0) {
            printf("Please enter a positive integer.\n");
        }
    } while (input <= 0);
    return input;
}

void read(struct account *acc) {
    printf("Enter the account holder name:\n");
    fflush(stdin);  // Clear the input buffer
    fgets(acc->holderName, sizeof(acc->holderName), stdin);
    acc->holderName[strcspn(acc->holderName, "\n")] = 0;  // Remove the newline character
    printf("Account Id:\n");
    scanf("%d", &acc->accId);
    printf("Enter Principal Amount and Interest Rate (Eg: 10000 7.5):\n");
    scanf("%f%f", &acc->prAmount, &acc->intRate);
    printf("Transaction Type (Deposit/Withdrawal/Investment) and Amount (Eg: Withdrawal 10000):\n");
    scanf("%s%f", acc->transType, &acc->transAmount);
    // Calculate the interest amount and total balance
    acc->intAmount = (acc->prAmount * acc->intRate) / 100;
    if (strcmp(acc->transType, "Withdrawal") == 0) {
        acc->totalBalance = (acc->prAmount + acc->intAmount) - acc->transAmount;
    } else {
        acc->totalBalance = (acc->prAmount + acc->intAmount) + acc->transAmount;
    }
}

void display(struct account acc) {
    printf("+------------------+--------+-------------+---------------+----------------+-----------+-------------+-------------------+\n");
    printf("| Account Holder   | Acc ID | Trans. Type | Principal Amt | Trans. Amt     | Int. Rate | Int. Amount  | Total Balance |\n");
    printf("+------------------+--------+-------------+---------------+----------------+-----------+-------------+---------------+\n");

    printf("| %-16s | %-6d | %-11s | %-13.2f | %-14.2f | %-9.2f | %-12.2f | %-14.2f |\n",
           acc.holderName, acc.accId, acc.transType, acc.prAmount, acc.transAmount, acc.intRate, acc.intAmount,
           acc.totalBalance);

    printf("+------------------+--------+-------------+---------------+----------------+-----------+-------------+-------------------+\n");
}

void delRecord(int id, struct account *finances, int *count) {
    int indextoDel = -1;
    for (i = 0; i < *count; i++) {
        if (finances[i].accId == id) {
            indextoDel = i;
            break;
        }
    }

    if (indextoDel != -1) {
        // Shifting elements to overwrite the deleted record
        for (i = indextoDel; i < *count - 1; i++) {
            finances[i] = finances[i + 1];
        }

        // Updating the count to reflect the removal of one record
        (*count)--;
        printf("Record with Account ID %d has been deleted.\n", id);
    } else {
        printf("Account with ID %d not found.\n", id);
    }
}

void matOperations(struct account *finances, int count) {
    float prAmountSum = 0;
    float transAmountSum = 0;
    float intRateSum = 0;
    float totalBalanceSum = 0;
    float maxTotalBalance = finances[0].totalBalance;
    float minTotalBalance = finances[0].totalBalance;

    float depositTotal = 0;
    float withdrawalTotal = 0;
    float investmentTotal = 0;
    int depositCount = 0;
    int withdrawalCount = 0;
    int investmentCount = 0;

    for (i = 0; i < count; i++) {
        prAmountSum += finances[i].prAmount;
        transAmountSum += finances[i].transAmount;
        intRateSum += finances[i].intRate;
        totalBalanceSum += finances[i].totalBalance;

        if (finances[i].totalBalance > maxTotalBalance) {
            maxTotalBalance = finances[i].totalBalance;
        }

        if (finances[i].totalBalance < minTotalBalance) {
            minTotalBalance = finances[i].totalBalance;
        }

        if (strcmp(finances[i].transType, "Deposit") == 0) {
            depositTotal += finances[i].transAmount;
            depositCount++;
        } else if (strcmp(finances[i].transType, "Withdrawal") == 0) {
            withdrawalTotal += finances[i].transAmount;
            withdrawalCount++;
        } else if (strcmp(finances[i].transType, "Investment") == 0) {
            investmentTotal += finances[i].transAmount;
            investmentCount++;
        }
    }

    float prAmountAverage = prAmountSum / count;
    float transAmountAverage = transAmountSum / count;
    float intRateAverage = intRateSum / count;
    float totalBalanceAverage = totalBalanceSum / count;

    float avgDepositAmount = depositCount > 0 ? depositTotal / depositCount : 0;
    float avgWithdrawalAmount = withdrawalCount > 0 ? withdrawalTotal / withdrawalCount : 0;
    float avgInvestmentAmount = investmentCount > 0 ? investmentTotal / investmentCount : 0;

    printf("Matrix Operations:\n");
    printf("====================================\n");
    printf("Total number of records: %d\n", count);
    printf("Average prAmount: %.2f\n", prAmountAverage);
    printf("Average transAmount: %.2f\n", transAmountAverage);
    printf("Average intRate: %.2f\n", intRateAverage);
    printf("Average totalBalance: %.2f\n", totalBalanceAverage);
    printf("Maximum totalBalance: %.2f\n", maxTotalBalance);
    printf("Minimum totalBalance: %.2f\n", minTotalBalance);
    printf("Average Deposit Amount: %.2f\n", avgDepositAmount);
    printf("Average Withdrawal Amount: %.2f\n", avgWithdrawalAmount);
    printf("Average Investment Amount: %.2f\n", avgInvestmentAmount);
    printf("====================================\n");
}

int main() {
    printf("===========================================================================\n");
    printf("\t\t2D Matrix of Monthly Expenses\n");
    printf("===========================================================================\n");
    struct account finances[100]; // Define an array to hold account data
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Enter the number of rows\n");
        printf("2. Enter account details\n");
        printf("3. Delete a record\n");
        printf("4. Display account information\n");
        printf("5. Perform matrix operations\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                r = getPositiveIntInput();
                while ((getchar()) != '\n');  // Clearing the input buffer
                break;

            case 2:
                if (r <= 0) {
                    printf("Please enter the number of rows first.\n");
                } else {
                    for (i = 0; i < r; i++) {
                        printf("\nAccount %d:\n", i + 1);
                        read(&finances[i]);
                        while ((getchar()) != '\n');  // Clearing the input buffer
                    }
                }
                break;

            case 3:
                if (r <= 0) {
                    printf("Please enter the number of rows first.\n");
                } else {
                    printf("Enter the Account ID for the record you want to delete: ");
                    scanf("%d", &del_id);
                    delRecord(del_id, finances, &r);
                    while ((getchar()) != '\n');  // Clearing the input buffer
                }
                break;

            case 4:
                if (r <= 0) {
                    printf("Please enter the number of rows first.\n");
                } else {
                    for (i = 0; i < r; i++) {
                        printf("\nAccount %d:\n", i + 1);
                        display(finances[i]);
                    }
                }
                break;

            case 5:
                if (r <= 0) {
                    printf("Please enter the number of rows first.\n");
                } else {
                    matOperations(finances, r);
                }
                break;

            case 6:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}


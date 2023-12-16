#ifndef FINANCES_H
#define FINANCES_H

struct account {
    char holderName[30];
    int accId;
    char transType[10];
    float prAmount;
    float transAmount;
    float intRate;
    float intAmount;
    float totalBalance;
};

void read(struct account *acc);
void display(struct account acc);
void delRecord(int id, struct account *finances, int *count);
void matOperations(struct account *finances, int count);

#endif


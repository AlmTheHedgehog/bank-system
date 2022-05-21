#ifndef STRUCTS_H
#define STRUCTS_H

enum check_types{isName, isAdress, isPESEL, isAccNumber, isNumb};

typedef struct account_struct{
    long int account_id;
    char name[31];
    char surname[31];
    char adress[61];
    long int pesel;
    long int balance;
}account;

#endif

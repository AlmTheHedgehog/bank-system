#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdlib.h>
#include <stdio.h>

#define DB_PATH "db.bin"
#define NAME_LENGTH 31
#define ADRESS_LENGTH 61
enum check_types{isName, isAdress, isPESEL, isAccNumber, isNumb};
typedef enum boolean_en{true = 1, false = 0}boolean;

typedef struct account_struct{
    long int account_id;
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    char adress[ADRESS_LENGTH];
    long int pesel;
    long int balance;
}account;

void list_all_acc();

#endif

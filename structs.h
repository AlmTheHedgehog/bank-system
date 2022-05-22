#ifndef STRUCTS_H
#define STRUCTS_H

#define db_path "db.bin"
enum check_types{isName, isAdress, isPESEL, isAccNumber, isNumb};
typedef enum boolean_en{true = 1, false = 0}boolean;

typedef struct account_struct{
    long int account_id;
    char name[31];
    char surname[31];
    char adress[61];
    long int pesel;
    long int balance;
}account;

#endif

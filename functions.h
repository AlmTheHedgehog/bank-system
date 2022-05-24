#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void string_read(char text[], enum check_types check_type, short size, char output[]);
short int put_acccount_inDB(account acc, boolean isNew); //0 is not smth wrong, 1 if successful, -1 file doesn`t exist
long int int_read(char text[], enum check_types check_type);
double double_read(char text[], enum check_types check_type);
void wrong_in();
short int file_wrong(char text[], FILE* file); //0 is not smth wrong, -1 file doesn`t exist
void append_acc_toDB(account acc, FILE* file);
void filling_new_acc(account *acc);
short int search_acc(account *acc, enum search_options s_option, void* input_value); //0 - not found, 1 - found, -1 - error
void separate_name_surname(char input[], char name[], char surname[]);
void add_name_surname(char output[], char name[], char surname[]);
void change_balance(account *acc, boolean isPut_money);
void transfer(account *acc_source, account acc_dist);
boolean confirmation();

#endif
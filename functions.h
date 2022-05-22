#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void string_read(char text[], enum check_types check_type, short size, char output[]);
short int put_acccount_inDB(account acc, boolean isNew); //0 is not smth wrong, 1 if successful, -1 file doesn`t exist
long int int_read(char text[], enum check_types check_type);
void wrong_in();
short int file_wrong(char text[], FILE* file); //0 is not smth wrong, -1 file doesn`t exist
void append_acc_toDB(account acc, FILE* file);

#endif
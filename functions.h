#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "structs.h"

void string_read(char text[], enum check_types check_type, short size, char output[]);
long int int_read(char text[], enum check_types check_type);
void wrong_in();

#endif
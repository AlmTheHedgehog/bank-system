#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include "structs.h"
#include "functions.h"

#if defined(_WIN32) && defined(__GNUC__)
    #define clear_csl() system("cls")
#elif defined(__linux__) && defined(__GNUC__)
    #define clear_csl() system("clear")
#endif



#endif
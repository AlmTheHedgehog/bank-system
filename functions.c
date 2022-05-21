#include "structs.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

void string_read(char text[], enum check_types check_type, short size, char output[]){
    printf("%s", text);
    short int isIncorrect = 1;
    do{
        if(scanf("%[^\n]%*c", output) == 1){
            if(check_type == isAdress){
                isIncorrect = 0;
            }else if(check_type == isName){
                isIncorrect = 0;
                int i = 0;
                while(output[i] != '\0'){
                    if((!((output[i] >= 65) && (output[i] <= 90)) && !((output[i] >= 97) && (output[i] <= 122)))
                            && (output[i] !='\0')){
                        isIncorrect = 1;
                    }
                    i++;
                }
            }else{
                printf("!!!WRONG check_type in string_read()");
            }
        }
        if(isIncorrect){
            wrong_in();
        }
    }while(isIncorrect);
}

long int int_read(char text[], enum check_types check_type){
    printf("%s", text);
    long int output = 0;
    int onlyNumbers;
    char input_str[16];
    do{
        onlyNumbers = 1;
        scanf("%15[^\n]s", input_str);
        int c, i = 0;
        while ((c = getchar()) != '\n' && c != EOF);
        while(input_str[i] != '\0'){
            if(!((input_str[i] >= 48) & (input_str[i] <= 57)) && (input_str[i] != '\0')){
                onlyNumbers = 0;
            }
            i++;
        }
        if(onlyNumbers){
            output = atol(input_str);
            switch(check_type){
                case isPESEL:
                    if((output >= 10000000000) && (output <= 99999999999)){
                        return output;
                    }
                    break;
                case isAccNumber:
                    if((output >= 1000000000000) && (output <= 9999999999999)){
                        return output;
                    }
                    break;
                case isNumb:
                    return output;
                default:
                    printf("!!!WRONG check_type in string_read()");
            }
        }
        wrong_in();
    }while(1);
}

void wrong_in(){
    printf("Sorry, you entered invalid data, try again:");
}
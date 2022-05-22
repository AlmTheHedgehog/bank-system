#include <stdio.h>
#include "structs.h"
#include "functions.h"

int main(){
    boolean isWorking = true, isValid_answer;
    short int answer = 0;
    printf("Welcome in the banking system!\n");
    while(isWorking){
        printf("\n1 - create new account\n");
        printf("2 - list all accounts\n");
        printf("3 - exit\n");
        printf("What do you want:");
        isValid_answer = false;
        while(!isValid_answer){
            scanf("%hd", &answer);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            switch(answer){
                case 1:
                    isValid_answer = true;
                    account new_acc;
                    filling_new_acc(&new_acc);
                    if(put_acccount_inDB(new_acc, true) != 1){
                        printf("Smth went wrong, try again\n");
                    }
                    break;
                case 2:
                    isValid_answer = true;
                    list_all_acc();
                    break;
                case 3:
                    isValid_answer = true;
                    isWorking = false;
                    break;
                default:
                    printf("Sorry, invalid answer, try again:");
            }
        }

    }
    printf("Thank you for using our product!©\n");

    return 0;
}
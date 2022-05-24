#include "structs.h"
#include "functions.h"

void list_all_acc(){
    FILE* db;
    db = fopen(DB_PATH, "rb");
    if(db != NULL){
        account eachAcc;
        fread(&eachAcc, sizeof(account), 1, db);
        while(!feof(db)){
            printf("\n");
            print_acc_info(eachAcc);
            fread(&eachAcc, sizeof(account), 1, db);
        }
    }else{
        file_wrong("!!!NO SUCH FILE during listing", db);
    }
}

void print_acc_info(account eachAcc){
    printf("Account_id:%ld\n", eachAcc.account_id);
    printf("PESEL:%ld\n", eachAcc.pesel);
    printf("Name:%s\n", eachAcc.name);
    printf("Surname:%s\n", eachAcc.surname);
    printf("Adress:%s\n", eachAcc.adress);
    printf("Balance:%.2f\n", eachAcc.balance);
}
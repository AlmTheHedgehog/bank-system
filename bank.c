#include "bank.h"

void account_interface(account acc);
void account_entering_interface();
enum search_options account_search_option_interface();

int main(){
    boolean isWorking = true, isValid_answer;
    short int answer = 0;
    clear_csl();
    printf("Welcome to the banking system!\n");
    while(isWorking){
        printf("\n1 - create new account\n");
        printf("2 - list all accounts\n");
        printf("3 - find account\n");
        printf("4 - exit\n");
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
                    account_entering_interface();
                    clear_csl();
                    printf("Welcome to the banking system!");
                    break;
                case 4:
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

void account_interface(account acc){
    boolean isWorking = true, isValid_answer;
    short int answer = 0;
    clear_csl();
    printf("Welcome to your account!\n");
    print_acc_info(acc);
    while(isWorking){
        printf("\n1 - transfer\n");
        printf("2 - deposit\n");
        printf("3 - withdrawal\n");
        printf("4 - exit from account\n");
        printf("What do you want:");
        isValid_answer = false;
        while(!isValid_answer){
            scanf("%hd", &answer);
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            switch(answer){
                case 1:
                    break;
                case 2:
                    isValid_answer = true;
                    make_deposit(&acc);
                    clear_csl();
                    print_acc_info(acc);
                    break;
                case 3:
                    break;
                case 4:
                    isValid_answer = true;
                    if(confirmation()){
                        isWorking = false;
                    }
                    break;
                default:
                    printf("Sorry, invalid answer, try again:");
            }
        }
    }
}

void account_entering_interface(){
    account current_account;
    enum search_options s_option = account_search_option_interface();
    void* value_ptr;
    switch(s_option){
        case sName_surname:;
            char value_ns[NAME_LENGTH*2], name[NAME_LENGTH], surname[NAME_LENGTH];
            string_read("Enter name:", isName, NAME_LENGTH, name);
            string_read("Enter surname:", isName, NAME_LENGTH, surname);
            add_name_surname(value_ns, name, surname);
            value_ptr = (void*)value_ns;
            break;
        case sAdress:;
            char value_a[ADRESS_LENGTH];
            string_read("Enter adress:", isAdress, ADRESS_LENGTH, value_a);
            value_ptr = (void*)value_a;
            break;
        case sPESEL:;
            long int value_p = int_read("Enter PESEL:", isPESEL);
            value_ptr = (void*)(&value_p);
            break;
        case sAccount_id:;
            long int value_ai = int_read("Enter account id:", isAccNumber);
            value_ptr = (void*)(&value_ai);
            break;
    }
    if(search_acc(&current_account, s_option, value_ptr)){
        account_interface(current_account);
    }else{
        printf("Sorry, account wasn`t found");
    }
}

enum search_options account_search_option_interface(){
    short int answer = 0;
    printf("\n1 - Search by name and surname\n");
    printf("2 - Search by adress\n");
    printf("3 - Search by pesel\n");
    printf("4 - Search by account id\n");
    printf("Choose searching option:");
    while(1){
        scanf("%hd", &answer);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch(answer){
            case 1:
                return sName_surname;
            case 2:
                return sAdress;
            case 3:
                return sPESEL;
            case 4:
                return sAccount_id;
            default:
                printf("Sorry, invalid answer, try again:");
        }
    }
}
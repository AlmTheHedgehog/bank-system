#include "structs.h"
#include "functions.h"

void string_read(char text[], enum check_types check_type, short size, char output[]){
    printf("%s", text);
    boolean isIncorrect = true;
    int i;
    do{
        if(scanf("%[^\n]s", output) == 1){
            isIncorrect = false;
            i = 0;
            if(check_type == isAdress){
                while((output[i] !='\0') && (!isIncorrect)){
                    i++;
                    if(i > 60){
                        isIncorrect = true;
                        printf("Too long. ");
                    }
                }
            }else if(check_type == isName){
                while((output[i] !='\0') && (!isIncorrect)){
                    if((!((output[i] >= 65) && (output[i] <= 90)) && !((output[i] >= 97) && (output[i] <= 122)))
                            && (output[i] !='\0')){
                        isIncorrect = true;
                    }
                    i++;
                    if(i > 30){
                        isIncorrect = true;
                        printf("Too long. ");
                    }
                }
            }else{
                printf("!!!WRONG check_type in string_read()");
            }
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(isIncorrect){
            wrong_in();
        }
    }while(isIncorrect);
}

double double_read(char text[], enum check_types check_type){
    printf("%s", text);
    double output = 0;
    boolean onlyNumbers;
    boolean dot_found = false;
    char input_str[16];
    int i, j;
    do{
        onlyNumbers = true;
        scanf("%15[^\n]s", input_str);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        i = 0;
        j = 0;
        while(input_str[i] != '\0'){
            if(!((input_str[i] >= 48) && (input_str[i] <= 57)) && ((input_str[i] != '\0') && (input_str[i] != '.'))){
                onlyNumbers = false;
            }
            if(input_str[i] == '.'){
                if(dot_found){
                    onlyNumbers = false;
                }else{
                    dot_found = true;
                }
            }else if(dot_found){
                j++;
            }
            i++;
        }
        if((i > 14) || (j > 2)){
            onlyNumbers = false;
        }
        if(onlyNumbers){
            output = atof(input_str);
            switch(check_type){
                case isPESEL:
                    if(((output >= 10000000000) && (output <= 99999999999)) && (j == 0)){
                        return output;
                    }
                    break;
                case isAccNumber:
                    if(((output >= 1000000000000) && (output <= 9999999999999)) && (j == 0)){
                        return output;
                    }
                    break;
                case isNumb:
                    if(output >= 0){
                        return output;
                    }else{
                        printf("Can`t be negative. ");
                    }
                default:
                    printf("!!!WRONG check_type in string_read()");
            }
        }
        wrong_in();
    }while(1);
}

long int int_read(char text[], enum check_types check_type){
    return (long)double_read(text, check_type);
}

void wrong_in(){
    printf("Sorry, you entered invalid data, try again:");
}
short int file_wrong(char text[], FILE* file){
    if(text != NULL){
        printf("%s\n", text);
    }
    if(file != NULL){
        fclose(file);
        return 0;
    }else{
        return -1;
    }
}
boolean confirmation(){
    printf("Are you sure in you decision(y or n)?");
    char output = ' ';
    while(1){
        scanf("%c", &output);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if(output == 'y'){
            return true;
        }else if(output == 'n'){
            return false;
        }else{
            wrong_in();
        }
    }
}

short int put_acccount_inDB(account acc, boolean isNew){
    FILE* db;
    db = fopen(DB_PATH, "rb+");
    if(db != NULL){
        account read_acc;
        boolean isMatch_found = false;
        while((!(feof(db))) && (!isMatch_found)){
            fread(&read_acc, sizeof(read_acc), 1, db);
            if(acc.account_id == read_acc.account_id){
                isMatch_found = true;
                if(isNew){
                    return file_wrong("!!!SAME ACC_ID during puting new acc in put_account_inDB", db);
                }
            }else if((strcmp(acc.name, read_acc.name) == 0) && (strcmp(acc.surname, read_acc.surname) == 0)){
                if(isNew){
                    return file_wrong("Sorry, in system exists account with the same name&surname", db);
                }
            }else if(acc.pesel == read_acc.pesel){
                if(isNew){
                    return file_wrong("Sorry, in system exists account with the same PESEL", db);
                }
            }
        }
        if(isNew == false){
            if(isMatch_found){
                fseek(db, -sizeof(account), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, db);
                fclose(db);
                return 1;
            }else{
                return file_wrong("!!!NO SUCH RECORD IN DB TO CHANGE during put_account_inDB", db);
            }
        }else{
            append_acc_toDB(acc, db);
            return 1;
        }
    }else{
        if(isNew){
            append_acc_toDB(acc, db);
            return 1;
        }
        return file_wrong("!!!NO SUCH FILE during put_account_inDB", db);
    }
}

void append_acc_toDB(account acc, FILE* file){
    file_wrong(NULL, file);
    file = fopen(DB_PATH, "ab");
    fwrite(&acc, sizeof(acc), 1, file);
    fflush(file);
    fclose(file);
}

void filling_new_acc(account *acc){
    printf("Creating new account\n");
    string_read("Enter your name:", isName, NAME_LENGTH, acc->name);
    string_read("Enter your surname:", isName, NAME_LENGTH, acc->surname);
    string_read("Enter your adress:", isAdress, ADRESS_LENGTH, acc->adress);
    acc->pesel = int_read("Enter your PESEL:", isPESEL);
    acc->balance = double_read("Enter your balance:", isNumb);
    acc->account_id = ((acc->pesel % 10) + ((acc->pesel/10) % 10));
    if(acc->account_id > 9){
        acc->account_id /= 10;
    }
    acc->account_id *= 10;
    acc->account_id += (((acc->pesel/100) % 10) + ((acc->pesel/1000) % 10));
    if(acc->account_id > 99){
        acc->account_id /= 10;
    }
    acc->account_id = (acc->account_id * 100000000000) + acc->pesel;
}

short int search_acc(account *acc, enum search_options s_option, void* input_value){
    FILE* db;
    char name[NAME_LENGTH], surname[NAME_LENGTH], adress[ADRESS_LENGTH];
    long int acc_id, pesel;
    db = fopen(DB_PATH, "rb+");
    if(db != NULL){
        if(s_option == sName_surname){
            separate_name_surname((char*)input_value, name, surname);
        }else if(s_option == sAdress){
            strcpy(adress, (char*)input_value);
        }else if(s_option == sAccount_id){
            acc_id = *((long*)input_value);
        }else if(s_option == sPESEL){
            pesel = *((long*)input_value);
        }else{
            return file_wrong("!!!WRONG SEARCH OPTION in seardch_acc", db);
        }
        account read_acc;
        while(!feof(db)){
            fread(&read_acc, sizeof(read_acc), 1, db);
            if(s_option == sName_surname){
                if((strcmp(name, read_acc.name) == 0) && (strcmp(surname, read_acc.surname) == 0)){
                    *acc = read_acc;
                    return 1;
                }
            }else if(s_option == sAdress){
                if(strcmp(adress, read_acc.adress) == 0){
                    *acc = read_acc;
                    return 1;
                }
            }else if(s_option == sAccount_id){
                if(acc_id == read_acc.account_id){
                    *acc = read_acc;
                    return 1;
                }
            }else{
                if(pesel == read_acc.pesel){
                    *acc = read_acc;
                    return 1;
                }
            }
        }
        return 0;
    }else{
        return file_wrong("!!!CAN`T OPEN FILE during search_acc", db);
    }
}

void separate_name_surname(char input[], char name[], char surname[]){
    boolean is_ended = false;
    for(int i = 0; i < (NAME_LENGTH); i++){
        if(!is_ended){
            if(input[i] == ' '){
                is_ended = true;
                name[i] = '\0';
            }else{
                name[i] = input[i];
            }
        }else{
            name[i] = '\0';
        }
    }
    is_ended = false;
    for(int i = NAME_LENGTH; i < (NAME_LENGTH*2); i++){
        if(!is_ended){
            if(input[i] == ' '){
                is_ended = true;
                surname[i - NAME_LENGTH] = '\0';
            }else{
                surname[i - NAME_LENGTH] = input[i];
            }
        }else{
            surname[i - NAME_LENGTH] = '\0';
        }
    }
}

void add_name_surname(char output[], char name[], char surname[]){
    boolean is_ended = false;
    for(int i = 0; i < (NAME_LENGTH); i++){
        if(!is_ended){
            if(name[i] == '\0'){
                is_ended = true;
                output[i] = ' ';
            }else{
                output[i] = name[i];
            }
        }else{
            output[i] = ' ';
        }
    }
    is_ended = false;
    for(int i = NAME_LENGTH; i < (NAME_LENGTH*2); i++){
        if(!is_ended){
            if(surname[i - NAME_LENGTH] == '\0'){
                is_ended = true;
                output[i] = ' ';
            }else{
                output[i] = surname[i - NAME_LENGTH];
            }
        }else{
            output[i] = ' ';
        }
    }
}

void change_balance(account *acc, boolean isPut_money){
    double sum = double_read("Enter ammount:", isNumb);
    if(!isPut_money){
        while((acc->balance - sum) < 0.0001){
            printf("Not enough money. ");
            sum = int_read("Enter ammount:", isNumb);
        }
        if(confirmation()){
            acc->balance -= sum;
            put_acccount_inDB(*acc, false);
        }
    }else{    
        if(confirmation()){
            acc->balance += sum;
            put_acccount_inDB(*acc, false);
        }
    }
}

void transfer(account *acc_source, account acc_dist){
    double sum = double_read("Enter ammount for transfer:", isNumb);
    if((acc_source->balance) <= 0){
        printf("Sorry, you don`t have any money for transfer :(\n");
    }else{
        while((acc_source->balance - sum) < 0.000001){
            printf("Not enough money. ");
            sum = int_read("Enter ammount:", isNumb);
        }
        if(confirmation()){
            acc_source->balance -= sum;
            put_acccount_inDB(*acc_source, false);
            acc_dist.balance += sum;
            put_acccount_inDB(acc_dist, false);
        }
    }
}
#include "structs.h"
#include "functions.h"

void string_read(char text[], enum check_types check_type, short size, char output[]){
    printf("%s", text);
    boolean isIncorrect = 1;
    do{
        if(scanf("%[^\n]%*c", output) == 1){
            if(check_type == isAdress){
                isIncorrect = false;
            }else if(check_type == isName){
                isIncorrect = false;
                int i = 0;
                while(output[i] != '\0'){
                    if((!((output[i] >= 65) && (output[i] <= 90)) && !((output[i] >= 97) && (output[i] <= 122)))
                            && (output[i] !='\0')){
                        isIncorrect = true;
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
    boolean onlyNumbers;
    char input_str[16];
    do{
        onlyNumbers = true;
        scanf("%15[^\n]s", input_str);
        int c, i = 0;
        while ((c = getchar()) != '\n' && c != EOF);
        while(input_str[i] != '\0'){
            if(!((input_str[i] >= 48) & (input_str[i] <= 57)) && (input_str[i] != '\0')){
                onlyNumbers = false;
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

short int put_acccount_inDB(account acc, boolean isNew){
    FILE* db;
    db = fopen(db_path, "rb+");
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
    file = fopen(db_path, "ab");
    fwrite(&acc, sizeof(acc), 1, file);
    fflush(file);
    fclose(file);
}
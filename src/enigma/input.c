#include "enigma/input.h"
#include <stdlib.h>

int is_letter(char character){
    // return 1 if the char is caracter
    
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z');
}

int is_uppercase_letter(char character){
    // return 1 if the char is in uppercase
    
    return character >= 'A' && character <= 'Z';
}

int is_lowercase_letter(char character){
    // return 1 if the char is lowercase
    
    return character >= 'a' && character <= 'z';
}

char lowercase_to_uppercase(char character){
    // transforms lowercase letter into uppercase letter
    
    if(is_lowercase_letter(character)){
        return character - ('a' - 'A');
    }else {
        return character;
    }
}

int txt_length(char txt[]){
    // count the number of characters in a array of characters
    
    int i;
    for(i = 0; txt[i] != '\0'; i++){
        ;
    }
    return i;
}

char * transform_txt(char ipt[]){
    // returns the input txt formatted for the enigma machine
    // transforms the text by filtering out characters used by the machine
    // converts lowercase letters to uppercase
    
    int length = txt_length(ipt);
    if(length == 0){
        return NULL;
    }

    char * opt = malloc(length);

    int i;
    int count = 0;
    
    for(i=0; ipt[i]!='\0'; i++){
        if(is_letter(ipt[i])){
            if(is_lowercase_letter(ipt[i])){
                opt[count] = lowercase_to_uppercase(ipt[i]);
                count++;
            }
        }
    }

    opt[count+1] = '\0';
    opt = realloc(opt, count+1);
    return opt;
}
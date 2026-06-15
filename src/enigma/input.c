#include "enigma/input.h"

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
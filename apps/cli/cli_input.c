#include "cli_input.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 32

char * read_line(void){
    /*
    Reads user input, stores it in memory, and dynamically allocates
    enough memory for the line.

    Returns the address of the stored line.
    The caller must free the returned pointer.
    */

    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;

    char * txt = malloc(capacity);
    if(txt == NULL){
        return NULL;
    }

    while(1){
        int c = getchar();
        if(c == EOF){
            if(length == 0){
                free(txt);
                return NULL;
            }
            break;
        }
        
        if(c == '\n'){
            break;
        }

        if(length+1 >= capacity){
            size_t new_capacity = capacity * 2;
            char * new_txt = realloc(txt, new_capacity);
            if(new_txt == NULL){
                free(txt);
                return NULL;
            }
            txt = new_txt;
            capacity = new_capacity;
        }

        txt[length] = (char)c;
        length++;

    }
    
    txt[length] = '\0';
    
    char * optimized_txt = realloc(txt, length+1);
    if(optimized_txt != NULL){
        txt = optimized_txt;
    }
    
    return txt;
}
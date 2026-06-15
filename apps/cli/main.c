#include <stdio.h>
#include <string.h>
#include "enigma/input.h"

int is_line_egal(char *, char *);

int main(void) {
    printf("%s", "==================================\n");
    printf("%s", "Welcom to enigma machine simulator\n");
    while(1){
        char * line = NULL;
        size_t line_size = 0;

        printf("%s", "> ");
        if(getline(&line, &line_size, stdin) == -1){
            break;
        }

        if(is_line_egal(line, ":quit")){
            break;
        }

        // TODO launch enigma engine here ! (enigma.c)
    }
    
    return 0;
}

int is_line_egal(char * line, char * command){
    size_t lenght = strlen(command);
    return strncmp(line, command, lenght) == 0;
}
#include <stdio.h>
#include <string.h>
#include "enigma/input.h"
#include "cli_input.h"

int is_line_equal(char *, char *);

int main(void) {
    printf("%s", "==================================\n");
    printf("%s", "Welcom to enigma machine simulator\n");
    
    while(1){

        printf("%s", "> ");

        char * txt = read_line();
        if(is_line_equal(txt, ":quit")){
            break;
        }

        printf("%s\n", txt);

        // TODO launch enigma engine here ! (enigma.c)
        //free(line);
    }
    
    return 0;
}

int is_line_equal(char * line, char * command){
    size_t length = strlen(command);
    return strncmp(line, command, length) == 0;
}
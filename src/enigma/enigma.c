#include "enigma/enigma.h"
#include "enigma/input.h"
#include <stdlib.h>

char *enigma(char ipt[]){
    // the enigma engine entry point
    return transform_txt(ipt);

}
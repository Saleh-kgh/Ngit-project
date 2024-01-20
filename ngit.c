#include <stdio.h>
#include "syntaxErrorRecognizer.h"
#include <string.h>
int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "config")==0) {
        if(strcmp(argv[2], "user.name")==0 || strcmp(argv[3], "user.name")==0) userInfo(argc, argv);
        else if(strcmp(argv[2], "user.email")==0 || strcmp(argv[3], "user.email")==0) userInfo(argc, argv); 
        char alias_spell[6]="alais."; 
        for(int i=0; i<6; i++) {
            if(argv[3][i]!=alias_spell[i]) {
                break;
            }
            if(i==5) aliasCommand(argc, argv);
        }    
    }
    else if(strcmp(argv[1], "init")==0) {
        initCount(argc, argv);
    }
    else if(strcmp(argv[1], "add")==0) {
        addCommand(argc, argv);
    }
    else if(strcmp(argv[1], "status")==0) {
        statusCommand(argc, argv);
    }
    else {
        printf("Invalid command due to unacceptable depth number!");
    }
    return 0;
}
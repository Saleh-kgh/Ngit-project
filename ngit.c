#include <stdio.h>
#include "syntaxErrorRecognizer.h"
#include <string.h>
int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "config")==0) {
        if(strcmp(argv[2], "user.name")==0 || strcmp(argv[3], "user.name")==0) userInfoSER(argc, argv);
        else if(strcmp(argv[2], "user.email")==0 || strcmp(argv[3], "user.email")==0) userInfoSER(argc, argv); 
        char alias_spell[6]="alais."; 
        for(int i=0; i<6; i++) {
            if(argv[3][i]!=alias_spell[i]) {
                break;
            }
            if(i==5) aliasSER(argc, argv);
        }    
    }
    else if(strcmp(argv[1], "init")==0) {
        initSER(argc, argv);
    }
    else if(strcmp(argv[1], "add")==0) {
        addSER(argc, argv);
    }
    else if(strcmp(argv[1], "status")==0) {
        statusSER(argc, argv);
    }
    else if(strcmp(argv[1], "commit")==0) {
        commitSER(argc, argv);
    }
    else if(strcmp(argv[1], "set")==0) {
        setSER(argc, argv);
    }
    else if(strcmp(argv[1], "replace")==0) {
        replaceSER(argc, argv);
    }
    else if(strcmp(argv[1], "remove")==0) {
        removeSER(argc, argv);
    }
    else if(strcmp(argv[1], "log")==0) {
        logSER(argc, argv);
    }
    else if(strcmp(argv[1], "branch")==0) {
        branchSER(argc, argv);
    }
    else if(strcmp(argv[1], "checkout")==0) {
        checkoutSER(argc, argv);
    }
    else {
        printf("Invalid command due to misspell or extra words!");
    }
    return 0;
}
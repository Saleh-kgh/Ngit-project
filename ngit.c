#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "syntaxErrorRecognizer.h"
#include "ngitHiddenDir.h"

int main(int argc, char *argv[]) {
    if(strcmp(argv[1], "config")==0) {
        if(strcmp(argv[2], "user.name")==0 || strcmp(argv[3], "user.name")==0) if(userInfoSER(argc, argv)==0) return 0;
        else if(strcmp(argv[2], "user.email")==0 || strcmp(argv[3], "user.email")==0) if(userInfoSER(argc, argv)==0) return 0; 
        char alias_spell[6]="alais."; 
        for(int i=0; i<6; i++) {
            if(argv[3][i]!=alias_spell[i]) {
                break;
            }
            if(i==5)
                if(aliasSER(argc, argv)==0) return 0;
        }    
    }
    else if(strcmp(argv[1], "init")==0) {
        if(initSER(argc, argv)==0) return 0;
        int dirState = makeHiddenNgitDir();
    }
    else if(strcmp(argv[1], "add")==0) {
        if(addSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "status")==0) {
        if(statusSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "commit")==0) {
        if(commitSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "set")==0) {
        if(setSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "replace")==0) {
        if(replaceSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "remove")==0) {
        if(removeSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "log")==0) {
        if(logSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "branch")==0) {
        if(branchSER(argc, argv)==0) return 0;
    }
    else if(strcmp(argv[1], "checkout")==0) {
        if(checkoutSER(argc, argv)==0) return 0;
    }
    else {
        printf("Invalid command due to misspell or extra words!");
    }

    return 0;
}
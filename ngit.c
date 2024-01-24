#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "syntaxErrorRecognizer.h"
#include "ngitHiddenDir.h"
#include "logicErrorRecognizer.h"
#include "userinfoEditor.h"
#include "listofcontents.h"
#include "addtoStage.h"

struct startupinfo {
    char username[50];
    char useremail[100];
    char currentbranch[50];
    char currentpath[100];
    int repositoryCount;
}startupInfo;

void startUp() {
    FILE* startUpfile = fopen("d:\\ANGP\\ngit-project\\startUp.txt", "r");
    char content[100];
    fgets(content, sizeof(content), startUpfile);
    strcpy(startupInfo.username, content);
    fgets(content, sizeof(content), startUpfile);
    strcpy(startupInfo.useremail, content);
    int lineCount=0;
    while(fgets(content, sizeof(content), startUpfile) != NULL) {
        lineCount++;
        strcpy(startupInfo.currentpath, content);
    }
    startupInfo.repositoryCount=lineCount;
    fclose(startUpfile);
    FILE* branchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt","r");
    fgets(content, sizeof(content), branchfile);
    strcpy(startupInfo.currentbranch, content);
    fclose(branchfile);
}

int main(int argc, char *argv[]) {
    startUp();
    int RESreturnedValue=0;
    if(strcmp(argv[1], "config")==0) {
        if(strcmp(argv[2], "user.name")==0 || strcmp(argv[3], "user.name")==0) {
            RESreturnedValue = userInfoSER(argc, argv);
            if(RESreturnedValue==0) return 0;
            else if(RESreturnedValue==1) {
                userGlobalInfoE(argc, argv, 0);
            }
            else {
                if(userInfoLER()==0) return 0;
                userLocalInfoE(argc, argv, 0);
            }
        }
        else if(strcmp(argv[2], "user.email")==0 || strcmp(argv[3], "user.email")==0) {
            RESreturnedValue = userInfoSER(argc, argv);
            if(RESreturnedValue==0) return 0; 
            else if(RESreturnedValue==1) {
                userGlobalInfoE(argc, argv, 1);
            }
            else {
                if(userInfoLER()==0) return 0;
                userLocalInfoE(argc, argv, 1);
            }
        }
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
        if(initLER()==0) return 0;
        makeHiddenNgitDir();
        listDirectories(1);
        listFiles(1);
    }
    else if(strcmp(argv[1], "add")==0) {
        if(addSER(argc, argv)==0) return 0;
        if(addLER(argc, argv)==0) return 0;
        listDirectories(0);
        listFiles(0);
        if(argc==3) {
            addtoStage(argv[2]);
        }
        else {
            for(int i=3; i<argc; i++) {
                addtoStage(argv[i]);
            }
        }
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
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "syntaxErrorRecognizer.h"
#include "ngitHiddenDir.h"
#include "logicErrorRecognizer.h"
#include "userinfoEditor.h"
#include "listofcontents.h"
#include "addtoStage.h"
#include "resetStage.h"
#include "directoryStatus.h"
#include "commitCreator.h"
#include "totalStatus.h"
#include "commitMesSet.h"

struct startupinfo {
    char username[50];
    char useremail[100];
    char currentbranch[50];
}startupInfo;

/*void startUp() {
    FILE* userInfoptr = fopen("d:\\ANGP\\ngit-project\\userInfo.txt", "r");
    fscanf(userInfoptr, "%s%s", startupInfo.username, startupInfo.useremail);
    fclose(userInfoptr);
    FILE* branchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt","r");
    fscanf(branchfile, "%s", startupInfo.currentbranch);
    fclose(branchfile);
}*/

int main(int argc, char *argv[]) {
    //startUp();
    int RESreturnedValue=0;
    if(strcmp(argv[1], "config")==0) {
        if(strcmp(argv[2], "user.name")==0 || strcmp(argv[3], "user.name")==0) {
            RESreturnedValue = userInfoSER(argc, argv);
            if(RESreturnedValue==0) return 0;
            else if(RESreturnedValue==1) {
                userGlobalInfoE(argc, argv, 0);
                //startUp();
                return 0;
            }
            else {
                if(userInfoLER()==0) return 0;
                userLocalInfoE(argc, argv, 0);
                //startUp();
                return 0;
            }
        }
        else if(strcmp(argv[2], "user.email")==0 || strcmp(argv[3], "user.email")==0) {
            RESreturnedValue = userInfoSER(argc, argv);
            if(RESreturnedValue==0) return 0; 
            else if(RESreturnedValue==1) {
                userGlobalInfoE(argc, argv, 1);
                //startUp();
                return 0;
            }
            else {
                if(userInfoLER()==0) return 0;
                userLocalInfoE(argc, argv, 1);
                //startUp();
                return 0;
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
    /*if(strlen(startupInfo.username)<2 || strlen(startupInfo.useremail)<2) {
        printf("please edit your personal info before anythings\n");
        return 0;
    }*/
    else if(strcmp(argv[1], "init")==0) {
        if(initSER(argc, argv)==0) return 0;
        if(initLER()==0) return 0;
        makeHiddenNgitDir();
        listDirectories(1);
        listDirectories(0);
        listFiles(1);
        listFiles(0);
    }
    else if(strcmp(argv[1], "add")==0) {
        if(addSER(argc, argv)==0) return 0;
        /*if(addLER(argc, argv)==0) return 0;*/
        /*char target='*';
        char* result=strchr(argv[2], target);
        if(result!=NULL) {
            printf("wildcard mojood nist");
            return 0;
        } */
        listDirectories(0);
        listFiles(0);
        if(argc==3) {
            if(addLER(argv[2])==0) return 0;
            addtoStage(argv[2]); return 0;
        }
        else if(strcmp(argv[2], "-f")==0){
            for(int i=3; i<argc; i++) {
                if(addLER(argv[i])==0) continue;
                addtoStage(argv[i]);
            }
            return 0;
        }
        else {
            char *endptr;
            long result;
            result = strtol(argv[3], &endptr, 10);
            stageDepth(result);
        }
    }
    else if(strcmp(argv[1], "reset")==0) {
        if(resetSER(argc, argv)==0) return 0;
        /*if(resetLER(argc, argv)==0) return 0;*/
        listDirectories(0);
        listFiles(0);
        resetStage(argv[2]);
    }
    else if(strcmp(argv[1], "status")==0) {
        if(statusSER(argc, argv)==0) return 0;
        listDirectories(0);
        listFiles(0);
        totalStatus();
    }
    else if(strcmp(argv[1], "commit")==0) {
        if(commitSER(argc, argv)==0) return 0;
        if(commitLER()==0) return 0;
        listDirectories(0);
        listFiles(0);
        commitCreator(argv[3]);
        listDirectories(1);
        listFiles(1);
        listDirectories(0);
        listFiles(0);
    }
    else if(strcmp(argv[1], "set")==0) {
        if(setSER(argc, argv)==0) return 0;
        if(commitSetLER(argv[5])==0) return 0;
        commitMesSet(argv[3], argv[5]); return 0;
    }
    else if(strcmp(argv[1], "replace")==0) {
        if(replaceSER(argc, argv)==0) return 0;
        commitMesReplace(argv[3], argv[5]); return 0;
    }
    else if(strcmp(argv[1], "remove")==0) {
        if(removeSER(argc, argv)==0) return 0;
        commitMesRemove(argv[3]); return 0;
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
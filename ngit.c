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
#include "logFunctions.h"
#include "createBranch.h"
#include "checkOut.h"
#include "revertCommit.h"
#include "createTag.h"

int isAllowed=0;

struct startupinfo {
    char username[50];
    char useremail[100];
    char currentbranch[50];
}startupInfo;

void startUp() {
    FILE* userInfoptr = fopen("d:\\ANGP\\ngit-project\\userInfo.txt", "r");
    fscanf(userInfoptr, "%s%s", startupInfo.username, startupInfo.useremail);
    fclose(userInfoptr);
    FILE* branchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt","r");
    fscanf(branchfile, "%s", startupInfo.currentbranch);
    fclose(branchfile);
    char filePath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,filePath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(filePath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    char allCommitsPath[MAX_PATH]; sprintf(allCommitsPath, "%s\\ngit\\info\\allCommits.txt", repoPath);
    FILE* allCommitptr=fopen(allCommitsPath, "r");
    char line[100];
    char HeadHash[9];
    fgets(line, sizeof(line), allCommitptr);
    line[strcspn(line, "\n")] = '\0';
    fclose(allCommitptr);
    strcpy(HeadHash, line);
    char currenntHash[9];
    char curCommithashPath[MAX_PATH]; sprintf(curCommithashPath, "%s\\ngit\\info\\curCommitHash.txt", repoPath);
    FILE* curCommithashptr=fopen(curCommithashPath, "r"); fscanf(curCommithashptr, "%s", currenntHash); fclose(curCommithashptr);
    if(strcmp(currenntHash, HeadHash)==0) isAllowed=1;
}

int main(int argc, char *argv[]) {
    startUp();
    //if(isAllowed==0) printf("you are in detached HEAD state\nyou can only explore your project and use checkout commands\n");
    int RESreturnedValue=0;
    if(strcmp(argv[1], "config")==0 ) {
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
    else if(strcmp(argv[1], "init")==0 ) {
        if(initSER(argc, argv)==0) return 0;
        if(initLER()==0) return 0;
        makeHiddenNgitDir();
        listDirectories(1);
        listDirectories(0);
        listFiles(1);
        listFiles(0);
    }
    else if(strcmp(argv[1], "add")==0 ) {
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
            //if(addLER(argv[2])==0) return 0;
            addtoStage(argv[2]); return 0;
        }
        else if(strcmp(argv[2], "-f")==0){
            for(int i=3; i<argc; i++) {
                //if(addLER(argv[i])==0) continue;
                addtoStage(argv[i]);
            }
            return 0;
        }
        else {
            char *endptr;
            long result;
            result = strtol(argv[3], &endptr, 10);
            stageDepth(result); return 0;
        }
    }
    else if(strcmp(argv[1], "reset")==0 ) {
        if(resetSER(argc, argv)==0) return 0;
        if(resetLER(argc, argv)==0) return 0;
        listDirectories(0);
        listFiles(0);
        resetStage(argv[2]); return 0;
    }
    else if(strcmp(argv[1], "status")==0 ) {
        if(statusSER(argc, argv)==0) return 0;
        listDirectories(0);
        listFiles(0);
        totalStatus(); return 0;
    }
    else if(strcmp(argv[1], "commit")==0 ) {
        if(commitSER(argc, argv)==0) return 0;
        if(commitLER()==0) return 0;
        listDirectories(0);
        listFiles(0);
        if(commitSER(argc, argv)==2) commitCreator(1, argv[3]);
        if(commitSER(argc, argv)==1) commitCreator(0, argv[3]);
        listDirectories(1);
        listFiles(1);
        listDirectories(0);
        listFiles(0);
        return 0;
    }
    else if(strcmp(argv[1], "set")==0 ) {
        if(setSER(argc, argv)==0) return 0;
        if(commitSetLER(argv[5])==0) return 0;
        commitMesSet(argv[3], argv[5]); return 0;
    }
    else if(strcmp(argv[1], "replace")==0 ) {
        if(replaceSER(argc, argv)==0) return 0;
        commitMesReplace(argv[3], argv[5]); return 0;
    }
    else if(strcmp(argv[1], "remove")==0 ) {
        if(removeSER(argc, argv)==0) return 0;
        commitMesRemove(argv[3]); return 0;
    }
    else if(strcmp(argv[1], "log")==0) {
        if(logSER(argc, argv)==0) return 0;
        int returnValue=logLER(argc, argv);
        if(returnValue==0) return 0;
        if(returnValue==7) {
            normalLog();
            return 0;
        }
        if(returnValue==1) {
            numberLog(argv[3]);
            return 0;
        }
        if(returnValue==2) {
            branchLog(argv[3]);
            return 0;
        }
        if(returnValue==3) {
            authorLog(argv[3]);
            return 0;
        }
        if(returnValue==4 || returnValue==5) {
            dateLog(argv[3], returnValue-4);
            return 0;
        }
        if(returnValue==5) {
            wordLog(argv[3]);
            return 0;
        } 
    }
    else if(strcmp(argv[1], "branch")==0 ) {
        if(branchSER(argc, argv)==0) return 0;
        if(argc==3) createBranch(argv[2]);
        if(argc==2) listBranches();
        return 0;
    }
    else if(strcmp(argv[1], "checkout")==0) {
        int returnedVale=checkoutSER(argc, argv);
        if(returnedVale==0) return 0;
        if(returnedVale==1) checkoutBranch(argv[2], 0);
        else if(returnedVale==2) checkoutHash(argv[2]); 
        else if(returnedVale==3) checkoutHash(argv[2]); 
        return 0;
    }
    else if(strcmp(argv[1], "revert")==0) {
        int returnValue=revertSER(argc, argv);
        switch (returnValue) {
            case 0:
                printf("Invalid command due to misspell or extra words!");
                break;
            case 1:
                revertCommit(argv[2], "nuull", returnValue);
                break;
            case 2:
                checkoutHash(argv[3]);
                commitCreator(0, argv[2]);
                break;
            case 3:
                revertCommit(argv[2], "nuull", returnValue);
                break;
            case 4:
                revertCommit(argv[3], "null", returnValue);
                break;
            case 5:
                revertCommit(argv[3], argv[2], returnValue);
                break;
        }
        return 0;
    }
    else if(strcmp(argv[1], "tag")==0) {
        int returnValue=tagSER(argc, argv);
        switch (returnValue) {
            case 0:
                printf("invalid command due to misspell or extra words\n");
                break;
            case 1:
                createTag(argv[3], "no message", "null", 1);
                break;
            case 2:
                createTag(argv[3], argv[5], "null", 2);
                break;
            case 3:
                createTag(argv[3], "no message", argv[5], 3);
                break;
            case 4:
                createTag(argv[3], argv[5], argv[7], 4);
                break;
            case 5:
                createTag(argv[3], argv[5], "null", 5);
                break;
            case 6:
                createTag(argv[3], "no message", argv[5], 6);
                break;
            case 7:
                createTag(argv[3], argv[5], argv[7], 7);
                break;
        }
        return 0;
    }
    else {
        printf("Invalid command due to misspell or extra words\n");
    }
    return 0;
}
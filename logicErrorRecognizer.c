#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include "generalSubFunctions.h"

int userInfoLER() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[100];
    int repoexists=0;
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!=NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result=strstr(currentPath, repoPath);
        if(result!=NULL) {
            repoexists=1;
        }
    }
    if(repoexists==0) {
        printf("you are not inside any of your ngit repositories");
        return 0;
    }
    fclose(reposfile);
    return 1;
}

int initLER() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[100];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!=NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result=strstr(currentPath, repoPath);
        if(result!=NULL) {
            printf("repository initialization failed, this directory is a ngit repositiory or a subdirectory");
            return 0;
        }
    }
    fclose(reposfile);
    return 1;
}

int addLER(int argc, char* argv[]) { // hanooz wildcard piadesazi nashode
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    int flag=0;
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) {
            flag=1;
            break;
        } 
    }
    fclose(reposfile);
    if(flag==0) {
        printf("you are not inside any of your repositories");
        return 0;
    }
    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    FILE* stagedfiles=fopen(repoPath, "r");
    char stagedfile[MAX_PATH];
    char currentPathcopy[MAX_PATH];
    strcpy(currentPathcopy, currentPath);
    if(argc==3) {
        strcat(currentPath, "\\");
        strcat(currentPath, argv[2]);
        FILE* fileExisits=fopen(currentPath, "r");
        DIR* dirExsists=opendir(currentPath);
        if(fileExisits==NULL && dirExsists==NULL) {
            printf("this file is not inside this directory or doesn't exist in your repository");
            return 0;
        }
        while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
            size_t len = strlen(repoPath);
            if (len > 0 && repoPath[len - 1] == '\n') {
                repoPath[len - 1] = '\0';
            }
            char* result=strstr(currentPath, stagedfile);
            if(result!=NULL) {
                printf("this file is already staged via a parent directory or itself");
                return 0;
            }
        }
        return 1;
    }
    else if(strcmp(argv[3],"-f")==0) {
        for(int i=3; i<argc; i++) {
            strcpy(currentPath, currentPathcopy);
            strcat(currentPath, "\\");
            strcat(currentPath, argv[i]);
            FILE* fileExisits=fopen(currentPath, "r");
            if(fileExisits==NULL) {
                printf("some of your files don't exist in your repository or are in other directories");
                return 0;
            }
            while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
                size_t len = strlen(repoPath);
                if (len > 0 && repoPath[len - 1] == '\n') {
                    repoPath[len - 1] = '\0';
                }
                char* result=strstr(currentPath, stagedfile);
                if(result!=NULL) {
                    printf("some of your files are already staged via a parent directory or themselves");
                    return 0;
                }
            }
        }
        return 1;
    }
}

int resetLER(int argc, char* argv[]) {
    if(strcmp(argv[2], "-undo")==0) return 1;
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    int flag=0;
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) {
            flag=1;
            break;
        } 
    }
    fclose(reposfile);
    if(flag==0) {
        printf("you are not inside any of your repositories");
        return 0;
    }

    strcat(currentPath, "\\");
    strcat(currentPath, argv[2]);
    FILE* fileExisits=fopen(currentPath, "r");
    DIR* dirExsists=opendir(currentPath);
    if(fileExisits==NULL && dirExsists==NULL) {
        printf("this file is not inside this directory or doesn't exist in your repository");
        return 0;
    }

    char repoPathcopy[MAX_PATH];
    strcpy(repoPathcopy, repoPath);
    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    FILE* stagedfiles=fopen(repoPath, "r");
    char stagedfile[MAX_PATH];
    flag=0;
    while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
        size_t len = strlen(stagedfile);
        if (len > 0 && stagedfile[len - 1] == '\n') {
            stagedfile[len - 1] = '\0';
        }
        char* result=strstr(currentPath, stagedfile);
        if(result!=NULL) {
            flag=1;
        }
    }
    if(flag==0) {
        printf("this file is not in staging area");
        return 0;
    }
        
    char *match = strstr(currentPath, repoPathcopy);
    memmove(match, match + strlen(repoPathcopy), strlen(match + strlen(repoPathcopy)) + 1);
    strcat(repoPathcopy, "\\ngit\\stagingArea");
    strcat(repoPathcopy, currentPath);
    FILE* fileisStaged=fopen(repoPathcopy, "r");
    DIR* dirisStaged=opendir(repoPathcopy);
    if(fileisStaged==NULL && dirisStaged==NULL) {
        printf("this file is not in staging area");
        return 0;
    }
    return 1;
}

int commitLER() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) {
            break;
        } 
    }
    fclose(reposfile);

    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    FILE* stagedfileptr=fopen(repoPath, "r");
    int stagedCount=0;
    char stagedfile[MAX_PATH];
    while(fgets(stagedfile, sizeof(stagedfile), stagedfileptr) != NULL) {
        size_t len = strlen(stagedfile);
        if (len > 0 && stagedfile[len - 1] == '\n') {
            stagedfile[len - 1] = '\0';
        }
        if(strlen(stagedfile)>1) stagedCount++;
    }
    if(stagedCount==0) {
        printf("there is nothing in staging area to commit");
        return 0;
    }
    return 1;
}
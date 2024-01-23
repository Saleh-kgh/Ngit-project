#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int userInfoLER() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[100];
    int repoexists=0;
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!=NULL) {
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
        char* result=strstr(currentPath, repoPath);
        if(result!=NULL) {
            printf("repository initialization failed, this directory is a ngit repositiory or a subdirectory");
            return 0;
        }
    }
    fclose(reposfile);
    return 1;
}
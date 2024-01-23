#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int initLogicCheck() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[100];
    FILE* startupfile=fopen("d:\\ANGP\\ngit-project\\startUp.txt", "r");
    fgets(repoPath, sizeof(repoPath), startupfile);
    fgets(repoPath, sizeof(repoPath), startupfile);
    while(fgets(repoPath, sizeof(repoPath), startupfile)!=NULL) {
        char* result=strstr(currentPath, repoPath);
        if(result!=NULL) {
            printf("repository initialization failed, this directory is a ngit repositiory or a subdirectory");
            return 0;
        }
    }
    fclose(startupfile);
    return 1;
}
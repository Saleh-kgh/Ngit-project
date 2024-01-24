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

int addLER(int argc, char* argv[]) { // hanooz wildcard piadesazi nashode
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    int flag=0;
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
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
        if(fileExisits==NULL) {
            printf("this file doesn't exist in your repository");
            return 0;
        }
        while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
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
                printf("some of your files don't exist in your repository");
                return 0;
            }
            while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
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
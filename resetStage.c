#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void resetStage(char* argv) {
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
    
    char repoPathcopy1[MAX_PATH];
    strcpy(repoPathcopy1, repoPath);
    char repoPathcopy2[MAX_PATH];
    strcpy(repoPathcopy2, repoPath);
    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    strcat(repoPathcopy1, "\\ngit\\info\\newstagedfiles.txt");
    FILE* stagedfiles=fopen(repoPath, "r");
    FILE* newstagedfiles=fopen(repoPathcopy1, "w");
    char stagedfile[MAX_PATH];
    char lastStagedfile[MAX_PATH];
    if(strcmp(argv, "-undo")==0) {
        while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
            size_t len = strlen(stagedfile);
            if (len > 0 && stagedfile[len - 1] == '\n') {
                stagedfile[len - 1] = '\0';
            }
            strcpy(lastStagedfile, stagedfile);
        }
        char piecesofFilepath[10][20]; 
        int idx=0;
        char* piece=strtok(lastStagedfile, "\\");
        while(piece!=NULL) {
            strcpy(piecesofFilepath[idx], piece);
            piece=strtok(NULL,"\\");
            idx++;
        }
        strcpy(argv, piecesofFilepath[idx-1]);
        rewind(stagedfiles);
    }
    strcat(currentPath, "\\");
    strcat(currentPath, argv);
    while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
        size_t len = strlen(stagedfile);
        if (len > 0 && stagedfile[len - 1] == '\n') {
            stagedfile[len - 1] = '\0';
        }
        if(strcmp(currentPath, stagedfile)!=0) {
            fputs(stagedfile, newstagedfiles);
            fputs("\n", newstagedfiles);
        }
    }
    fclose(stagedfiles);
    fclose(newstagedfiles);
    remove(repoPath);
    rename(repoPathcopy1, repoPath);

    char *match = strstr(currentPath, repoPathcopy2);
    memmove(match, match + strlen(repoPathcopy2), strlen(match + strlen(repoPathcopy2)) + 1);
    strcat(repoPathcopy2, "\\ngit\\stagingArea");
    strcat(repoPathcopy2, currentPath);
    printf("%s\n", repoPathcopy2);
    if(remove(repoPathcopy2)!=0) printf("error removing file");
    RemoveDirectoryA(repoPathcopy2);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include "diffCheck.c"

int conflictThreat(char* sourceStoragePath, char* destinationStoragePath, int state) {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    char sourceTempFile[MAX_PATH];
    char destinationTempFile[MAX_PATH];
    char sourceFileType[5];
    char destinationFileType[5];
    char sourceFileModif[25];
    char destinationFileModif[25];
    FILE* sourceStorageptr=fopen(sourceStoragePath, "r");
    FILE* destinationStorageptr=fopen(destinationStoragePath, "r");
    int flag=0;
    while(fscanf(sourceStorageptr, "%s%s%s", sourceTempFile, sourceFileType, sourceFileModif)==3) {
        if(strcmp(sourceFileType, "d")==0) {
            if(strstr(sourceTempFile, ".txt")!=NULL) {  ///////////////// inja noe file ro age c ham bood lahaz mikonam
                rewind(destinationStorageptr);
                while(fscanf(destinationStorageptr, "%s%s%s", destinationTempFile, destinationFileType, destinationFileModif)==3) {
                    if(strcmp(sourceTempFile, destinationTempFile)==0) {
                        char commitedFiles[18]="commitedfiles.txt";
                        char commitSourceFilePath[MAX_PATH]; strcpy(commitSourceFilePath, sourceStoragePath);
                        char *match = strstr(commitSourceFilePath, commitedFiles);
                        memmove(match, match + strlen(commitedFiles), strlen(match + strlen(commitedFiles)) + 1); strcat(commitSourceFilePath, "content");
                        char *match = strstr(sourceTempFile, repoPath);
                        memmove(match, match + strlen(repoPath), strlen(match + strlen(repoPath)) + 1); strcat(commitSourceFilePath, sourceTempFile);
                        int returnValue=diffCheck(commitSourceFilePath, destinationTempFile);
                        if(returnValue==0) flag=1;
                        break;
                    }
                }
            }
        } 
    }
    if(flag==1) return 0;
    return 1;
}
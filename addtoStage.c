#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void addtoStage(char argv[]) {
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
    char stagedfileaddress[MAX_PATH];
    strcpy(stagedfileaddress, repoPath);
    strcat(stagedfileaddress, "\\ngit\\info\\stagedfiles.txt");
    char repoPathcopy[MAX_PATH];
    strcpy(repoPathcopy, filePath);
    strcat(filePath, "\\");
    strcat(filePath, argv);
    FILE* isfile=fopen(filePath, "r");
    char filePathcopy[MAX_PATH];
    strcpy(filePathcopy, filePath);        
    char *match = strstr(filePath, repoPath);
    memmove(match, match + strlen(repoPath), strlen(match + strlen(repoPath)) + 1);
    char piecesofFilepath[10][20]; 
    int idx=0;
    char* piece=strtok(filePath, "\\");
    while(piece!=NULL) {
        strcpy(piecesofFilepath[idx], piece);
        piece=strtok(NULL,"\\");
        idx++;
    }
    strcat(repoPath, "\\ngit\\stagingArea");
    if(isfile==NULL) {
        for(int i=0; i<idx-1; i++) {
            strcat(repoPath, "\\");               
            strcat(repoPath, piecesofFilepath[i]);
            DIR* dirptr=opendir(repoPath);
            if(dirptr==NULL) {
                CreateDirectory(repoPath, NULL);
            }               
        }
        strcat(repoPath, "\\");
        strcat(repoPath, piecesofFilepath[idx-1]);
        char filetocopy[MAX_PATH];
        FILE* stagedfilesptr=fopen(stagedfileaddress, "a");
        fputs(filePathcopy, stagedfilesptr);
        fputs("\n", stagedfilesptr);
        fclose(stagedfilesptr);
        FILE *batchFile = fopen("copydir.bat", "w");
        fprintf(batchFile, "@echo off\n");
        fprintf(batchFile, "set \"sourceDirectory=%s\"\n", filePathcopy);
        fprintf(batchFile, "set \"destinationDirectory=%s\"\n", repoPath);
        fprintf(batchFile, ")\n");
        fprintf(batchFile, "xcopy \"%%sourceDirectory%%\" \"%%destinationDirectory%%\" /E /I /Q /Y >nul\n");
        fprintf(batchFile, "exit /b 0\n");
        fclose(batchFile);
        system("copydir.bat");
        strcat(repoPathcopy, "\\copydir.bat");
        remove(repoPathcopy);
    }
    else {
        for(int i=0; i<idx-1; i++) {
            strcat(repoPath, "\\");               
            strcat(repoPath, piecesofFilepath[i]);
            DIR* dirptr=opendir(repoPath);
            if(dirptr==NULL) {
                CreateDirectory(repoPath, NULL);
            }               
        }
        strcat(repoPath, "\\");
        strcat(repoPath, piecesofFilepath[idx-1]);
        FILE *batchFile=fopen("copyfile.bat", "w");
        fprintf(batchFile, "@echo off\n");
        fprintf(batchFile, "set \"sourceFile=%s\"\n", filePathcopy);
        fprintf(batchFile, "set \"destinationFile=%s\"\n", repoPath);
        fprintf(batchFile, ")\n");
        fprintf(batchFile, "type \"%%sourceFile%%\" > \"%%destinationFile%%\"\n");
        fprintf(batchFile, "exit /b 0\n");
        fclose(batchFile);
        system("copyfile.bat");
        strcat(repoPathcopy, "\\copyfile.bat");
        remove(repoPathcopy);
        FILE* stagedfileptr=fopen(stagedfileaddress, "a");
        fputs(filePathcopy, stagedfileptr);
        fputs("\n", stagedfileptr);
        fclose(stagedfileptr);
    }   
    fclose(isfile);
}
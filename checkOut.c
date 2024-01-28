#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

void checkoutBranch(char* branchName) {
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

    char lastCommitBranPath[MAX_PATH]; sprintf(lastCommitBranPath, "%s\\ngit\\info\\%slastCommit.txt", repoPath, branchName);
    int lastCommit=0;
    FILE* lastCommitBranptr=fopen(lastCommitBranPath, "r"); fscanf(lastCommitBranptr, "%d", &lastCommit); fclose(lastCommitBranptr);
    char branchLastComContPath[MAX_PATH]; sprintf(branchLastComContPath, "%s\\ngit\\branches\\%s\\commits\\%d", repoPath, branchName, lastCommit);
    char branchCommitedFilesPath[MAX_PATH]; sprintf(branchCommitedFilesPath, "%s\\commitedfiles.txt", branchLastComContPath);
    char stagedFilesPath[MAX_PATH]; sprintf(stagedFilesPath, "%s\\ngit\\info\\stagedfiles.txt", repoPath);
    strcat(branchLastComContPath, "\\content");
    char tempFilePathtoCopy[MAX_PATH];
    char tempFiletypetoCopy[5];
    char tempFileModiftoCopy[25];
    FILE* commitedFilesptr=fopen(branchCommitedFilesPath, "r");
    while(fscanf(commitedFilesptr, "%s%s%s", tempFilePathtoCopy, tempFiletypetoCopy, tempFileModiftoCopy)==3) {
        if(strcmp(tempFiletypetoCopy, "d")==0) continue;
        char lastPieceofFiletoCopy[MAX_PATH];
        char piceseofFilePath[10][20];
        strcpy(lastPieceofFiletoCopy, tempFilePathtoCopy);
        char *match = strstr(lastPieceofFiletoCopy, repoPath);
        memmove(match, match + strlen(repoPath), strlen(match + strlen(repoPath)) + 1);
        int idx1=0;
        char* piece1=strtok(lastPieceofFiletoCopy, "\\");
        while(piece1!=NULL) {
            strcpy(piceseofFilePath[idx1], piece1);
            piece1=strtok(NULL,"\\");
            idx1++;
        }
        char tempFilePathsource[MAX_PATH];
        sprintf(tempFilePathsource, "%s", branchLastComContPath);
        char destFilePathsource[MAX_PATH];
        sprintf(destFilePathsource, "%s", repoPath);
        for(int i=0; i<idx1-1; i++) {
            strcat(tempFilePathsource, "\\");
            strcat(tempFilePathsource, piceseofFilePath[i]);
            strcat(destFilePathsource, "\\");
            strcat(destFilePathsource, piceseofFilePath[i]);
            DIR* dirptr=opendir(destFilePathsource);
            if(dirptr==NULL) {
                closedir(dirptr);
                CreateDirectory(destFilePathsource, NULL);
            }
            closedir(dirptr);
        }
        strcat(tempFilePathsource, "\\");
        strcat(tempFilePathsource, piceseofFilePath[idx1-1]);
        strcat(destFilePathsource, "\\");
        strcat(destFilePathsource, piceseofFilePath[idx1-1]);
        FILE *batchFile=fopen("copyfile.bat", "w");
        fprintf(batchFile, "@echo off\n");
        fprintf(batchFile, "copy /Y \"%s\" \"%s\" > NUL \n", tempFilePathsource, destFilePathsource);
        fprintf(batchFile, "exit /b 0\n");
        fclose(batchFile);
        system("copyfile.bat");
        char batFilePath[MAX_PATH];
        strcpy(batFilePath, filePath);
        strcat(batFilePath, "\\copyfile.bat");
        remove(batFilePath);
    }
    fclose(commitedFilesptr);
    FILE *batchFile=fopen("copyfile.bat", "w");
    fprintf(batchFile, "@echo off\n");
    fprintf(batchFile, "set \"sourceFile=%s\"\n", branchCommitedFilesPath);
    fprintf(batchFile, "set \"destinationFile=%s\"\n", stagedFilesPath);
    fprintf(batchFile, ")\n");
    fprintf(batchFile, "type \"%%sourceFile%%\" > \"%%destinationFile%%\"\n");
    fprintf(batchFile, "exit /b 0\n");
    fclose(batchFile);
    system("copyfile.bat");
    char batFilePath[MAX_PATH];
    strcpy(batFilePath, filePath);
    strcat(batFilePath, "\\copyfile.bat");
    remove(batFilePath);
    char currentbranchPath[MAX_PATH]; sprintf(currentbranchPath, "%s\\ngit\\info\\currentbranch.txt", repoPath);
    FILE* curBranchptr=fopen(currentbranchPath, "w"); fprintf(curBranchptr, "%s", branchName); fclose(curBranchptr);
    return;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <time.h>
#include <shellapi.h>

void commitCreator(char* message) {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len1 = strlen(repoPath);
        if (len1 > 0 && repoPath[len1 - 1] == '\n') {
            repoPath[len1 - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    FILE* totalCommmitptr=fopen("d:\\ANGP\\ngit-project\\totalCommitCount.txt", "r");
    int totalCommit=0;
    fscanf(totalCommmitptr, "%d", &totalCommit);
    fclose(totalCommmitptr);
    totalCommit++;
    totalCommmitptr=fopen("d:\\ANGP\\ngit-project\\totalCommitCount.txt", "w");
    fprintf(totalCommmitptr, "%d", totalCommit);
    fclose(totalCommmitptr);
    char lastCommitFilePath[MAX_PATH];
    strcpy(lastCommitFilePath, repoPath);
    strcat(lastCommitFilePath, "\\ngit\\info\\lastCommit.txt");
    FILE* lastCommitptr=fopen(lastCommitFilePath, "r");
    int lastCommit=0;
    fscanf(lastCommitptr, "%d", &lastCommit);
    fclose(lastCommitptr);
    lastCommit++;
    lastCommitptr=fopen(lastCommitFilePath, "w");
    fprintf(lastCommitptr, "%d", lastCommit);
    fclose(lastCommitptr);


    FILE* currentBranchptr=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt", "r");
    char currentbranch[25];
    fscanf(currentBranchptr, "%s", currentbranch);
    fclose(currentBranchptr);
    char commitFolderPath[MAX_PATH];
    strcpy(commitFolderPath, repoPath);
    strcat(commitFolderPath, "\\ngit\\branches\\");
    char restofCommitFolderPath[MAX_PATH];
    sprintf(restofCommitFolderPath, "%s\\commits\\%d", currentbranch, lastCommit);
    strcat(commitFolderPath, restofCommitFolderPath);
    CreateDirectory(commitFolderPath, NULL);
    char commitContentFilePath[MAX_PATH];
    char stagingAreapath[MAX_PATH];
    strcpy(commitContentFilePath, commitFolderPath);
    strcat(commitContentFilePath, "\\content");
    strcpy(stagingAreapath, repoPath);
    strcat(stagingAreapath, "\\ngit\\stagingArea");
    FILE* batchFile = fopen("copydir.bat", "w");
    fprintf(batchFile, "@echo off\n");
    fprintf(batchFile, "set \"sourceDirectory=%s\"\n", stagingAreapath);
    fprintf(batchFile, "set \"destinationDirectory=%s\"\n", commitContentFilePath);
    fprintf(batchFile, ")\n");
    fprintf(batchFile, "xcopy \"%%sourceDirectory%%\" \"%%destinationDirectory%%\" /E /I /Q /Y >nul\n");
    fprintf(batchFile, "exit /b 0\n");
    fclose(batchFile);
    system("copydir.bat");
    char batFilePath[MAX_PATH];
    strcpy(batFilePath, currentPath);
    strcat(batFilePath, "\\copydir.bat");
    if(remove(batFilePath)!=0) printf("failed to remove batchfile\n");
    char localuserPath[MAX_PATH];
    strcpy(localuserPath, repoPath);
    strcat(localuserPath, "\\ngit\\info\\localuser.txt");
    FILE* localUserptr=fopen(localuserPath, "r");
    char username[50];
    char useremail[50];
    fgets(username, sizeof(username), localUserptr);
    size_t len2 = strlen(username);
    if (len2 > 0 && username[len2 - 1] == '\n') {
        username[len2 - 1] = '\0';
    }
    fgets(useremail, sizeof(useremail), localUserptr);
    size_t len3 = strlen(useremail);
    if (len3 > 0 && useremail[len3 - 1] == '\n') {
        useremail[len3 - 1] = '\0';
    }
    fclose(localUserptr);
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);
    char* dateandTime=asctime(localTime);
    char commitDetailPath[MAX_PATH];
    strcpy(commitDetailPath, commitFolderPath);
    strcat(commitDetailPath, "\\commitDetail.txt");
    FILE* commitDetailptr=fopen(commitDetailPath, "w");
    fprintf(commitDetailptr, "%08d\n%s\n%s\n%s\n%s", totalCommit, message, username, useremail, dateandTime);
    fclose(commitDetailptr);
    printf("commited successfully\n%08d\n%s\n%s\n%s\n%s", totalCommit, message, username, useremail, dateandTime);
    char commithashPath[MAX_PATH];
    strcpy(commithashPath, repoPath);
    strcat(commithashPath, "\\ngit\\info\\commithashes.txt");
    FILE* commithashptr=fopen(commithashPath, "a");
    fprintf(commithashptr, "%08d\n", totalCommit);
    fclose(commithashptr);
    char commitedfilesPath[MAX_PATH];
    strcpy(commitedfilesPath, commitFolderPath);
    strcat(commitedfilesPath, "\\commitedfiles.txt");
    char stagedfilesPath[MAX_PATH];
    strcpy(stagedfilesPath, repoPath);
    strcat(stagedfilesPath, "\\ngit\\info\\stagedfiles.txt");
    char begstagedfilesPath[MAX_PATH];
    strcpy(begstagedfilesPath, repoPath);
    strcat(begstagedfilesPath, "\\ngit\\info\\begstagedfiles.txt");
    FILE* batchFile1=fopen("copyfile.bat", "w");
    fprintf(batchFile1, "@echo off\n");
    fprintf(batchFile1, "set \"sourceFile=%s\"\n", stagedfilesPath);
    fprintf(batchFile1, "set \"destinationFile=%s\"\n", commitedfilesPath);
    fprintf(batchFile1, ")\n");
    fprintf(batchFile1, "type \"%%sourceFile%%\" > \"%%destinationFile%%\"\n");
    fprintf(batchFile1, "exit /b 0\n");
    fclose(batchFile1);
    system("copyfile.bat");
    char batFile1Path[MAX_PATH];
    strcpy(batFile1Path, currentPath);
    strcat(batFile1Path, "\\copyfile.bat");
    if(remove(batFile1Path)!=0) printf("failed to remove batchfile1\n");
    char subPath0[MAX_PATH];
    char subType0[5];
    char subModified0[30];
    FILE* stagedFilesptr=fopen(stagedfilesPath, "r");
    FILE* begstagedFilesptr=fopen(begstagedfilesPath, "w");
    while(fscanf(stagedFilesptr, "%s%s%s", subPath0, subType0, subModified0)==3) {
        fprintf(begstagedFilesptr, "%s %s %s\n", subPath0, subType0, subModified0);
    }
    fclose(stagedFilesptr);
    fclose(begstagedFilesptr);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

void normalLog() {
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

    char allCommitPath[MAX_PATH];
    strcpy(allCommitPath, repoPath);
    strcat(allCommitPath, "\\ngit\\info\\allCommits.txt");
    FILE* allCommitptr=fopen(allCommitPath, "r");
    char line[100];
    char commitData[7][100];
    while (fgets(line, sizeof(line), allCommitptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(commitData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allCommitptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[i], line);
        }
        printf("commit hash: %s\non branch: %s\nnumber of files commited: %s\ncommit message: %s\nauthor: %s\nemail of author: %s\ndate commited: %s\n////////////////////////////////////////////////\n"
        , commitData[0], commitData[1], commitData[2], commitData[3], commitData[4], commitData[5], commitData[6]);
    }
    fclose(allCommitptr);
}        

void numberLog(char* count) {
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

    int number = atoi(count);
    char allCommitPath[MAX_PATH];
    strcpy(allCommitPath, repoPath);
    strcat(allCommitPath, "\\ngit\\info\\allCommits.txt");
    FILE* allCommitptr=fopen(allCommitPath, "r");
    char line[100];
    char commitData[7][100];
    while (number>0 && fgets(line, sizeof(line), allCommitptr)) {
        number--;
        line[strcspn(line, "\n")] = '\0';
        strcpy(commitData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allCommitptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[i], line);
        }
        printf("commit hash: %s\non branch: %s\nnumber of files commited: %s\ncommit message: %s\nauthor: %s\nemail of author: %s\ndate commited: %s\n////////////////////////////////////////////////\n"
        , commitData[0], commitData[1], commitData[2], commitData[3], commitData[4], commitData[5], commitData[6]);
    }
    fclose(allCommitptr);
}

void branchLog(char* branch) {
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

    char allCommitPath[MAX_PATH];
    strcpy(allCommitPath, repoPath);
    strcat(allCommitPath, "\\ngit\\info\\allCommits.txt");
    FILE* allCommitptr=fopen(allCommitPath, "r");
    char line[100];
    char commitData[7][100];
    while (fgets(line, sizeof(line), allCommitptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(commitData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allCommitptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[i], line);
        }
        if(strcmp(branch, commitData[1])==0) {
            printf("commit hash: %s\non branch: %s\nnumber of files commited: %s\ncommit message: %s\nauthor: %s\nemail of author: %s\ndate commited: %s\n////////////////////////////////////////////////\n"
            , commitData[0], commitData[1], commitData[2], commitData[3], commitData[4], commitData[5], commitData[6]);
        }  
    }
    fclose(allCommitptr);
}

void authorLog(char* author) {
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

    char allCommitPath[MAX_PATH];
    strcpy(allCommitPath, repoPath);
    strcat(allCommitPath, "\\ngit\\info\\allCommits.txt");
    FILE* allCommitptr=fopen(allCommitPath, "r");
    char line[100];
    char commitData[7][100];
    while (fgets(line, sizeof(line), allCommitptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(commitData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allCommitptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[i], line);
        }
        if(strcmp(author, commitData[4])==0) {
            printf("commit hash: %s\non branch: %s\nnumber of files commited: %s\ncommit message: %s\nauthor: %s\nemail of author: %s\ndate commited: %s\n////////////////////////////////////////////////\n"
            , commitData[0], commitData[1], commitData[2], commitData[3], commitData[4], commitData[5], commitData[6]);
        }  
    }
    fclose(allCommitptr);
}

void wordLog(char* targetWord) {
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

    char allCommitPath[MAX_PATH];
    strcpy(allCommitPath, repoPath);
    strcat(allCommitPath, "\\ngit\\info\\allCommits.txt");
    FILE* allCommitptr=fopen(allCommitPath, "r");
    char line[100];
    char commitData[7][100];
    while (fgets(line, sizeof(line), allCommitptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(commitData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allCommitptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[i], line);
        }
        if(strstr(commitData[3], targetWord)!=NULL) {
            printf("commit hash: %s\non branch: %s\nnumber of files commited: %s\ncommit message: %s\nauthor: %s\nemail of author: %s\ndate commited: %s\n////////////////////////////////////////////////\n"
            , commitData[0], commitData[1], commitData[2], commitData[3], commitData[4], commitData[5], commitData[6]);
        }
    }
    fclose(allCommitptr);
}
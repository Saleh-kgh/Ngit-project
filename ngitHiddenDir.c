#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "syntaxErrorRecognizer.h"

int makeHiddenNgitDir() {
    char *folderName = "ngit";
    char currentDirectory[MAX_PATH];
    if (GetCurrentDirectory(MAX_PATH, currentDirectory) != 0) {
        strcat(currentDirectory, "\\");
        strcat(currentDirectory, folderName);
        if (CreateDirectory(currentDirectory, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
            if (GetLastError() == ERROR_ALREADY_EXISTS) {
                printf("directory is already set as a ngit repository.");
            } 
            else if (SetFileAttributes(currentDirectory, FILE_ATTRIBUTE_DIRECTORY)) {
                printf("directory is succesfully initialized as a ngit repository.\n");
                FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "a");
                fputs("\n", reposfile);
                char currentDirectory[MAX_PATH];
                GetCurrentDirectory(MAX_PATH, currentDirectory);
                fputs(currentDirectory, reposfile);
                fclose(reposfile);
                char curDirpathCopy[MAX_PATH];
                strcat(currentDirectory, "\\ngit");
                strcpy(curDirpathCopy, currentDirectory);
                strcat(currentDirectory, "\\info");
                CreateDirectory(currentDirectory, NULL);
                FILE* userInfofile = fopen("d:\\ANGP\\ngit-project\\userInfo.txt", "r+");
                char content[100];
                char username[100];
                char useremail[100];
                fgets(content, sizeof(content), userInfofile);
                strcpy(username, content);
                fgets(content, sizeof(content), userInfofile);
                strcpy(useremail, content);
                fclose(userInfofile);
                strcat(currentDirectory, "\\localuser.txt");
                FILE* fptr=fopen(currentDirectory, "w");
                fputs(username, fptr);
                fputs(useremail, fptr);
                //fputs("1\n", fptr); // tedade branch
                //fputs("0", fptr); // tedade commit
                fclose(fptr);
                strcpy(currentDirectory, curDirpathCopy);
                strcat(currentDirectory, "\\info\\commithasehs.txt");
                FILE* fptr2=fopen(currentDirectory, "w");
                fclose(fptr2);
                strcpy(currentDirectory, curDirpathCopy);
                strcat(currentDirectory, "\\branches");
                CreateDirectory(currentDirectory, NULL);
                strcat(currentDirectory, "\\master");
                CreateDirectory(currentDirectory, NULL);
                strcat(currentDirectory, "\\commithistory");
                CreateDirectory(currentDirectory, NULL);
                strcpy(currentDirectory, curDirpathCopy);
                strcat(currentDirectory, "\\stagingArea");
                CreateDirectory(currentDirectory, NULL);
                strcpy(currentDirectory, curDirpathCopy);
                strcat(currentDirectory, "\\stashingArea");
                CreateDirectory(currentDirectory, NULL);
                FILE* curbranchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt", "r");
                if(curbranchfile==NULL) {
                    fclose(curbranchfile);
                    curbranchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt", "w");
                    fputs("master", curbranchfile);
                }
                else {
                    fclose(curbranchfile);
                    remove("d:\\ANGP\\ngit-project\\currentbranch.txt");
                    curbranchfile=fopen("d:\\ANGP\\ngit-project\\currentbranch.txt", "w");
                    fputs("master", curbranchfile);
                }
                fclose(curbranchfile);
            } 
        } 
        else {
            printf("systemic error creating repository.");
            return 0;
        }
    }
    return 1;
}


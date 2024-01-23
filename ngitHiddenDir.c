#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "syntaxErrorRecognizer.h"

int makeHiddenNgitDir() {
    char *folderName = "ngit";
    char currentDirectory[MAX_PATH];
    int returnValue=0;
    if (GetCurrentDirectory(MAX_PATH, currentDirectory) != 0) {
        strcat(currentDirectory, "\\");
        strcat(currentDirectory, folderName);
        if (CreateDirectory(currentDirectory, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
            if (GetLastError() == ERROR_ALREADY_EXISTS) {
                printf("directory is already set as a ngit repository.");
                returnValue=1;
            } 
            else if (SetFileAttributes(currentDirectory, FILE_ATTRIBUTE_DIRECTORY)) {
                printf("directory is succesfully initialized as a ngit repository.\n");
            } 
        } 
        else {
            printf("systemic error creating repository.");
            return 0;
        }
    }
    if(returnValue==1) return 2;
    return 1;
}
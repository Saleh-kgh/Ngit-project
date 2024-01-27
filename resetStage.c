#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void removeDirectory(const char* path) {
    SHFILEOPSTRUCT fileOp = {
        .hwnd   = NULL,
        .wFunc  = FO_DELETE,
        .pFrom  = path,
        .pTo    = NULL,
        .fFlags = FOF_NOCONFIRMATION | FOF_SILENT | FOF_NOERRORUI,
        .fAnyOperationsAborted = FALSE,
        .hNameMappings = NULL
    };

    int result = SHFileOperation(&fileOp);
    if (result == 0) {
        printf("Directory '%s' successfully removed.\n", path);
    } else {
        printf("Error removing directory. Error code: %d\n", result);
    }
}

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
    char lastStagedfile[MAX_PATH];
    char subPath0[MAX_PATH];
    char subPath1[MAX_PATH];
    char subType0[5];
    char subType1[5];
    char subModified0[30];
    char subModified1[30];
    if(strcmp(argv, "-undo")==0) {
        while(fscanf(stagedfiles, "%s%s%s", subPath0, subType0, subModified0)==3) {
            strcpy(lastStagedfile, subPath0);
        }
        char repoPathcopy3[MAX_PATH];
        strcpy(repoPathcopy3, repoPathcopy2);
        strcat(repoPathcopy3, "\\");
        char *match = strstr(lastStagedfile, repoPathcopy3);
        memmove(match, match + strlen(repoPathcopy3), strlen(match + strlen(repoPathcopy3)) + 1);
        strcpy(argv, lastStagedfile);
        rewind(stagedfiles);
    }
    strcat(currentPath, "\\");
    strcat(currentPath, argv);
    char needlePath[MAX_PATH];
    strcpy(needlePath, currentPath);
    strcat(needlePath, "\\");
    while(fscanf(stagedfiles, "%s%s%s", subPath0, subType0, subModified0)==3) {
        if(strstr(subPath0, needlePath)==NULL && strcmp(currentPath, subPath0)!=0) {
            fprintf(newstagedfiles, "%s %s %s\n", subPath0, subType0, subModified0);
        }
    }
    fclose(stagedfiles);
    fclose(newstagedfiles);
    SetFileAttributes(repoPath, FILE_ATTRIBUTE_NORMAL);
    DeleteFile(repoPath);                                  
    rename(repoPathcopy1, repoPath);

    char *match = strstr(currentPath, repoPathcopy2);
    memmove(match, match + strlen(repoPathcopy2), strlen(match + strlen(repoPathcopy2)) + 1);
    strcat(repoPathcopy2, "\\ngit\\stagingArea");
    strcat(repoPathcopy2, currentPath);
    FILE* fptr=fopen(repoPathcopy2, "r");
    DIR* dptr=opendir(repoPathcopy2);
    if(fptr!=NULL) {
        fclose(fptr);
        SetFileAttributes(repoPathcopy2, FILE_ATTRIBUTE_NORMAL);
        DeleteFile(repoPathcopy2);
    }
    else {
        closedir(dptr);
        printf("%s\n", repoPathcopy2);
        removeDirectory(repoPathcopy2);
    }                                  
}
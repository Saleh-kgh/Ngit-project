#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <sys/stat.h>
#include "generalSubFunctions.h"

int userInfoLER() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[100];
    int repoexists=0;
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!=NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
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
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        
        char* result=strstr(currentPath, repoPath);
        int idx1=0;
        char* piece1=strtok(currentPath, "\\");
        while(piece1!=NULL) {
            piece1=strtok(NULL,"\\");
            idx1++;
        }
        int idx2=0;
        char* piece2=strtok(repoPath, "\\");
        while(piece2!=NULL) {
            piece2=strtok(NULL,"\\");
            idx2++;
        }
        if(result!=NULL && idx1!=idx2) {
            printf("repository initialization failed, this directory is a ngit repositiory or a subdirectory");
            return 0;
        }
    }
    fclose(reposfile);
    return 1;
}

int addLER(char* argv) { // hanooz wildcard piadesazi nashode
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    int flag=0;
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        flag=0;
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) {
            char currentPath1[MAX_PATH];
            char repoPath1[MAX_PATH];
            strcpy(currentPath1, currentPath);
            strcpy(repoPath1, repoPath);
            char piecesofFilepath1[10][20];
            char piecesofFilepath2[10][20];
            int idx1=0;
            char* piece1=strtok(currentPath1, "\\");
            while(piece1!=NULL) {
                strcpy(piecesofFilepath1[idx1], piece1);
                piece1=strtok(NULL,"\\");
                idx1++;
            }
            int idx2=0;
            char* piece2=strtok(repoPath1, "\\");
            while(piece2!=NULL) {
                strcpy(piecesofFilepath2[idx2], piece2);
                piece2=strtok(NULL,"\\");
                idx2++;
            }
            for(int i=0; i<idx2; i++) {
                if(strcmp(piecesofFilepath1[i], piecesofFilepath2[i])!=0) flag=1;
            } 
            if(flag==0) break;
        }
    }
    fclose(reposfile);
    if(flag==1) {
        printf("you are not inside any of your repositories\n");
        return 0;
    }
    char newAlladdress[MAX_PATH];
    char stagedFilesaddress[MAX_PATH];
    strcpy(newAlladdress, repoPath);
    strcpy(stagedFilesaddress, repoPath);
    strcat(newAlladdress, "\\ngit\\info\\contents\\newAll.txt");
    strcat(stagedFilesaddress, "\\ngit\\info\\stagedfiles.txt");
    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    FILE* stagedfiles=fopen(repoPath, "r");
    char stagedfile[MAX_PATH];
    char currentPathcopy[MAX_PATH];
    strcpy(currentPathcopy, currentPath);
    strcat(currentPath, "\\");
    strcat(currentPath, argv);
    FILE* fileExisits=fopen(currentPath, "r");
    int dirFlag=0;
    struct stat directoryInfo;
    if (stat(currentPath, &directoryInfo) != 0) {
    }
    if (S_ISDIR(directoryInfo.st_mode)) {
        dirFlag=1;
    }
    if(fileExisits==NULL && dirFlag==0) {
        printf("this file <%s> is not inside this directory or doesn't exist in your repository\n", argv);
        fclose(fileExisits);
        return 0;
    }
    FILE* newAllptr=fopen(newAlladdress, "r");
    FILE* stagedFilesptr=fopen(stagedFilesaddress, "r");
    char subPath0[MAX_PATH];
    char subPath1[MAX_PATH];
    char subType0[5];
    char subType1[5];
    char subModified0[30];
    char subModified1[30];
    while(fscanf(newAllptr, "%s%s%s", subPath0, subType0, subModified0)==3) {
        if(strcmp(subPath0, currentPath)==0) {
            while(fscanf(stagedFilesptr, "%s%s%s", subPath1, subType1, subModified1)==3) {
                if(strcmp(subPath0, subPath1)==0) {
                    if(strcmp(subModified0, subModified1)==0) {
                        printf("this file <%s> contains no recent changes to add", argv);
                        return 0;
                    }
                    break;
                }
            }
            break;
        }
    }
    return 1;
    /*if(argc==3) {
        strcat(currentPath, "\\");
        strcat(currentPath, argv[2]);
        FILE* fileExisits=fopen(currentPath, "r");
        DIR* dirExsists=opendir(currentPath);
        if(fileExisits==NULL && dirExsists==NULL) {
            printf("this file is not inside this directory or doesn't exist in your repository");
            return 0;
        }
        while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
            size_t len = strlen(repoPath);
            if (len > 0 && repoPath[len - 1] == '\n') {
                repoPath[len - 1] = '\0';
            }
            char* result=strstr(currentPath, stagedfile);
            if(result!=NULL) {
                printf("this file is already staged via a parent directory or itself");
                return 0;
            }
        }
        return 1;
    }*/
}

int resetLER(int argc, char* argv[]) {
    if(strcmp(argv[2], "-undo")==0) return 1;
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    int flag=0;
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
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

    strcat(currentPath, "\\");
    strcat(currentPath, argv[2]);
    FILE* fileExisits=fopen(currentPath, "r");
    DIR* dirExsists=opendir(currentPath);
    if(fileExisits==NULL && dirExsists==NULL) {
        printf("this file is not inside this directory or doesn't exist in your repository");
        return 0;
    }

    char repoPathcopy[MAX_PATH];
    strcpy(repoPathcopy, repoPath);
    strcat(repoPath, "\\ngit\\info\\stagedfiles.txt");
    FILE* stagedfiles=fopen(repoPath, "r");
    char stagedfile[MAX_PATH];
    flag=0;
    while(fgets(stagedfile, sizeof(stagedfile), stagedfiles)!=NULL) {
        size_t len = strlen(stagedfile);
        if (len > 0 && stagedfile[len - 1] == '\n') {
            stagedfile[len - 1] = '\0';
        }
        char* result=strstr(currentPath, stagedfile);
        if(result!=NULL) {
            flag=1;
        }
    }
    if(flag==0) {
        printf("this file is not in staging area");
        return 0;
    }
        
    char *match = strstr(currentPath, repoPathcopy);
    memmove(match, match + strlen(repoPathcopy), strlen(match + strlen(repoPathcopy)) + 1);
    strcat(repoPathcopy, "\\ngit\\stagingArea");
    strcat(repoPathcopy, currentPath);
    FILE* fileisStaged=fopen(repoPathcopy, "r");
    DIR* dirisStaged=opendir(repoPathcopy);
    if(fileisStaged==NULL && dirisStaged==NULL) {
        printf("this file is not in staging area");
        return 0;
    }
    return 1;
}

int commitLER() {
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

    char stagedFielsaddress[MAX_PATH];
    char oldAllFilesaddress[MAX_PATH];
    char newAllFilesaddress[MAX_PATH];
    strcpy(stagedFielsaddress, repoPath);
    strcpy(oldAllFilesaddress, repoPath);
    strcpy(newAllFilesaddress, repoPath);
    strcat(stagedFielsaddress, "\\ngit\\info\\stagedfiles.txt");
    strcat(oldAllFilesaddress, "\\ngit\\info\\contents\\oldAll.txt");
    strcat(newAllFilesaddress, "\\ngit\\info\\contents\\newAll.txt");
    int countStagedFiles=0;
    int countUnmodifiedFiles=0;
    char subPath0[MAX_PATH];
    char subPath1[MAX_PATH];
    char subType0[5];
    char subType1[5];
    char subModified0[30];
    char subModified1[30];
    FILE* stagedFilesptr=fopen(stagedFielsaddress, "r");
    FILE* oldallFilesptr=fopen(oldAllFilesaddress, "r");
    char stagedfile[MAX_PATH];
    while(fscanf(stagedFilesptr, "%s%s%s", subPath0, subType0, subModified0)==3) {
        if(strcmp(subType0, "d")==0) continue;
        countStagedFiles++;
        while(fscanf(oldallFilesptr, "%s%s%s", subPath1, subType1, subModified1)==3) {
            if(strcmp(subPath0, subPath1)==0) {
                if(strcmp(subModified0, subModified1)==0) {
                    countUnmodifiedFiles++;
                }
            }
        }
    }
    if(countStagedFiles==countUnmodifiedFiles) {
        printf("there isn't any modified or new file in staging area to commit\n");
        return 0;
    }   
    fclose(oldallFilesptr);
    rewind(stagedFilesptr);
    FILE* newAllFilesptr=fopen(newAllFilesaddress, "r");
    while(fscanf(stagedFilesptr, "%s%s%s", subPath0, subType0, subModified0)==3) {
        if(strcmp(subType0, "d")==0) continue;
        while(fscanf(newAllFilesptr, "%s%s%s", subPath1, subType1, subModified1)==3) {
            if(strcmp(subPath0, subPath1)==0) {
                if(strcmp(subModified0, subModified1)!=0) {
                    printf("not allowed to commit, you have recently modified files <%s> not staged since recent change\n", subPath0);
                    return 0;
                }
            }
        }
    }
    return 1;
}

int commitSetLER(char* shortcutName) {
    char directoryPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, directoryPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(directoryPath, repoPath);
        if(result!=NULL) {
            break;
        } 
    }
    fclose(reposfile);
    char commitsetMessagesaddress[MAX_PATH];
    strcpy(commitsetMessagesaddress, repoPath);
    strcat(commitsetMessagesaddress, "\\ngit\\info\\commitsetMessage.txt");
    FILE* commitsetMessptr=fopen(commitsetMessagesaddress, "r");
    char tempShortcut[100];
    char tempMessage[100];
    int flag=0;
    while(fscanf(commitsetMessptr, "%99s", tempShortcut)==1) {
        fgets(tempMessage, sizeof(tempMessage), commitsetMessptr);
        size_t len1 = strlen(tempMessage);
        if (len1 > 0 && tempMessage[len1 - 1] == '\n') {
            tempMessage[len1 - 1] = '\0';
        }
        if(strcmp(tempShortcut,shortcutName)==0) {
            flag=1;
            break;
        }
    }
    if(flag==1) {
        if(tempMessage[0]==' ') {
            memmove(tempMessage, tempMessage + 1, strlen(tempMessage));
            tempMessage[strlen(tempMessage)] = '\0';
        }
        printf("shortcut <%s> is already assigned to <%s> message\n", shortcutName, tempMessage);
        return 0;
    }
    return 1;
}

int logLER(int argc, char* argv[]) {
    if(argc==2) return 7;
    if(strcmp(argv[2],"-branch")==0) {
        char directoryPath[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, directoryPath);
        char repoPath[MAX_PATH];
        FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
        while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
            size_t len = strlen(repoPath);
            if (len > 0 && repoPath[len - 1] == '\n') {
                repoPath[len - 1] = '\0';
            }
            char* result = strstr(directoryPath, repoPath);
            if(result!=NULL) {
                break;
            } 
        }
        fclose(reposfile);
        char branchesFilPath[MAX_PATH];
        strcpy(branchesFilPath, repoPath);
        strcat(branchesFilPath, "\\ngit\\info\\branches.txt");
        FILE* branchesFileptr=fopen(branchesFilPath, "r");
        char branch[20];
        int flag=0;
        while(fscanf(branchesFileptr, "%s", branch)==1) {
            if(strcmp(branch, argv[3])==0) {
                flag=1;
                return 2;
            }
        }
        if(flag==0) {
            printf("branch <%s> does not exist", argv[3]);
            return 0;
        }
    }
    else if(strcmp(argv[2],"-n")==0) return 1;
    else if(strcmp(argv[2],"-author")==0) return 3;
    else if(strcmp(argv[2],"-since")==0) return 4;
    else if(strcmp(argv[2],"-before")==0) return 5;
    else if(strcmp(argv[2],"-search")==0) return 6;
}
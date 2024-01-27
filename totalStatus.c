#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void totalStatus() {
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

    char newAlladdress[MAX_PATH];
    char oldAlladdress[MAX_PATH];
    char stagedFilesaddress[MAX_PATH];
    strcpy(newAlladdress, repoPath);
    strcat(newAlladdress, "\\ngit\\info\\contents\\newAll.txt");
    strcpy(oldAlladdress, repoPath);
    strcat(oldAlladdress, "\\ngit\\info\\contents\\oldAll.txt");
    strcpy(stagedFilesaddress, repoPath);
    strcat(stagedFilesaddress, "\\ngit\\info\\stagedfiles.txt");
    FILE* newAllptr=fopen(newAlladdress, "r");
    FILE* oldAllptr=fopen(oldAlladdress, "r");
    FILE* stagedFilesptr=fopen(stagedFilesaddress, "r");
    char subPath0[MAX_PATH];
    char subPath1[MAX_PATH];
    char subPath2[MAX_PATH];
    char subType0[5];
    char subType1[5];
    char subType2[5];
    char subModified0[30];
    char subModified1[30];
    char subModified2[30];
    int exists_innew=0;
    int exists_inold=0;
    int modif_state=0;
    while(fscanf(stagedFilesptr, "%s%s%s", subPath0, subType0, subModified0)==3) {
        if(strcmp(subType0, "f")!=0) continue;
        while(fscanf(newAllptr, "%s%s%s", subPath1, subType1, subModified1)==3) {
            if(strcmp(subPath0, subPath1)==0) {
                exists_innew=1;
                if(strcmp(subModified0, subModified1)!=0) {
                    modif_state=1;
                }
                else {
                    modif_state=3;
                }
                while(fscanf(oldAllptr, "%s%s%s", subPath2, subType2, subModified2)==3) {
                    if(strcmp(subPath0, subPath2)==0) {
                        exists_inold=1;
                        if(strcmp(subModified0,subModified2)==0 && strcmp(subModified0, subModified1)==0){
                            modif_state=0;
                        }
                        else if(strcmp(subModified0,subModified2)!=0 && strcmp(subModified0, subModified1)==0){
                            modif_state=2;
                        }
                        break;
                    }
                }
                break;
            }
        }
        if(exists_innew==0) {
            printf("%s -D\n", subPath0);
        }
        else if(modif_state==1 && exists_inold==1) {
            printf("%s -M\n", subPath0);
        }
        else if(modif_state==3 && exists_inold==0) {
            printf("%s +A\n", subPath0);
        }
        else if(modif_state==1 && exists_inold==0) {
            printf("%s -A\n", subPath0);
        }
        else if(modif_state==2) {
            printf("%s +M\n", subPath0);
        }
        else if(modif_state==0) {
            int flag=0;
            char begstagedfilesaddress[MAX_PATH];
            strcpy(begstagedfilesaddress, repoPath);
            strcat(begstagedfilesaddress, "\\ngit\\info\\begstagedfiles.txt");
            FILE* begStagedptr=fopen(begstagedfilesaddress, "r");
            while(fscanf(begStagedptr,"%s%s%s", subPath1, subType1, subModified1)==3) {
                if(strcmp(subPath0, subPath1)==0) {
                    printf("%s -N\n", subPath0);
                    flag=1;
                    break;
                }
            }
            fclose(begStagedptr);
            if(flag==0) {
                printf("%s +A\n", subPath0);
            }    
        }
        exists_innew=0;
        exists_inold=0;
        modif_state=0;
        rewind(newAllptr);
        rewind(oldAllptr);
    }
    fclose(newAllptr);
    fclose(oldAllptr);
    fclose(stagedFilesptr);
}
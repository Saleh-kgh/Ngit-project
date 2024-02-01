#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

int static firstAdd=0;

int addtoStage(char argv[]) {
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
    char absolouteRepoPath[MAX_PATH]; strcpy(absolouteRepoPath, repoPath);
    if(firstAdd==0) {
        char lastStagedPath[MAX_PATH]; strcpy(lastStagedPath, repoPath); strcat(lastStagedPath, "\\ngit\\info\\lastStaged.txt");
        char lastStagedaddPath[MAX_PATH]; strcpy(lastStagedaddPath, repoPath); strcat(lastStagedaddPath, "\\ngit\\info\\lastStagedadd.txt");
        FILE* lastStagedptr=fopen(lastStagedPath, "r"); FILE* lastStagedaddptr=fopen(lastStagedaddPath, "w"); 
        fprintf(lastStagedaddptr, "%s\\%s\n", filePath, argv);
        char tempLastStaged[MAX_PATH];
        while(fscanf(lastStagedptr, "%s", tempLastStaged)==1) {
            fprintf(lastStagedaddptr, "%s\n", tempLastStaged);
        }
        fclose(lastStagedptr);
        fclose(lastStagedaddptr);
        SetFileAttributes(lastStagedPath, FILE_ATTRIBUTE_NORMAL);
        DeleteFile(lastStagedPath);                                  
        rename(lastStagedaddPath, lastStagedPath);
        firstAdd=1;
    }
    
    char repositoryPath[MAX_PATH];
    strcpy(repositoryPath, filePath);
    char repoPathcopy2[MAX_PATH];
    strcpy(repoPathcopy2, repoPath);
    char stagedfileaddress[MAX_PATH];
    strcpy(stagedfileaddress, repoPath);
    strcat(stagedfileaddress, "\\ngit\\info\\stagedfiles.txt");
    char newstagedfileaddress[MAX_PATH];
    strcpy(newstagedfileaddress, repoPath);
    strcat(newstagedfileaddress, "\\ngit\\info\\newstagedfiles.txt");
    char repoPathcopy[MAX_PATH];
    strcpy(repoPathcopy, filePath);
    char filePathcopy[MAX_PATH];
    strcpy(filePathcopy, repoPath);
    strcat(filePath, "\\");
    strcat(filePath, argv);
    FILE* isfile=fopen(filePath, "r"); 
    DIR* isDir=opendir(filePath);       
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
    char repoPathcopy3[MAX_PATH];
    strcpy(repoPathcopy3, filePathcopy);
    strcat(repoPathcopy2, "\\ngit\\info\\contents\\newAll.txt");
    FILE* allNewptr=fopen(repoPathcopy2, "r");
    FILE* stagedfilesptr=fopen(stagedfileaddress, "a");
    FILE* stagedfilesread=fopen(stagedfileaddress, "r");
    if(isfile==NULL && isDir!=NULL) {
        for(int i=0; i<idx; i++) {
            strcat(repoPath, "\\");               
            strcat(repoPath, piecesofFilepath[i]); 
            strcat(repoPathcopy3, "\\");               
            strcat(repoPathcopy3, piecesofFilepath[i]);       
            DIR* dirptr=opendir(repoPath);
            if(dirptr==NULL) {
                rewind(allNewptr);
                CreateDirectory(repoPath, NULL);                      
                char dirPath[MAX_PATH];
                char type[5];
                char dirModification[30];
                while(fscanf(allNewptr, "%s%s%s", dirPath, type, dirModification)==3) {
                    if(strcmp(dirPath, repoPathcopy3)==0) {
                       fprintf(stagedfilesptr,"%s d %s\n", repoPathcopy3, dirModification);
                       rewind(allNewptr); 
                       break;
                    }
                }
            }    
                      
        }
        fclose(stagedfilesptr);
        rewind(allNewptr);
        fclose(stagedfilesread);
        strcat(repoPathcopy3, "\\");
        char subPath[MAX_PATH];
        char subType[5];
        char subModified[30];
        int round=0;
        while(fscanf(allNewptr,"%s%s%s", subPath, subType, subModified)==3) {
            if(strstr(subPath, repoPathcopy3)!=NULL && strcmp(subType, "f")==0) {
                char *match = strstr(subPath, repositoryPath);
                memmove(match, match + strlen(repositoryPath), strlen(match + strlen(repositoryPath)) + 1);
                addtoStage(subPath);           
            }
        }  
    }
    else {
        for(int i=0; i<idx-1; i++) {
            strcat(repoPath, "\\");               
            strcat(repoPath, piecesofFilepath[i]);
            strcat(repoPathcopy3, "\\");               
            strcat(repoPathcopy3, piecesofFilepath[i]);
            DIR* dirptr=opendir(repoPath);
            if(dirptr==NULL) {
                CreateDirectory(repoPath, NULL);
                char dirPath[MAX_PATH];
                char type[5];
                char dirModification[30];
                rewind(allNewptr);
                while(fscanf(allNewptr, "%s%s%s", dirPath, type, dirModification)==3) {
                    if(strcmp(dirPath, repoPathcopy3)==0) {
                       fprintf(stagedfilesptr,"%s d %s\n", repoPathcopy3, dirModification);
                       rewind(allNewptr); 
                       break;
                    }
                }
            }            
        }
        strcat(repoPath, "\\");
        strcat(repoPath, piecesofFilepath[idx-1]);
        strcat(repoPathcopy3, "\\");               
        strcat(repoPathcopy3, piecesofFilepath[idx-1]);
        char subPath0[MAX_PATH];
        char subType0[5];
        char subModified0[30];
        char subPath1[MAX_PATH];
        char subType1[5];
        char subModified1[30];
        int flag1=0;
        int flag2=0;
        rewind(allNewptr);
        rewind(stagedfilesread);
        while(fscanf(allNewptr,"%s %s %s", subPath0, subType0, subModified0)==3) {
            if(strcmp(subPath0, repoPathcopy3)==0) {
                while(fscanf(stagedfilesread,"%s %s %s", subPath1, subType1, subModified1)==3) {
                    if(strcmp(subPath1, repoPathcopy3)==0) {
                        flag1=1;
                        if(strcmp(subModified0, subModified1)==0) return 0;
                        break;
                    }
                }
                flag2=1;
                break;
            }
        }
        rewind(stagedfilesread);
        if(flag2==0) {
            while(fscanf(stagedfilesread,"%s %s %s", subPath1, subType1, subModified1)==3) {
                if(strcmp(subPath1, repoPathcopy3)==0) {
                    flag1=1;
                    break;
                }
            }
        }
        fclose(allNewptr);
        if(flag2==1 || flag1==0) {
            strcat(repoPathcopy, "\\copyfile.bat");
            FILE *batchFile=fopen(repoPathcopy, "w");
            fprintf(batchFile, "@echo off\n");
            fprintf(batchFile, "set \"sourceFile=%s\"\n", repoPathcopy3);
            fprintf(batchFile, "set \"destinationFile=%s\"\n", repoPath);
            fprintf(batchFile, ")\n");
            fprintf(batchFile, "type \"%%sourceFile%%\" > \"%%destinationFile%%\"\n");
            fprintf(batchFile, "exit /b 0\n");
            fclose(batchFile);
            system("copyfile.bat");
            remove(repoPathcopy);
        }
        if(flag1==1 && flag2==1) {
            FILE* newStagedFilesptr=fopen(newstagedfileaddress, "w");
            rewind(stagedfilesread);
            while(fscanf(stagedfilesread,"%s %s %s", subPath1, subType1, subModified1)==3) {
                if(strcmp(subPath1, repoPathcopy3)==0) {
                    fprintf(newStagedFilesptr,"%s f %s\n", repoPathcopy3, subModified0);
                }
                else {
                    fprintf(newStagedFilesptr,"%s %s %s\n", subPath1, subType1, subModified1);
                }
            }
            rewind(stagedfilesread);
            rewind(newStagedFilesptr);
            fclose(stagedfilesread);
            fclose(newStagedFilesptr);
            fclose(stagedfilesptr);
            SetFileAttributes(stagedfileaddress, FILE_ATTRIBUTE_NORMAL);
            DeleteFile(stagedfileaddress);                                  
            rename(newstagedfileaddress, stagedfileaddress);
        }
        else if(flag2==1 && flag1==0){
            stagedfilesptr=fopen(stagedfileaddress, "a");
            fprintf(stagedfilesptr,"%s f %s\n", repoPathcopy3, subModified0);
            fclose(stagedfilesptr);
        }
        else if(flag2==0 && flag1==1) {
            FILE* newStagedFilesptr=fopen(newstagedfileaddress, "w");
            rewind(stagedfilesread);
            while(fscanf(stagedfilesread,"%s%s%s", subPath1, subType1, subModified1)==3) {
                if(strcmp(subPath1, repoPathcopy3)==0) {
                    SetFileAttributes(repoPath, FILE_ATTRIBUTE_NORMAL);
                    DeleteFile(repoPath);
                    char removedFilesPath[MAX_PATH]; sprintf(removedFilesPath, "%s\\ngit\\info\\removedFiles.txt", absolouteRepoPath);
                    FILE* removedFilesptr=fopen(removedFilesPath, "a"); fprintf(removedFilesptr, "%s %s %s\n", subPath1, subType1, subModified1);
                    fclose(removedFilesptr);
                }
                else {
                    fprintf(newStagedFilesptr,"%s %s %s\n", subPath1, subType1, subModified1);
                }
            }
            rewind(stagedfilesread);
            rewind(newStagedFilesptr);
            fclose(stagedfilesread);
            fclose(newStagedFilesptr);
            fclose(stagedfilesptr);
            SetFileAttributes(stagedfileaddress, FILE_ATTRIBUTE_NORMAL);
            DeleteFile(stagedfileaddress);                                  
            rename(newstagedfileaddress, stagedfileaddress);
        }
    }   
    fclose(isfile);
}

void stageDepth(int depth) {
    char currentpath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentpath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt", "r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentpath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    char stagedfilesaddress[MAX_PATH];
    strcpy(stagedfilesaddress, repoPath);
    strcat(stagedfilesaddress, "\\ngit\\info\\stagedfiles.txt");
    char maxDepthaddress[MAX_PATH];
    strcpy(maxDepthaddress, repoPath);
    strcat(maxDepthaddress, "\\ngit\\info\\maxDepth.txt");
    FILE* maxDepthfile=fopen(maxDepthaddress, "r");
    int maxDepth=0;
    fscanf(maxDepthfile, "%d", &maxDepth);
    fclose(maxDepthfile);
    if(depth>=maxDepth) depth=maxDepth;
    char contentsfileaddrress[MAX_PATH];
    strcpy(contentsfileaddrress, repoPath);
    strcat(contentsfileaddrress, "\\ngit\\info\\contents");
    char oldAlladdress[MAX_PATH];
    strcpy(oldAlladdress, repoPath);
    strcat(oldAlladdress, "\\ngit\\info\\contents\\oldAll.txt");
    char contentsfileaddrresscopy[MAX_PATH];
    strcpy(contentsfileaddrresscopy, contentsfileaddrress);    
    for(int i=0; i<=depth; i++) {
        strcpy(contentsfileaddrress, contentsfileaddrresscopy);
        sprintf(contentsfileaddrress, "%s\\%d", contentsfileaddrress, i);
        char newDirsaddress[MAX_PATH];
        char newfilesaddress[MAX_PATH];
        sprintf(newDirsaddress, "%s\\newDirs.txt", contentsfileaddrress);
        sprintf(newfilesaddress, "%s\\newfiles.txt", contentsfileaddrress);
        char existingdirectory[MAX_PATH];
        char stagedfile[MAX_PATH];
        int flag1=0;
        int flag2=0;
        int flag3=0;
        char directoryPath[MAX_PATH];
        char dirType[5];
        char dirModification[30];
        char olddirectoryPath[MAX_PATH];
        char olddirType[5];
        char olddirModification[30];
        FILE* newDirsfile=fopen(newDirsaddress, "r");
        FILE* stagedfilesptr=fopen(stagedfilesaddress, "r");
        FILE* oldAllptr=fopen(oldAlladdress, "r");
        while(fgets(existingdirectory, sizeof(existingdirectory), newDirsfile) != NULL) {
            size_t len = strlen(existingdirectory);
            if (len > 0 && existingdirectory[len - 1] == '\n') {
                existingdirectory[len - 1] = '\0';
            }
            printf("%s ", existingdirectory);   
            while(fscanf(stagedfilesptr, "%s%s%s", directoryPath, dirType, dirModification)==3) {  
                if(strcmp(existingdirectory, directoryPath)==0) {
                    while(fscanf(oldAllptr, "%s%s%s", olddirectoryPath, olddirType, olddirModification)==3) {
                        if(strcmp(existingdirectory, olddirectoryPath)==0) { 
                            if(strcmp(olddirModification, dirModification)!=0) {
                                printf("1\n");
                                flag1=1;
                            }
                            else {
                                printf("0\n");
                            }
                            flag2=1;
                            break;
                        }
                    }
                    flag3=1;
                    break;
                } 
            }
            if(flag1==0 && flag2==0 && flag3==1) {
                printf("1\n");
            }
            if(flag1==0 && flag2==0 && flag3==0) {
                printf("0\n");
            }
            flag1=0;
            flag2=0;
            flag3=0;
            rewind(stagedfilesptr);
            rewind(oldAllptr);
        }
        fclose(newDirsfile);
        char existingfile[MAX_PATH];
        FILE* newfilesptr=fopen(newfilesaddress, "r");
        while(fgets(existingfile, sizeof(existingfile), newfilesptr) != NULL) {
            size_t len = strlen(existingfile);
            if (len > 0 && existingfile[len - 1] == '\n') {
                existingfile[len - 1] = '\0';
            }
            printf("%s ", existingfile);   
            while(fscanf(stagedfilesptr, "%s%s%s", directoryPath, dirType, dirModification)==3) {  
                if(strcmp(existingfile, directoryPath)==0) {
                    while(fscanf(oldAllptr, "%s%s%s", olddirectoryPath, olddirType, olddirModification)==3) {
                        if(strcmp(existingfile, olddirectoryPath)==0) {
                            if(strcmp(olddirModification, dirModification)!=0) {
                                printf("1\n");
                                flag1=1;
                            }
                            else {
                                printf("0\n");
                            }
                            flag2=1;
                            break;
                        }
                    }
                    flag3=1;
                    break;
                } 
            }
            if(flag1==0 && flag2==0 && flag3==1) {
                printf("1\n");
            }
            if(flag1==0 && flag2==0 && flag3==0) {
                printf("0\n");
            }
            flag1=0;
            flag2=0;
            flag3=0;
            rewind(stagedfilesptr);
            rewind(oldAllptr);
        }
        fclose(newfilesptr);
    }
}
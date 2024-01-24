#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <windows.h>

void listDirectories(int isOld) {
    int dirDepth=0;
    char outputPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,outputPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(outputPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    strcpy(outputPath, repoPath);
    outputPath[strcspn(outputPath, "\n")] = '\0';
    strcat(outputPath, "\\ngit\\info\\contents");
    char outputfilepath[MAX_PATH];
    char extralstpath[MAX_PATH];
    while(1) {
        sprintf(outputfilepath,"%s\\%d", outputPath, dirDepth);
        CreateDirectory(outputfilepath, NULL);
        strcpy(extralstpath, outputfilepath);
        switch (isOld) {
            case 1 :
                strcat(outputfilepath, "\\oldDirs.txt");
                break;
            case 0 :
                strcat(outputfilepath, "\\newDirs.txt");
                break;
        }
        FILE* outputfile = fopen(outputfilepath, "w");
        struct dirent *entry;
        int subDirsCount=0;
        if(dirDepth==0) {
            char dirPath[MAX_PATH];
            strcpy(dirPath, repoPath);
            dirPath[strcspn(dirPath, "\n")] = '\0';
            DIR* dirptr = opendir(dirPath);
            while ((entry = readdir(dirptr)) != NULL) {
                if (entry->d_type == DT_DIR) {
                    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, "ngit") != 0) {
                        fprintf(outputfile, "%s\\%s\n", dirPath, entry->d_name);
                        subDirsCount++;
                    }
                }
            }
            closedir(dirptr);
        }
        else {
            char dirPath[MAX_PATH];
            char Dirsfile[MAX_PATH];
            sprintf(Dirsfile,"%s\\%d", outputPath, dirDepth-1);
            switch (isOld) {
                case 1 :
                    strcat(Dirsfile, "\\oldDirs.txt");
                    break;
                case 0 :
                    strcat(Dirsfile, "\\newDirs.txt");
                    break;
            }
            FILE* dirsfileptr=fopen(Dirsfile, "r");
            while(fgets(dirPath, sizeof(dirPath), dirsfileptr)) {
                size_t len = strlen(repoPath);
                if (len > 0 && repoPath[len - 1] == '\n') {
                    repoPath[len - 1] = '\0';
                }
                dirPath[strcspn(dirPath, "\n")] = '\0';
                DIR* dirptr = opendir(dirPath);
                while ((entry = readdir(dirptr)) != NULL) {
                    if (entry->d_type == DT_DIR) {
                        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, "ngit") != 0) {
                            fprintf(outputfile, "%s\\%s\n", dirPath, entry->d_name);
                            subDirsCount++;
                        }
                    }
                }
                closedir(dirptr);
            }
            fclose(dirsfileptr);           
        }
        fclose(outputfile);
        dirDepth++;
        if(subDirsCount<1) {
            break; 
        }
    } 
    repoPath[strcspn(repoPath, "\n")] = '\0';
    strcat(repoPath, "\\ngit\\info\\maxDepth.txt");
    FILE* maxDepthfile=fopen(repoPath, "w");
    fprintf(maxDepthfile, "%d", dirDepth-1);
    fclose(maxDepthfile);  
}

void listFiles(int isOld) {
    int dirDepth=0;
    char outputPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,outputPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(outputPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    int maxDepth=0;
    char maxDepthaddress[MAX_PATH];
    repoPath[strcspn(repoPath, "\n")] = '\0';
    sprintf(maxDepthaddress, "%s\\ngit\\info\\maxDepth.txt", repoPath);
    FILE* maxDepthfile=fopen(maxDepthaddress, "r");
    fscanf(maxDepthfile, "%d", &maxDepth);
    fclose(maxDepthfile);
    strcpy(outputPath, repoPath);
    outputPath[strcspn(outputPath, "\n")] = '\0';
    strcat(outputPath, "\\ngit\\info\\contents");
    char outputfilepath[MAX_PATH];
    char extralstpath[MAX_PATH];
    while(1) {
        sprintf(outputfilepath,"%s\\%d", outputPath, dirDepth);
        //CreateDirectory(outputfilepath, NULL);
        //strcpy(extralstpath, outputfilepath);
        switch (isOld) {
            case 1 :
                strcat(outputfilepath, "\\oldfiles.txt");
                break;
            case 0 :
                strcat(outputfilepath, "\\newfiles.txt");
                break;
        }
        FILE* outputfile = fopen(outputfilepath, "w");
        struct dirent *entry;
        int subDirsCount=0;
        if(dirDepth==0) {
            char dirPath[MAX_PATH];
            strcpy(dirPath, repoPath);
            dirPath[strcspn(dirPath, "\n")] = '\0';
            DIR* dirptr = opendir(dirPath);
            while ((entry = readdir(dirptr)) != NULL) {
                if (entry->d_type == DT_REG) {
                    fprintf(outputfile, "%s\\%s\n", dirPath, entry->d_name);
                }
            }
            closedir(dirptr);
        }
        else {
            char dirPath[MAX_PATH];
            char Dirsfile[MAX_PATH];
            sprintf(Dirsfile,"%s\\%d", outputPath, dirDepth-1);
            switch (isOld) {
                case 1 :
                    strcat(Dirsfile, "\\oldDirs.txt");
                    break;
                case 0 :
                    strcat(Dirsfile, "\\newDirs.txt");
                    break;
            }
            FILE* dirsfileptr=fopen(Dirsfile, "r");
            while(fgets(dirPath, sizeof(dirPath), dirsfileptr)) {
                size_t len = strlen(repoPath);
                if (len > 0 && repoPath[len - 1] == '\n') {
                    repoPath[len - 1] = '\0';
                }
                dirPath[strcspn(dirPath, "\n")] = '\0';
                DIR* dirptr = opendir(dirPath);
                while ((entry = readdir(dirptr)) != NULL) {
                    if (entry->d_type == DT_REG) {
                        fprintf(outputfile, "%s\\%s\n", dirPath, entry->d_name);
                    }
                }
                closedir(dirptr);
            }
            fclose(dirsfileptr);           
        }
        fclose(outputfile);
        dirDepth++;
        if(maxDepth+1==dirDepth) {
            break; 
        }
    }   
}


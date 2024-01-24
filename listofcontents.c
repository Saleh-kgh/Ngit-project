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
}


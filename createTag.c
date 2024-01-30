#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

void createTag(char* tagName, char* tagMessage, char* commitHash, int state) {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);
    char localuserPath[MAX_PATH]; sprintf(localuserPath, "%s\\ngit\\info\\localuser.txt", repoPath); char author[30]; char authorEmail[30];
    FILE* localuserptr=fopen(localuserPath, "r"); fgets(author, sizeof(author), localuserptr); fgets(authorEmail, sizeof(authorEmail), localuserptr); fclose(localuserptr);
    author[strcspn(author, "\n")] = '\0'; authorEmail[strcspn(authorEmail, "\n")] = '\0';
    char curCommitPath[MAX_PATH]; sprintf(curCommitPath, "%s\\ngit\\info\\curCommithash.txt", repoPath); char curCommithash[9];
    FILE* curCommitptr=fopen(curCommitPath, "r"); fscanf(curCommitptr, "%s", curCommithash); strcpy(commitHash, curCommithash); fclose(curCommitptr);
    if(state==3 && state==4 && state==6 && state==7) {
        int flag=1;
        char allCommitsPath[MAX_PATH]; sprintf(allCommitsPath, "%s\\ngit\\info\\allCommits.txt", repoPath);
        FILE* allCommitsptr=fopen(allCommitsPath, "r"); char commitData[7][40]; char line[100];
        while (fgets(line, sizeof(line), allCommitsptr)) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(commitData[0], line);
            for (int i = 1; i < 7; i++) {
                if (!fgets(line, sizeof(line), allCommitsptr)) {
                    printf("Error: Unexpected end of file\n");
                    return;
                }
                line[strcspn(line, "\n")] = '\0';
                strcpy(commitData[i], line);
            }
            if(strcmp(commitData[0], commitHash)==0) {
                strcpy(author, commitData[4]); strcpy(authorEmail, commitData[5]);
                flag=1;
                break;
            }
        }
        if(flag==0) {
            printf("the commit hash <%s> in invalid\n", commitHash);
            return;
        }
    }
    char date[40];
    SYSTEMTIME st;
    GetLocalTime(&st);
    const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    sprintf(date, "%s %s %02d %02d:%02d:%02d %04d\n", daysOfWeek[st.wDayOfWeek], months[st.wMonth - 1], st.wDay, st.wHour, st.wMinute, st.wSecond, st.wYear);
    int reassignFlag=0;
    char allTagsPath[MAX_PATH]; sprintf(allTagsPath, "%s\\ngit\\info\\allTags.txt", repoPath);
    FILE* allTagsptr=fopen(allTagsPath, "r");
    if(allTagsptr==NULL && state>4) {
        printf("tag <%s> does not exist\n", tagName);
        fclose(allTagsptr);
        return;
    }
    else if(allTagsptr==NULL && state<5) {
        fclose(allTagsptr);
        allTagsptr=fopen(allTagsPath, "w");
        fprintf(allTagsptr, "%s\n%s\n%s\n%s\n%s\n%s\n", tagName, commitHash, author, authorEmail, date, tagMessage);
        fclose(allTagsptr);
        return;
    }
    else if(allTagsPath!=NULL) {
        char line[40]; char tagData[6][40];
        while (fgets(line, sizeof(line), allTagsptr)) {
            line[strcspn(line, "\n")] = '\0';
            strcpy(tagData[0], line);
            for (int i = 1; i < 7; i++) {
                if (!fgets(line, sizeof(line), allTagsptr)) {
                    printf("Error: Unexpected end of file\n");
                    return;
                }
                line[strcspn(line, "\n")] = '\0';
                strcpy(tagData[i], line);
            }
            if(strcmp(tagData[0], tagName)==0) {
                if(state>4) {
                    reassignFlag=1;
                    break;
                }
                else {
                    printf("tag <%s> is already assigned to commit with hash <%s>\n", tagName, tagData[1]);
                    fclose(allTagsptr);
                    return;
                }
            }
        }
        if(state>4 && reassignFlag==0) {
            printf("tag <%s> does not exist and can't be reassigned\n", tagName, tagData[1]);
            fclose(allTagsptr);
            return;
        }
        if(state < 5) {
            fclose(allTagsptr); allTagsptr=fopen(allTagsPath, "a");
            fprintf(allTagsptr, "%s\n%s\n%s\n%s\n%s\n%s\n", tagName, commitHash, author, authorEmail, date, tagMessage);
            fclose(allTagsptr);
            return;
        }   
        if(state>4 && reassignFlag==1) {
            char newallTagsPath[MAX_PATH]; sprintf(newallTagsPath, "%s\\ngit\\info\\newallTags.txt", repoPath);
            FILE* newallTagsptr=fopen(newallTagsPath, "w");
            char line[40]; char tagData[6][40];
            while (fgets(line, sizeof(line), allTagsptr)) {
                line[strcspn(line, "\n")] = '\0';
                strcpy(tagData[0], line);
                for (int i = 1; i < 7; i++) {
                    if (!fgets(line, sizeof(line), allTagsptr)) {
                        printf("Error: Unexpected end of file\n");
                        return;
                    }
                    line[strcspn(line, "\n")] = '\0';
                    strcpy(tagData[i], line);
                }
                if(strcmp(tagData[0], tagName)==0) {
                    fprintf(allTagsptr, "%s\n%s\n%s\n%s\n%s\n%s\n", tagName, commitHash, author, authorEmail, date, tagMessage);
                }
                else {
                    fprintf(allTagsptr, "%s\n%s\n%s\n%s\n%s\n%s\n", tagData[0], tagData[1], tagData[2], tagData[3], tagData[4], tagData[5]);
                }
            }
            fclose(newallTagsptr); fclose(allTagsptr);
            SetFileAttributes(allTagsPath, FILE_ATTRIBUTE_NORMAL);
            remove(allTagsPath); rename(newallTagsPath, allTagsPath);
            return;
        }
    }
}

void tagIDShow (char* tagName) {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);

    char allTagsPath[MAX_PATH]; sprintf(allTagsPath, "%s\\ngit\\info\\allTags.txt", repoPath);
    FILE* allTagsptr=fopen(allTagsPath, "r");
    char line[40]; char tagData[6][40];
    while (fgets(line, sizeof(line), allTagsptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(tagData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allTagsptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(tagData[i], line);
        }
        if(strcmp(tagData[0], tagName)==0) {
            printf("Tag name: %s\nCommit hash: %s\nAuthor: %s <%s>\nDate: %s\nMessage: %s\n", tagName, tagData[1], tagData[2], tagData[3], tagData[4], tagData[5]);
            fclose(allTagsptr);
            return;
        }
    }
    printf("tag <%s> was not found\n", tagName);
    fclose(allTagsptr);
    return;
}

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void tagsListShow() {
    char currentPath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,currentPath);
    char repoPath[MAX_PATH];
    FILE* reposfile=fopen("d:\\ANGP\\ngit-project\\repositories.txt","r");
    while(fgets(repoPath, sizeof(repoPath), reposfile)!= NULL) {
        size_t len = strlen(repoPath);
        if (len > 0 && repoPath[len - 1] == '\n') {
            repoPath[len - 1] = '\0';
        }
        char* result = strstr(currentPath, repoPath);
        if(result!=NULL) break;
    }
    fclose(reposfile);

    char allTagsPath[MAX_PATH]; sprintf(allTagsPath, "%s\\ngit\\info\\allTags.txt", repoPath);
    FILE* allTagsptr=fopen(allTagsPath, "r");
    char line[40]; char tagData[6][40]; char tagNames[50][15]; int idx=0;
    while (fgets(line, sizeof(line), allTagsptr)) {
        line[strcspn(line, "\n")] = '\0';
        strcpy(tagData[0], line);
        for (int i = 1; i < 7; i++) {
            if (!fgets(line, sizeof(line), allTagsptr)) {
                printf("Error: Unexpected end of file\n");
                return;
            }
            line[strcspn(line, "\n")] = '\0';
            strcpy(tagData[i], line);
        }
        strcpy(tagNames[idx], tagData[0]); idx++;
    }
    if(idx==0) {
        printf("there is no tag to list\n");
        return;
    }
    size_t numStrings = sizeof(tagNames) / sizeof(tagNames[0]);
    qsort(tagNames, numStrings, sizeof(tagNames[0]), compareStrings);
    printf("List of tags:\n");
    for (size_t i = 0; i < numStrings; ++i) {
        printf("%s\n", tagNames[i]);
    }
    return;
}
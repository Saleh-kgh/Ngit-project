#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int userInfo(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=4 && argc!=5) error_occured=1;
    if(argc==5) {
        if(strcmp(argv[2], "-global")!=0) error_occured=1;           
        if(strcmp(argv[3],"user.name")!=0  && strcmp(argv[3],"user.email")!=0) error_occured=1;  
    }
    if(argc==4) {
        if(strcmp(argv[2],"user.name")!=0 && strcmp(argv[2],"user.email")!=0) error_occured=1;
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}

int aliasCommand(int argc, char* argv[]) {
    int error_occured=0;
    char alias_spell[6]="alais.";
    if(argc!=4 && argc!=5) error_occured=1;
    if(argc==5) {
        if(strcmp(argv[2], "-global")!=0) error_occured=1;      
        for(int i=0; i<6; i++) {
            if(argv[3][i]!=alias_spell[i]) {
                error_occured=1;
                break;
            }
        }       
    }
    if(argc==4) {
        for(int i=0; i<6; i++) {
            if(argv[2][i]!=alias_spell[i]) {
                error_occured=1;
                break;
            }
        } 
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}

int initCount(int argc, char* argv[]) {
    if(argc!=2) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}

int addCommand(int argc, char* argv[]) {
    int error_occured=0;
    if(argc<3) error_occured=1;
    if(argc==3 && strcmp(argv[2], "-redo")==0) return 2;
    if(argc!=3 && (strcmp(argv[2], "-f")!=0 && strcmp(argv[2], "-n")!=0)) error_occured=1;
    if(strcmp(argv[2],"-n")==0 && argc!=4) error_occured=1;
    if(argc==3 && (strcmp(argv[2], "-f")==0 || strcmp(argv[2], "-n")==0)) error_occured=1;
    if(strcmp(argv[2],"-n")==0) {
        int length = strlen(argv[3]);
        for(int i=0; i<length; i++) {
            if(argv[3][i]<47 || argv[3][i]>57) {
                printf("Invalid command due to unacceptable depth number!");
                return 0;
            }
        }
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}

int statusCommand(int argc, char* argv[]) {
    if(argc!=2) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}

int commitCommand(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=4) error_occured=1;
    if(strcmp(argv[2], "-m")!=0) error_occured=1;
    if(strlen(argv[3])>75) {
        printf("commit message too long!");
        return 0;
    }
    if(argv[3][0]=='"' && argv[3][1]=='"') {
        printf("There is no comment to your commit!");
        return 0;
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words!");
        return 0;
    }
    return 1;
}
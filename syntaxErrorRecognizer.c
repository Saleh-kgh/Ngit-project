#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int userInfoSER(int argc, char* argv[]) {
    int error_occured=0;
    int returnValue=1;
    if(argc!=4 && argc!=5) error_occured=1;
    if(argc==5) {
        if(strcmp(argv[2], "-global")!=0) error_occured=1;           
        if(strcmp(argv[3],"user.name")!=0  && strcmp(argv[3],"user.email")!=0) error_occured=1;  
    }
    if(argc==4) {
        if(strcmp(argv[2],"user.name")!=0 && strcmp(argv[2],"user.email")!=0) error_occured=1;
        returnValue=2;
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words dash.");       
        return 0;
    }
    return returnValue;
}

int aliasSER(int argc, char* argv[]) {
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
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int initSER(int argc, char* argv[]) {
    if(argc!=2) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int addSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc<3) error_occured=1;
    if(argc==3 && strcmp(argv[2], "-redo")==0) return 2;
    if(argc!=3 && (strcmp(argv[2], "-f")!=0 && strcmp(argv[2], "-n")!=0)) error_occured=1;
    if(strcmp(argv[2],"-n")==0 && argc!=4) error_occured=1;
    if(argc==3 && (strcmp(argv[2], "-f")==0 || strcmp(argv[2], "-n")==0)) error_occured=1;
    if(strcmp(argv[2],"-n")==0) {
        int length = strlen(argv[3]);
        for(int i=0; i<length; i++) {
            if(argv[3][i]<48 || argv[3][i]>57) {
                printf("Invalid command due to unacceptable depth number.");
                return 0;
            }
        }
    }
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int resetSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc<3) error_occured=1;
    else if(argc==3 && strcmp(argv[2], "-f")==0) error_occured=1;
    else if(argc>3 && strcmp(argv[2], "-f")!=0) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int statusSER(int argc, char* argv[]) {
    if(argc!=2) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int commitSER(int argc, char* argv[]) {
    int error_occured=0;
    if(strcmp(argv[2], "-m")!=0 && strcmp(argv[2], "-s")!=0) error_occured=1;
    if(strlen(argv[3])>75) {
        printf("commit message too long.");
        return 0;
    }
    /*if(argv[3][0]==97 && argv[3][1]==97) {
        printf("There is no comment to your commit!");
        return 0;
    }*/
    if(argc==3 && error_occured==0) {
        printf("There is no comment to your commit.");
        return 0;
    }
    if(argc!=4) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    if(strcmp(argv[2], "-s")==0) return 2;
    return 1;
}

int setSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=6) error_occured=1;
    if(strcmp(argv[2], "-m")!=0) error_occured=1;
    if(strcmp(argv[4], "-s")!=0) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int replaceSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=6) error_occured=1;
    if(strcmp(argv[2], "-m")!=0) error_occured=1;
    if(strcmp(argv[4], "-s")!=0) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int removeSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=4) error_occured=1;
    if(strcmp(argv[2], "-s")!=0) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int logSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc==2) return 6;
    if(argc!=4 && argc!=2) error_occured=1;
    if(argc==4 && (strcmp(argv[2], "-n")!=0) && (strcmp(argv[2], "-branch")!=0) && (strcmp(argv[2], "-author")!=0) && (strcmp(argv[2], "-since")!=0) && (strcmp(argv[2], "-before")!=0) && (strcmp(argv[2], "-search")!=0))
        error_occured=1;
    
    if(strcmp(argv[2],"-n")==0) {
        int length = strlen(argv[3]);
        for(int i=0; i<length; i++) {
            if(argv[3][i]<48 || argv[3][i]>57) {
                printf("Invalid command due to unacceptable number.");
                return 0;
            }
        }
    }
    // code for invalid date of since and before
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    if(argc==2) return 6;
    if(strcmp(argv[2], "-n")==0) return 1;
    else if(strcmp(argv[2], "-branch")==0) return 2;
    else if(strcmp(argv[2], "-author")==0) return 3;
    else if(strcmp(argv[2], "-since")==0 || strcmp(argv[2], "-before")==0) return 4;
    else if(strcmp(argv[2], "-search")==0) return 5;
}

int branchSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc>3) error_occured=1;
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    if(argc==3) return 2; 
    return 1;
}

int checkoutSER(int argc, char* argv[]) {
    int error_occured=0;
    if(argc!=3) error_occured=1;
    char head[4]="HEAD";
    int i;
    for(i=0; i<4; i++) {
        if(head[i]!=argv[2][i])
            break;
    }
    if(i==4) {
        if(strlen(argv[2])==4)
            return 3;
    }
    if(strlen(argv[2])==8) {
        for(int i=0; i<8; i++) {
            if(argv[2][i]<48 || argv[2][i]>57) {
                return 1;
            }
        }
        return 2;
    }
    
    if(error_occured==1) {
        printf("Invalid command due to misspell or extra words.");
        return 0;
    }
    return 1;
}

int revertSER(int argc, char* argv[]) {
    if(argc==3) {
        if(strstr(argv[2], "HEAD-")!=NULL) {
            int len=strlen(argv[2]);
            for(int i=5; i<len; i++) {
                if(argv[2][i]<48 || argv[2][i]>57) return 0;
            }
        return 3;
        } 
        else return 1;
    }
    if(argc!=4) return 0;
    if(strcmp(argv[2], "-n")==0)  return 4;
    if(strstr(argv[3], "HEAD-")!=NULL) {
        int len=strlen(argv[3]);
        for(int i=5; i<len; i++) {
            if(argv[3][i]<48 || argv[3][i]>57) return 0;
        }
        return 5;
    }
    return 2;
}
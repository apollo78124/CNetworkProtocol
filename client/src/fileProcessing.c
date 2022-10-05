#include "fileProcessing.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>


void readFile(char *file_exps[]) {
    /**
    printf("Client: List of files to process received.\n");
    printf("Expressions received: \n");
    for(int index = 0; file_exps[index] != NULL && index < 19; ++index) {
        printf(file_exps[index]);
        printf("\n");
    }
    */

    char tempString1[] = "/root/Documents/ClientTesting/";
    //int result = checkForAsterisk(tempString1);
    char* tempStringArray1 = getListOfFilePathFromExpression(tempString1);
}

//return 3 when asterisk is in the fileName which is last token in the directory path
int checkForAsterisk(char tempString2[]) {
    char * token = strtok(tempString2, "/");
    char * tokenBefore;
    while (token != NULL) {
        tokenBefore = token;
        token=strtok(NULL, "/");
    }

    char *checker = strchr(tokenBefore, '*');

    if (checker != NULL) {
        return 1;
    } else {
        return 0;
    }
}

char** getListOfFilePathFromExpression(char tempString3[]) {
    DIR *tempDir;
    struct dirent *dir;
    tempDir = opendir(tempString3);
    if (tempDir) {
        while ((dir = readdir(tempDir)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(tempDir);
    }
    return NULL;
}

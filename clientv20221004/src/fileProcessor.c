//
// Created by davlee on 10/5/2022.
//
#include "fileProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void makeNewFile(char filePath[]) {
    FILE *fp;
    FILE *fptr;
    char buff[2555];
    int bufferLength = 2555;
    char buffer[bufferLength];
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filePath, "rw+");

    //Writing to File
    //fputs("This is testing for fputs...\n", fp);

    //Reading from file
    while(fgets(buffer, bufferLength, fp)) {
        printf("%s", buffer);
    }

    //Checks if file exists
    /**
    if ((fptr = fopen("C:\\program.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
     */

    fclose(fp);
    fclose(fptr);
}
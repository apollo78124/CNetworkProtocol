//
// Created by davlee on 10/5/2022.
//
#include "fileProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void makeNewFile(char filePath[]) {
    FILE *reader1;
    FILE *wiper1;
    char buff[2555];
    int bufferLength = 2555;
    char buffer[bufferLength];
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    reader1 = fopen(filePath, "r");
    wiper1 = fopen("D:/Test1/received.txt", "a+");

    //Writing to File
    //fputs("This is testing for fputs...\n", fp);

    //Reading from file
    while(fgets(buffer, bufferLength, reader1)) {
        printf("%s", buffer);
        fputs(buffer, wiper1);
    }

    //Checks if file exists
    /**
    if ((fptr = fopen("C:\\program.txt","r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
     */

    fclose(reader1);
}
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
    //char buff[2555];
    int bufferLength = 255;
    char buffer[bufferLength];
    //char * line = NULL;
    //size_t len = 0;
    //ssize_t read;

    reader1 = fopen(filePath, "r");
    wiper1 = fopen("/root/Documents/client/received.txt", "a+");
    //Writing to File
    //fputs("This is testing for fputs...\n", fp);
    if (reader1 != NULL && wiper1 != NULL) {
        while(fgets(buffer, bufferLength, reader1)) {
            printf("%s", buffer);
            fputs(buffer, wiper1);
        }
    }

    //Reading from file


    //Checks if file exists
    /**
    if ((fptr = fopen("C:\\program.txt","r")) == NULL) {
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    */

    fclose(reader1);
    fclose(wiper1);
}
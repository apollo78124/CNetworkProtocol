//
// Created by davlee on 10/5/2022.
//
#include "fileProcessor.h"

const char* fileSendSignal = "?FSRFSRFSRFSRFSR";
const char* streamingEndSignal = "?EOCEOCEOCEOCEOC";
const int bufferLength = 255;

void sendOneFile(int socket1, char filePath[], char fileName[], char bufferFromServer[]) {
    int valueRead;
    FILE *reader1;
    //Buffer used for sending
    char buffer1[bufferLength];
    memset(buffer1, 0, bufferLength);

    send(socket1, fileSendSignal, strlen(fileSendSignal), 0);

    printf("ClientV20221004: Sent File Upload Signal\n");
    memset(bufferFromServer, 0, 255);
    valueRead = read(socket1, bufferFromServer, 255);

    //If Server confirms file send request

    if (strcmp(bufferFromServer, "?FSRCFSRCFSRCFSRCFSRC") == 0) {
        //Send File Name to server
        send(socket1, fileName, strlen(fileName), 0);
        printf("ClientV20221004: File name %s sent\n", fileName);
        //Wait for Server Confirmation
        printf("ClientV20221004: Waiting for filename confirmation...\n");
        memset(bufferFromServer, 0, bufferLength);
        valueRead = read(socket1, bufferFromServer, 255);

        //If server confirms it received file name
        if (strcmp(bufferFromServer, "?FNCFNCFNCFNCFNC") == 0) {
            printf("ClientV20221004: File name confirmation received\n");

            //start streaming file contents to server
            reader1 = fopen(filePath, "r");
            printf("ClientV20221004: Started file reader. Started streaming...\n");
            int counter = 0;
            if (reader1 != NULL) {
                printf("ClientV20221004: Streaming started...\n");
                while(fgets(buffer1, bufferLength, reader1)) {
                    if (strlen(buffer1) < 1) {
                        printf("ClientV20221004: Warning: Sent empty string\n");
                    }
                    send(socket1, buffer1, bufferLength, 0);
                    counter++;
                    memset(buffer1, 0, bufferLength);
                }
                printf("ClientV20221004: Reached end of file. Streaming ending...\n");
            }
        }
        //Send stream end signal
        send(socket1, streamingEndSignal, strlen(streamingEndSignal), 0);
        printf("ClientV20221004: Sent Streaming stop signal\n");

        //Get confirmation from server that it closed its file writer
        memset(bufferFromServer, 0, 255);
        printf("ClientV20221004: Waiting for streaming end confirmation...\n");
        valueRead = read(socket1, bufferFromServer, 1024);
        printf("ClientV20221004: Server confirmed stream end\n");

        fclose(reader1);
        close(buffer1);
    }
}

void loopThroughStringArray(char tempString3[]) {
    char* fileExpressions11[] = {"/root/Documents/client/A Tale of Two Cities.txt", "/root/Documents/client/foo.txt"}, **fff;
    fff = fileExpressions11;
    while(*fff != "") {
        printf("%s\n", *fff++);
    }
}

char* getFileNameFromFilePath(char tempString4[]) {
    char *stringToTest = strdup(tempString4);
    char *token = strtok(stringToTest, "/");
    char *tokenBefore;
    while (token != NULL) {
        tokenBefore = token;
        token=strtok(NULL, "/");
    }
    close(stringToTest);
    return tokenBefore;
}
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#include "fileProcessor.h"

int main(int argc, char *argv[]) {
    FILE *reader1;
    //char buff[2555];
    int bufferLength = 255;
    char buffer1[bufferLength];

    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* fileSendSignal = "?FSRFSRFSRFSRFSR";
    char* streamingEndSignal = "?EOCEOCEOCEOCEOC";
    char* fileName = "A Tale of Two Cities.txt";
    char bufferFromServer[bufferLength];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
                "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((client_fd
                 = connect(sock, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    close(fileSendSignal);
    send(sock, fileSendSignal, strlen(fileSendSignal), 0);

    printf("ClientV20221004: Sent File Upload Signal\n");
    memset(bufferFromServer, 0, 255);
    valread = read(sock, bufferFromServer, 255);

    //If Server confirms file send request

    if (strcmp(bufferFromServer, "?FSRCFSRCFSRCFSRCFSRC") == 0) {
        //Send File Name to server
        send(sock, fileName, strlen(fileName), 0);
        printf("ClientV20221004: File name %s sent\n", fileName);
        //Wait for Server Confirmation
        printf("ClientV20221004: Waiting for filename confirmation...\n");
        memset(bufferFromServer, 0, 255);
        valread = read(sock, bufferFromServer, 255);

        //If server confirms it received file name
        if (strcmp(bufferFromServer, "?FNCFNCFNCFNCFNC") == 0) {
            printf("ClientV20221004: File name confirmation received\n");

            //start streaming file contents to server
            reader1 = fopen("/root/Documents/client/A Tale of Two Cities.txt", "r");
            printf("ClientV20221004: Started file reader. Started streaming...\n");
            int counter = 0;
            if (reader1 != NULL) {
                printf("ClientV20221004: Streaming started...\n");
                while(fgets(buffer1, bufferLength, reader1)) {
                    if (strlen(buffer1) < 1) {
                        printf("ClientV20221004: Warning: Sent empty string\n");
                    }
                    send(sock, buffer1, bufferLength, 0);
                    counter++;

                }
                printf("ClientV20221004: Reached end of file. Streaming ending...\n");
            }
        }
        //Send stream end signal
        send(sock, streamingEndSignal, strlen(streamingEndSignal), 0);
        printf("ClientV20221004: Sent Streaming stop signal\n");

        //Get confirmation from server that it closed its file writer
        memset(bufferFromServer, 0, 255);
        printf("ClientV20221004: Waiting for streaming end confirmation...\n");
        valread = read(sock, bufferFromServer, 1024);
        printf("ClientV20221004: Server confirmed stream end\n");
    }

    // closing the connected socket
    close(client_fd);
    printf("ClientV20221004: Socket closed\n");

    fclose(reader1);
    printf("ClientV20221004: File reader closed\n");
    return 0;
}



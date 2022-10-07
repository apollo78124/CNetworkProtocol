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
    char* fileName = "received.txt";
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
        //Wait for Server Confirmation
        memset(bufferFromServer, 0, 255);
        valread = read(sock, bufferFromServer, 255);
        //If server confirms it received file name
        if (strcmp(bufferFromServer, "?FNCFNCFNCFNCFNC") == 0) {
            //start streaming file contents to server
            send(sock, "mock file content", strlen("mock file content"), 0);
        }
        //Send stream end signal
        send(sock, streamingEndSignal, strlen(streamingEndSignal), 0);

        //Get confirmation from server that it closed its file writer
        memset(bufferFromServer, 0, 255);
        valread = read(sock, bufferFromServer, 1024);
    }

    // closing the connected socket
    close(client_fd);


    fclose(reader1);
    return 0;
}



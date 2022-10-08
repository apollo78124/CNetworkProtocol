#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "serverContext.h"
#define PORT 8080
int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char bufferFromClient[255];
    char* confirmFileTransferSignal = "?FSRCFSRCFSRCFSRCFSRC";
    char* fileNameConfirmSignal = "?FNCFNCFNCFNCFNC";
    char* writeFileDoneSignal = "?WFDWFDWFDWFDWFD";

    char* fileStoragePath = "/root/Documents/server/";
    char fileName[255];
    char filePath[255];
    FILE *wiper3;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("ServerV20221004: Listening... \n");
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
                 = accept(server_fd, (struct sockaddr*)&address,
                          (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("ServerV20221004: Connected to Client: %s\n", inet_ntoa(address.sin_addr));
    memset(bufferFromClient, 0, 255);
    valread = read(new_socket, bufferFromClient, 255);
    //if client sent for file send request
    if (strcmp(bufferFromClient, "?FSRFSRFSRFSRFSR") == 0) {
        printf("ServerV20221004: Client %s requested to upload file \n", inet_ntoa(address.sin_addr));
        //Signal file transfer is available
        send(new_socket, confirmFileTransferSignal, strlen(confirmFileTransferSignal), 0);
        printf("ServerV20221004: Told client %s file upload is available... \n", inet_ntoa(address.sin_addr));


        //Wait for file name
        printf("ServerV20221004: Waiting for client %s file filename... \n", inet_ntoa(address.sin_addr));
        memset(bufferFromClient, 0, 255);
        valread = read(new_socket, bufferFromClient, 2555);
        //Create File
        printf("ServerV20221004: File name received from client %s \n", inet_ntoa(address.sin_addr));
        strcpy(fileName, bufferFromClient);
        strcpy(filePath, fileStoragePath);
        strcat(filePath, fileName);
        makeFile1(filePath);
        printf("ServerV20221004: File %s created\n", fileName);

        //Tell Client that server is ready for content
        send(new_socket, fileNameConfirmSignal, strlen(fileNameConfirmSignal), 0);
        printf("ServerV20221004: Told client %s to start streaming file content \n", inet_ntoa(address.sin_addr));
        //Get File content
        wiper3 = fopen(filePath, "a+");
        printf("ServerV20221004: Writing content...\n");
        //Writing to File
        if (wiper3!= NULL) {
            while(1) {
                memset(bufferFromClient, 0, 255);
                valread = read(new_socket, bufferFromClient, 255);
                if (strcmp(bufferFromClient, "?EOCEOCEOCEOCEOC") == 0) {
                    printf("ServerV20221004: Client %s signaled END OF FILE\n", inet_ntoa(address.sin_addr));
                    break;
                }
                fputs(bufferFromClient, wiper3);
            }
        }

        fclose(wiper3);
        printf("ServerV20221004: Closed file writer for filename %s\n", filePath);
        //Done writing files
        send(new_socket, writeFileDoneSignal, strlen(writeFileDoneSignal), 0);
        printf("ServerV20221004: Told client we closed file writer %s\n", filePath);
    }

    shutdown(server_fd, SHUT_RDWR);
    printf("ServerV20221004: Shutdown server listener... \n");
    // closing the connected socket
    close(new_socket);
    close(bufferFromClient);
    close(fileName);
    close(filePath);
    close(bufferFromClient);
    close(confirmFileTransferSignal);
    close(fileStoragePath);
    close(fileNameConfirmSignal);
    close (writeFileDoneSignal);

    printf("ServerV20221004: Closed all variables\n", filePath);
    // closing the listening socket
    return 0;
}
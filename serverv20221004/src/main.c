#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
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
    FILE *wiper1;

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
    memset(bufferFromClient, 0, 255);
    valread = read(new_socket, bufferFromClient, 255);
    //if client sent for file send request
    if (strcmp(bufferFromClient, "?FSRFSRFSRFSRFSR") == 0) {
        //Signal file transfer is available
        send(new_socket, confirmFileTransferSignal, strlen(confirmFileTransferSignal), 0);
        //Wait for file name
        memset(bufferFromClient, 0, 255);
        valread = read(new_socket, bufferFromClient, 2555);
        //Create File
        strcpy(fileName, bufferFromClient);
        strcpy(filePath, fileStoragePath);
        strcat(filePath, fileName);
        makeFile1(filePath);
        //Tell Client that server is ready for content
        send(new_socket, fileNameConfirmSignal, strlen(fileNameConfirmSignal), 0);

        //Get File content
        memset(bufferFromClient, 0, 255);
        valread = read(new_socket, bufferFromClient, 2555);
        wiper1 = fopen(filePath, "a+");
        //Writing to File
        if (wiper1 != NULL) {
            //while(fgets(buffer, bufferLength, reader1)) {
             //   printf("%s", buffer);
                fputs(bufferFromClient, wiper1);
            //}
        }

        fclose(wiper1);
        //Stream end signal
        memset(bufferFromClient, 0, 255);
        valread = read(new_socket, bufferFromClient, 2555);

        //Done writing files
        send(new_socket, writeFileDoneSignal, strlen(writeFileDoneSignal), 0);
    }

    shutdown(server_fd, SHUT_RDWR);
    // closing the connected socket
    close(new_socket);
    close(bufferFromClient);
    close(fileName);
    close(filePath);
    close(bufferFromClient);
    close(confirmFileTransferSignal);
    close(fileStoragePath);
    close(wiper1);
    close(fileNameConfirmSignal);
    close (writeFileDoneSignal);
    // closing the listening socket
    return 0;
}
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/stat.h>
#include "serverContext.h"

struct arguments_refined {
    char downloadDirectory[255];
    char *portString;
    int portNumber;
};
static void argumentProcessing(int argc, char *argv[], struct arguments_refined *arg_refined);
static void checkIfDirectoryExistsAndCreateOneIfNot(char *directoryToCheckin, char *directoryToCheck, struct arguments_refined *arg_refined);
int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char bufferFromClient[255] = {0};
    int bufferNumber = 0;
    char* confirmFileTransferSignal = "?FSRCFSRCFSRCFSRCFSRC";
    char* fileNameConfirmSignal = "?FNCFNCFNCFNCFNC";
    char* writeFileDoneSignal = "?WFDWFDWFDWFDWFD";
    char* clientAddress[255] = {0};
    char fileName[255] = {0};
    char filePath[255] = {0};
    FILE *wiper3;

    //process arguments
    struct arguments_refined arg_refined;
    argumentProcessing(argc, argv, &arg_refined);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(arg_refined.portNumber);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("ServerV20221004: Listening to port: %d \n", arg_refined.portNumber);
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
    strcpy(clientAddress, inet_ntoa(address.sin_addr));
    printf("ServerV20221004: Connected to Client: %s\n", clientAddress);

    //Make storage for this specific client
    checkIfDirectoryExistsAndCreateOneIfNot(arg_refined.downloadDirectory, clientAddress, &arg_refined);

    while (1) {
        //Read request from client.
        printf("ServerV20221004: Waiting for request from client: %s\n", clientAddress);
        valread = read(new_socket, bufferFromClient, 255);
        //Request 1. if client sent for file send request
        if (strcmp(bufferFromClient, "?FSRFSRFSRFSRFSR") == 0) {
            printf("ServerV20221004: Client %s requested to upload file \n", clientAddress);
            //Signal file transfer is available
            send(new_socket, confirmFileTransferSignal, strlen(confirmFileTransferSignal), 0);
            printf("ServerV20221004: Told client %s file upload is available... \n", clientAddress);

            //Wait for file name
            printf("ServerV20221004: Waiting for client %s file filename... \n", clientAddress);
            memset(bufferFromClient, 0, 255);
            valread = read(new_socket, bufferFromClient, 255);
            //Create File
            printf("ServerV20221004: File name received from client %s \n", clientAddress);
            strcpy(fileName, bufferFromClient);
            strcpy(filePath, arg_refined.downloadDirectory);
            strcat(filePath, fileName);
            makeFile1(filePath);
            printf("ServerV20221004: File %s created\n", fileName);

            //Tell Client that server is ready for number of buffers
            send(new_socket, fileNameConfirmSignal, strlen(fileNameConfirmSignal), 0);
            printf("ServerV20221004: Told client %s to send number of buffers \n", clientAddress);

            //Wait for number of buffers to receive
            printf("ServerV20221004: Waiting for client %s number of buffers to receive... \n", clientAddress);
            memset(bufferFromClient, 0, 255);
            valread = read(new_socket, bufferFromClient, 255);
            bufferNumber = strtoumax(bufferFromClient, NULL, 10);

            //Tell Client that server is received number of buffers
            send(new_socket, "?NBRNBRNBRNBRNBR", strlen("?NBRNBRNBRNBRNBR"), 0);
            printf("ServerV20221004: Told client %s to start streaming \n", clientAddress);

            //Get File content
            wiper3 = fopen(filePath, "a+");
            printf("ServerV20221004: Writing content...\n");
            int counter = 0;
            //Writing to File
            if (wiper3!= NULL) {
                while(counter < bufferNumber + 1) {
                    memset(bufferFromClient, 0, 255);
                    valread = read(new_socket, bufferFromClient, 255);
                    if (strcmp(bufferFromClient, "?EOCEOCEOCEOCEOC") == 0) {
                        printf("ServerV20221004: Client %s signaled END OF FILE\n", clientAddress);
                        break;
                    }

                    fputs(bufferFromClient, wiper3);
                    counter++;
                }
            }

            fclose(wiper3);
            printf("ServerV20221004: Closed file writer for filename %s\n", fileName);
            //Done writing files
            send(new_socket, writeFileDoneSignal, strlen(writeFileDoneSignal), 0);
            printf("ServerV20221004: Told client we closed file writer %s\n", fileName);
        }

        //Request 2. if client send abort connection request
        if (strcmp(bufferFromClient, "?EXITEXITEXITEXITEXIT") == 0) {
            printf("ServerV20221004: Received connection abort request from client: %s\n", inet_ntoa(address.sin_addr));
            break;
        }
    }


    shutdown(server_fd, SHUT_RDWR);
    printf("ServerV20221004: Shutdown server listener... \n");
    // closing the connected socket
    close(new_socket);
    close(bufferFromClient);
    close(fileName);
    close(filePath);
    close(confirmFileTransferSignal);
    close(fileNameConfirmSignal);
    close (writeFileDoneSignal);

    printf("ServerV20221004: Closed all variables\n");
    // closing the listening socket
    return 0;
}

int stringToInt(char tempString4[]) {

    int number = strtoumax(tempString4, NULL, 10);

    return number;
}

static void argumentProcessing(int argc, char *argv[], struct arguments_refined *arg_refined) {
    int c;
    memset(arg_refined->downloadDirectory, 0, 255);
    strcpy(arg_refined->downloadDirectory, "/root/Documents/serverstorage/");
    arg_refined->portString = "50278";
    arg_refined->portNumber = stringToInt(arg_refined->portString);
    while((c = getopt(argc, argv, ":p:d:")) != -1)   // NOLINT(concurrency-mt-unsafe)
    {
        switch(c)
        {
            case 'd':
            {
                if (optarg[strlen(optarg)-1] != '/') {
                    strcpy(arg_refined->downloadDirectory, optarg);
                    strcat(arg_refined->downloadDirectory, "/");
                } else {
                    strcpy(arg_refined->downloadDirectory, optarg);
                }
                break;
            }
            case 'p':
            {
                arg_refined->portString = optarg;
                arg_refined->portNumber = stringToInt(arg_refined->portString);
                break;
            }
            case 'P':
            {
                arg_refined->portString = optarg;
                arg_refined->portNumber = stringToInt(arg_refined->portString);
                break;
            }
        }

    }
}

static void checkIfDirectoryExistsAndCreateOneIfNot(char *directoryToCheckin, char *directoryToCheck, struct arguments_refined *arg_refined) {
    struct stat st = {0};
    char tempString7[255] = {0};
    strcpy(tempString7, directoryToCheckin);
    strcat(tempString7, directoryToCheck);
    strcat(tempString7, "/");

    if (stat(tempString7, &st) == -1) {
        mkdir(tempString7, 0700);
    }
    strcpy(arg_refined->downloadDirectory, tempString7);
}

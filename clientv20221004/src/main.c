
#define PORT 8080
#include "fileProcessor.h"

int bufferLength2 = 255;
const char* connectionAbortRequest = "?EXITEXITEXITEXITEXIT";
int main(int argc, char *argv[]) {

    //char buff[2555];
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;

    char* serverAddressToConnect = "127.0.0.1";

    char* filePath = "/";
    char* fileName = "";

    char* fileExpressions[] = {"/root/Documents/client/A Tale of Two Cities.txt", "/root/Documents/client/foo.txt"}, **filePath1;

    char bufferFromServer[bufferLength2];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, serverAddressToConnect, &serv_addr.sin_addr)
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
    printf("Connected to server %s", serverAddressToConnect);

    filePath1 = fileExpressions;
    //Loop through file expressions and send each of them.
    while(*filePath1 != "") {
        strcpy(filePath, *filePath1);
        strcpy(fileName, getFileNameFromFilePath(filePath));

        //sendOneFile(sock, filePath, fileName, bufferFromServer);

        *filePath1++;
    }


    //Connection Abort request
    printf("ClientV20221004: Send connection abort signal to server\n");
    send(sock, connectionAbortRequest, strlen(connectionAbortRequest), 0);
    // closing the connected socket
    close(client_fd);
    printf("ClientV20221004: Socket closed\n");
    return 0;
}



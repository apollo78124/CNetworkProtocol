
#define PORT 50278

#include <inttypes.h>
#include "fileProcessor.h"

int bufferLength2 = 255;
const char* connectionAbortRequest = "?EXITEXITEXITEXITEXIT";
struct arguments_refined {
    char *serverAddress;
    char *portString;
    int portNumber;
    int fileExpressionsSize;
    char *file_expressions[20];
};
static void argumentProcessing(int argc, char *argv[], struct arguments_refined *arg_refined);
int main(int argc, char *argv[]) {

    //char buff[2555];
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;

    char* serverAddressToConnect;

    char* filePath = "/";
    char* fileName = "";

    char bufferFromServer[bufferLength2];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    //process arguments
    struct arguments_refined arg_refined;
    argumentProcessing(argc, argv, &arg_refined);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(arg_refined.portNumber);
    serverAddressToConnect = arg_refined.serverAddress;
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

    for (size_t i = 0; i < arg_refined.fileExpressionsSize; i++)
    {
        filePath = arg_refined.file_expressions[i];
        fileName = getFileNameFromFilePath(arg_refined.file_expressions[i]);
        sendOneFile(sock, filePath, fileName, bufferFromServer);
    }


    //Connection Abort request
    printf("ClientV20221004: Send connection abort signal to server\n");
    send(sock, connectionAbortRequest, strlen(connectionAbortRequest), 0);
    // closing the connected socket
    close(client_fd);
    printf("ClientV20221004: Socket closed\n");
    return 0;
}

int stringToInt(char tempString4[]) {

    int number = strtoumax(tempString4, NULL, 10);

    return number;
}


static void argumentProcessing(int argc, char *argv[], struct arguments_refined *arg_refined) {
    int c;

    while((c = getopt(argc, argv, ":p:s:")) != -1)   // NOLINT(concurrency-mt-unsafe)
    {
        switch(c)
        {
            case 's':
            {
                arg_refined->serverAddress = optarg;
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

    if(optind < argc)
    {
        arg_refined->fileExpressionsSize = 0;
        if ((argc - 1 - optind) > 19) {

        }
        int tempFEIndex = 0;
        for(char **tempv = argv+ optind; *tempv != argv[argc]; tempv++) {
            arg_refined->file_expressions[tempFEIndex] = *tempv;
            tempFEIndex++;
            arg_refined->fileExpressionsSize++;
        }
    }
}





//
// Created by dldms on 10/5/2022.
//
#include <stdio.h>
#include "serverContext.h"
// Return value:
// 0 : Invalid or faulty request from client
// 1 : Connection successtul
char ipIn[] = "192.168.1.79";

int listenForRequest() {
    printf(ipIn);
    takeFileFromClient(ipIn);
}

int takeFileFromClient(char fileName[]) {
    printf(ipIn);
}
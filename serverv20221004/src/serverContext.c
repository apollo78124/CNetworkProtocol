//
// Created by dldms on 10/5/2022.
//
#include <stdio.h>
#include "serverContext.h"


int makeFile1(char fileName[]) {
    FILE *wiper2;
    wiper2 = fopen("/root/Documents/server/received.txt", "w+");
    fputs("", wiper2);
    fclose(wiper2);
}
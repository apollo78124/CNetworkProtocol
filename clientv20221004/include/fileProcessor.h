//
// Created by davlee on 10/5/2022.
//
#include "header.h"
#ifndef V20221004_FILEPROCESSOR_H
#define V20221004_FILEPROCESSOR_H
void sendOneFile(int socket1, char filePath[], char fileName[], char bufferFromServer[]);
void loopThroughStringArray(char tempString3[]);
char* getFileNameFromFilePath(char tempString4[]);
#endif //V20221004_FILEPROCESSOR_H


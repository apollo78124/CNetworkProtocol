//
// Created by root on 04/10/22.
//

#ifndef V4_FILEPROCESSING_H
#define V4_FILEPROCESSING_H
#include <stddef.h>


void readFile(char *file_exps[]);
int checkForAsterisk(char tempString2[]);
char** getListOfFilePathFromExpression(char tempString3[]);

#endif //V4_FILEPROCESSING_H

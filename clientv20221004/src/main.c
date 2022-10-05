#include <stdio.h>
#include "fileProcessor.h"

int main(int argc, char *argv[]) {
    char ipIn[] = "192.168.1.79";
    char fileToSend[] = "D:/Test1/foo.txt";

    makeNewFile(fileToSend);

    return 0;
}

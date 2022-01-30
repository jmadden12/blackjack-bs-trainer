#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

unsigned int readFileToString(char** receive, unsigned int size, const char* filename){
    unsigned int charsRead = 0;
    char mode = 'r';
    FILE* handle = fopen(filename, &mode);
    char buf;
    int fd = fileno(handle);
    while(read(fd, &buf, 1) > 0){
        if(charsRead == size){
            size *= 2;
            char* new = malloc(size);
            strncpy(new, *receive, charsRead);
            *receive = new;
        }
        (*receive)[charsRead] = buf;
        charsRead++;
    }
    if(charsRead < size){
        *receive[charsRead] = '\0';
    } else {
        size++;
        char* new = malloc(size);
        strncpy(new, *receive, charsRead);
        *receive = new;  
        *receive[charsRead] = '\0';
    }
    return charsRead;
}
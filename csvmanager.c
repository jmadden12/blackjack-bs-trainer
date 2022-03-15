#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cardhelper.h"

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
        (*receive)[charsRead] = '\0';
    } else {
        size++;
        char* new = malloc(size);
        strncpy(new, *receive, charsRead);
        *receive = new;  
        (*receive)[charsRead] = '\0';
    }
    return charsRead;
}

char** allocateFormattedArray(){
    int len = (NUM_DEALER_CARDS + 1) * NUM_PLAYER_HANDS;
    char** array = calloc(len, sizeof(char*));
    for(int i = 0; i < len; i++){
        array[i] = calloc(4, sizeof(char));
    }
    return array;
}
/* 
    IT GOES ON AND ON .... NEVER ON AND OFF ...
    STAY STRONG AND NEVER TAKE A PAUSE
    
*/
void formatCSVRawString(char* toFormat, char*** formatted){
    for(int i = 0; i < (NUM_PLAYER_HANDS * LINE_LEN); i++){
        if(i % LINE_LEN == 0){
            /*
            printf("Player Hand Detected: ");
            printf("%c%c\n", toFormat[i], toFormat[i + 1]);
            */
            int offset = ((i/LINE_LEN)*(NUM_DEALER_CARDS + 1));
            strncpy((*formatted)[offset], &(toFormat[i]), 2);
        }
        if(((i % LINE_LEN) % 2) == 1 && (i % LINE_LEN) > 2){
            /*
            printf("Basic choice detected: ");
            printf("%c\n", toFormat[i]);
            */
            int offset = ((i/LINE_LEN)*(NUM_DEALER_CARDS + 1)) + ((i % LINE_LEN)/2);
            strncpy((*formatted)[offset], &(toFormat[i]), 1);
        }

    }
}

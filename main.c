#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cardhelper.h"
#include "csvmanager.h"


void testCardValueHandTranslate(){
    char* testCases[12] = {"QQ", "QJ", "22", "AA", "3A", "A2", "A6", "7A", "7T", "8J", "65", "34"};
    char* testAnsrs[12] = {"TT", "TT", "22", "AA", "A3", "A2", "A6", "A7", "17", "18", "11", "07"};
    for(int i = 0; i < 12; i++){
        char answer[3];
        char a, b;
        charactersFromHand(testCases[i], &a, &b);
        translatePlayerHand(answer, a, b);
        printf("Case: %s, Output: %s, Answer: %s, strcmp: %d\n", testCases[i], answer, testAnsrs[i], strcmp(testAnsrs[i], answer));
    }
}

void testReadFileToString(){
    unsigned int bufsize = 1024;
    char* test = malloc(bufsize);

    unsigned int charsRead = readFileToString(&test, bufsize, "testfile.txt");

    printf("%s\n", test);

}

int main(){
    //testCardValueHandTranslate();
    testReadFileToString();
    return 0;
}

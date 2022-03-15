#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <time.h>

#include <unistd.h>

#include "cardhelper.h"
#include "csvmanager.h"


double numberHands = 0;
double correctHands = 0;

void testCheckPlayerResponse(){
    unsigned int bufsize = 1024;
    char* test = malloc(bufsize);

    unsigned int charsRead = readFileToString(&test, bufsize, "basicstrategy.csv");

    char** formatted = allocateFormattedArray();
    formatCSVRawString(test, &formatted);
    double check = 0;
    check = checkPlayerResponse("15", '2', "H", formatted);
    
}

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

    unsigned int charsRead = readFileToString(&test, bufsize, "basicstrategy.csv");

    printf("%s\n", test);
    char** formatted = allocateFormattedArray();
    formatCSVRawString(test, &formatted);
    for(int i = 0; i < (NUM_DEALER_CARDS + 1) * NUM_PLAYER_HANDS; i++){
        printf("%s", formatted[i]);
        if(i % (NUM_DEALER_CARDS + 1) == 10){
            printf("\n");
        }
    }

}

void quitHandler(int sig){
    if(numberHands != 0){
    printf("\n\n\nSaving results. Bye!\n\n\n");
    FILE* handle = fopen("results", "a");
    fprintf(handle, "%u\n", (unsigned int)time(NULL));
    fprintf(handle, "%f %f %f\n", correctHands, numberHands, correctHands/numberHands);
    }
    exit(0);
}

int main(){
    signal(SIGINT, quitHandler);
    //testCardValueHandTranslate();
    //testReadFileToString();
    //testCheckPlayerResponse();
    printf("BlackJack Basic Strategy Trainer\n");
    printf("By Jack Madden\n");
    printf(" ___   ___   ___   ___   ___\n");
    printf("|A  | |K  | |Q  | |J  | |10 |\n");
    printf("|(`)| |(`)| |(`)| |(`)| |(`)|\n");
    printf("|_\\_| |_\\_| |_\\_| |_\\_| |_\\_|\n");
    printf("H for Hit, S for Stand, P for sPlit, D for Double Down (case sensitive)\n");

    unsigned int bufsize = 1024;
    char* test = malloc(bufsize);

    unsigned int charsRead = readFileToString(&test, bufsize, "basicstrategy.csv");

    char** formatted = allocateFormattedArray();
    formatCSVRawString(test, &formatted);

    while(1){
        char* playerResponse = calloc(4, sizeof(char));
        char* prf = calloc(4, sizeof(char));
        char* hand = generatePlayerHand();
        char upcard = generateDealerCard();
        char* recievehand = calloc(3, sizeof(char));
        translatePlayerHand(recievehand, hand[0], hand[1]);
        
        printf("Dealer's card: %c\n", upcard);
        printf("Your hand: %s\n", hand);
        printf("Your response: ");
        fgets(playerResponse, 4, stdin);
        sscanf(playerResponse, "%s", prf);
        correctHands += checkPlayerResponse(recievehand, upcard, prf, formatted);
        numberHands += 1;   
        if(numberHands != 0){
            printf("Correct ratio: %f\n", correctHands/numberHands);
        }
        printf("_______________________________________________________\n\n\n");
        free(hand);
        free(playerResponse);
    }



    free(test);
    free(formatted);
    return 0;
}

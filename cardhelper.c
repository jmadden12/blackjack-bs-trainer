#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "cardhelper.h"

void charactersFromHand(char* hand, char* a, char* b){
    sscanf(hand, "%c%c", a, b);
}

int getCardValue(char card){
    if(card == 'T' || card == 'J' || card == 'Q' || card == 'K'){
        return 10;
    } else if (card > 49 && card < 58){
        return card - 48;
    } else if (card == 'A'){
        return 1;
    } else {
        return -1;
    }
}

void translatePlayerHand(char* receive, char a, char b){
    int valA = getCardValue(a);
    int valB = getCardValue(b);
    if(valA == valB){
        if(valA == 1){
            receive[0] = 'A';
            receive[1] = 'A';
            
        } else if (valA == 10){
            receive[0] = 'T';
            receive[1] = 'T';
        } else {
            receive[0] = (char)(valA + 48);
            receive[1] = (char)(valA + 48);
        }
    } else if(valA == 1 || valB == 1){
        receive[0] = 'A';
        if(valA == 1){
            receive[1] = (char)(valB + 48);
        } else {
            receive[1] = (char)(valA + 48); 
        }
    } else {
        int total = valA + valB;
        if(total < 10){
            receive[0] = '0';
            receive[1] = (char)(total + 48);
        } else {
            receive[0] =  '1';
            receive[1] = (char)((total - 10) + 48);
        }
    }
    receive[2] = '\0';
}

double checkPlayerResponse(char* hand, char upcard, char* response, char** table){
    double correct = 0;
    for(int i = 0; i < ((NUM_DEALER_CARDS + 1) * NUM_PLAYER_HANDS); i+= (NUM_DEALER_CARDS + 1)){
        if(strncmp(table[i], hand, 2) == 0){
            if(strncmp(table[i + getCardValue(upcard)], response, 1) == 0){
                printf("Correct response! \n");
                correct = 1;
                break;
            } else {
                printf("Incorrect response: correct response was %s\n", table[i + getCardValue(upcard)]);
                correct = 0;
                break;
            }
        }
    }
    return correct;
}

char generateDealerCard(){
    char possible[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    srand((unsigned int)time(NULL));
    int card = rand() % 13;
    return possible[card];
}

char* generatePlayerHand(){
    char possible[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    srand((unsigned int)time(NULL) + 4);
    int card1 = rand() % 13;
    int card2 = rand() % 13;
    char* hand = calloc(3, sizeof(char));
    hand[0] = possible[card1];
    hand[1] = possible[card2];
    return hand;
}
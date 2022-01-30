#include <stdio.h>

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
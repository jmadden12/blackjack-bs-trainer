#include <stdio.h>
#include <string.h>

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

int main(){
    testCardValueHandTranslate();
    return 0;
}

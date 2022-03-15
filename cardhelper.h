#define NUM_PLAYER_HANDS 32
#define LINE_LEN 23

#define NUM_DEALER_CARDS 10


void charactersFromHand(char*, char*, char*);

int getCardValue(char);

void translatePlayerHand(char*, char, char);

double checkPlayerResponse(char* hand, char upcard, char* response, char** table);

char* generatePlayerHand();

char generateDealerCard();
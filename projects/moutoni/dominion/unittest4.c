// int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)

//struct gameState {
//    int numPlayers; //number of players
//    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//    int embargoTokens[treasure_map+1];
//    int outpostPlayed;
//    int outpostTurn;
//    int whoseTurn;
//    int phase;
//    int numActions; /* Starts at 1 each turn */
//    int coins; /* Use as you see fit! */
//    int numBuys; /* Starts at 1 each turn */
//    int hand[MAX_PLAYERS][MAX_HAND];
//    int handCount[MAX_PLAYERS];
//    int deck[MAX_PLAYERS][MAX_DECK];
//    int deckCount[MAX_PLAYERS];
//    int discard[MAX_PLAYERS][MAX_DECK];
//    int discardCount[MAX_PLAYERS];
//    int playedCards[MAX_DECK];
//    int playedCardCount;
//};


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

#include <limits.h>

int main()
{
    
    int seed = 500;
    int player = 2;
    int deckCount = 0;
    
    //int handPos;
    int trashFlag = 0;
    
    struct gameState state;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    
    initializeGame(player, k, seed, &state);
    
    
    
    for (int i = INT_MIN; i <= INT_MAX; ++i) {
        if(!int scoreFor (player, gameState *state)){
            deckCount = fullDeckCount(player, i, &state);
            printf("For iteration %i deck count is %i\n", %i , deckCount);
            //break;;
        }
       // printf("Passed test to discard all cards!\n");
        
    }
}
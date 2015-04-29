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
    for (int i = 0; i <= INT_MAX ; ++i) {
        if(!getCost(i))
        {
            printf("Test to get cost of card %i failed: exiting\n!", i);
            break;
        }
        printf("Test to get cost of all cards pased!");
    }
}
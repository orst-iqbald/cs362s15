#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"

//insert the given card into a random hand position of the current player's hand.
//this will overwrite the card currently in that position.
//returns the position of the inserted card.
int insertCardRand(struct gameState* gs, int card);

//initialize every gameState variable to some random but valid number
void genRandState(struct gameState* gs);

//Returns a weighted random number based upon the given ranges and their 
//corresponding weights.  Returns -1 on failure.
//ranges[]: ranges of values. ex. [2, 5, 6] -> [2,5), [5,6), [6,RAND_MAX)
//rangesLen: length of ranges[]
//weights[]: weights of the various ranges specified by ranges[].  An 
//individual weight divided by the sum of the weights gives the chance that a 
//number from the corresponding range will be returned
//weightsLen: length of weights[]
//PRECONDITION: ranges[] must have increasing values. Every value must be //nonnegative. rangesLen and weightsLen must be equal. srand() must already be
//set
int weightedRand(int ranges[], int rangesLen, int weights[], int weightsLen);

//prints some of the variables of th gamestate
//debug purposes
void printGameState(struct gameState* gs);

//counts the number of treasure cards in the hand of the current player of the
//gameState
int handTreasureCount(struct gameState* gs);

//tests cardAdventurer()
int main() {
    int i;
    struct gameState* gs = malloc(sizeof(struct gameState));
    struct gameState* gs0 = malloc(sizeof(struct gameState));
    int handpos;
    int player;
    int res;      //return value of function
    int deltaDeck;
    int deltaDiscard;
    int deltaHand;
    int deltaPlayed;
    int deltaHandTreasure;
    int isGoodCardCount;
    int isGoodHandCount;
    int isGoodPlayedCardCount;
    int isGoodHandTreasureCount;
    
    srand(42);
    
    printf("Testing randomtestadventurer.c:\n");
    printf("FAILED TESTS: ");
    
    for (i = 0; i < 1000; ++i) {
        isGoodCardCount = 1;
        isGoodHandCount = 1;
        isGoodPlayedCardCount = 1;
        isGoodHandTreasureCount = 1;
        
        genRandState(gs);
        //make sure smithy is in current player's hand
        handpos = insertCardRand(gs, adventurer);
        player = gs->whoseTurn;
        //make a copy of the gameState
        memcpy(gs0, gs, sizeof(struct gameState));
        
        //printGameState(gs0);
        //printGameState(gs);
        
        res = cardAdventurer(gs, handpos);
        assert(res == 0);
        
        //printGameState(gs0);
        //printGameState(gs);
        
        deltaDeck = gs->deckCount[player] - gs0->deckCount[player];
        deltaDiscard = gs->discardCount[player] - gs0->discardCount[player];
        deltaHand = gs->handCount[player] - gs0->handCount[player];
        deltaPlayed = gs->playedCardCount - gs0->playedCardCount;
        
        if (deltaDeck + deltaDiscard + deltaHand != -1)
            isGoodCardCount = 0;
        //the played adventurer card leaves the hand
        if (deltaHand < -1 || deltaHand > 1)
            isGoodHandCount = 0;
        if (deltaPlayed != 1)
            isGoodPlayedCardCount = 0;
        
        deltaHandTreasure = handTreasureCount(gs) - handTreasureCount(gs0);
        
        if (deltaHandTreasure < 0 || deltaHandTreasure > 2)
            isGoodHandTreasureCount = 0;
        
        if (!isGoodCardCount || !isGoodHandCount || 
            !isGoodPlayedCardCount || !isGoodHandTreasureCount) {
            printf("%i", i);
            if (!isGoodCardCount)
                printf("^");
            if (!isGoodHandCount)
                printf("+");
            if (!isGoodPlayedCardCount)
                printf("*");
            if (!isGoodHandTreasureCount)
                printf("$");
            printf(" ");
        }
    }
    
    printf("\n^Failed due to cumulative deck/discard/hand count\n");
    printf("+Failed due to hand count\n");
    printf("*Failed due to played card count\n");
    printf("$Failed due to the change in the number of treasures\n");
    printf("%i test runs of randomtestadventurer.c executed\n\n", i);
    
    return 0;
}

int insertCardRand(struct gameState* gs, int card) {
    int player = gs->whoseTurn;
    int pos;
    
    if (gs->handCount[player] != 0) {
        pos = rand() % gs->handCount[player];
    } else {
        gs->handCount[player] = 1;
        pos = 0;
    }
    
    gs->hand[player][pos] = card;
    
    return pos;
}

void genRandState(struct gameState* gs) {
    int i, j;
    
    gs->numPlayers = (rand() % 3) + 2;
    for (i = 0; i < treasure_map+1; ++i) {
        gs->supplyCount[i] = rand() % 16;
    }
    for (i = 0; i < treasure_map+1; ++i) {
        //15 embargo tokens total
        gs->embargoTokens[i] = rand() % 16;
    }
    gs->outpostPlayed = rand() % 2;
    gs->outpostTurn = rand() % 2;
    gs->whoseTurn = rand() % gs->numPlayers;
    gs->phase = rand() % 3;
    gs->numActions = rand();
    gs->coins = rand();
    gs->numBuys = rand();
    for (i = 0; i < gs->numPlayers; ++i) {
        gs->handCount[i] = 
                weightedRand((int[3]){0,10,MAX_HAND}, 3, (int[3]){99,1,0}, 3);
        for (j = 0; j < gs->handCount[i]; ++j) {
            gs->hand[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs->numPlayers; ++i) {
        gs->deckCount[i] = 
                weightedRand((int[3]){0,40,MAX_DECK}, 3, (int[3]){95,5,0}, 3);
        for (j = 0; j < gs->deckCount[i]; ++j) {
            gs->deck[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs->numPlayers; ++i) {
        gs->discardCount[i] = 
                weightedRand((int[3]){0,40,MAX_DECK}, 3, (int[3]){95,5,0}, 3);
        for (j = 0; j < gs->discardCount[i]; ++j) {
            gs->discard[i][j] = rand() % treasure_map+1;
        }
    }
    gs->playedCardCount = rand() % 10;
    for (i = 0; i < gs->playedCardCount; ++i) {
        gs->playedCards[i] = rand() % treasure_map+1;
    }
}

int weightedRand(int ranges[], int rangesLen, int weights[], int weightsLen) {
    int i;
    int weightSum = 0;
    int rawRange;
    
    //ensure that the arrays are the same length
    if (rangesLen != weightsLen)
        return -1;
    
    //sum weights[]
    for (i = 0; i < weightsLen; ++i) {
        weightSum += weights[i];
    }
    
    //pick a range based on their weights
    rawRange = rand() % weightSum;
    for (i = 0; i < weightsLen; ++i) {
        rawRange -= weights[i];
        if (rawRange < 0) {
            break;
        }
    }
    
    //ensure that the range has only nonnegative values
    if (ranges[i] < 0)
        return -1;
    
    //ensure that the range is non-empty
    if (ranges[i] >= ranges[i+1])
        return -1;
    
    //calculate the chosen range and return a random number within that range
    if (i + 1 < rangesLen) {
        return ( rand() % (ranges[i+1] - ranges[i]) ) + ranges[i];
    } else {
        return ( rand() % (RAND_MAX - ranges[i]) ) + ranges[i];
    }
}

void printGameState(struct gameState* gs) {
    int p = gs->whoseTurn;
    
    printf("\n");
    printf("numPlayers: %i\n", gs->numPlayers);
    printf("whoseTurn: %i\n", gs->whoseTurn);
    printf("handCount[p]: %i\n", gs->handCount[p]);
    printf("deckCount[p]: %i\n", gs->deckCount[p]);
    printf("discardCount[p]: %i\n", gs->discardCount[p]);
    printf("playedCardCount: %i\n", gs->playedCardCount);
}

int handTreasureCount(struct gameState* gs) {
    int i;
    int player = gs->whoseTurn;
    int card;
    int treasureCt;
    
    for (i = 0; i < gs->handCount[player]; ++i) {
        card = gs->hand[player][i];
        if (card == copper || card == silver || card == gold) {
            ++treasureCt;
        }
    }
    
    return treasureCt;
}

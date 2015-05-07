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

//tests cardSmithy()
int main() {
    int i;
    struct gameState* gs = malloc(sizeof(struct gameState));
    struct gameState* gs0 = malloc(sizeof(struct gameState));
    int handpos;
    int player;
    int res;      //return value of function
    
    srand(42);
    
    printf("Testing randomtestcard.c:\n");
    printf("FAILED TESTS: ");
    
    for (i = 0; i < 1000; ++i) {
        genRandState(gs);
        //make sure smithy is in current player's hand
        handpos = insertCardRand(gs, smithy);
        player = gs->whoseTurn;
        //make a copy of the gameState
        memcpy(gs0, gs, sizeof(struct gameState));
        
        //printGameState(gs0);
        //printGameState(gs);
        
        res = cardSmithy(gs, handpos);
        assert(res == 0);
        
        //printGameState(gs0);
        //printGameState(gs);
                 
        if (gs->deckCount[player] != 0 || gs->discardCount[player] != 0) {
            //deck/discard should go down by 3 cards total
            assert( (gs->deckCount[player] + gs->discardCount[player]) - 
                    (gs0->deckCount[player] + gs0->discardCount[player]) == -3);
            //+3 cards but a card also gets played
            assert(gs->handCount[player] - gs0->handCount[player] == 2);
        } else {
            //that is, unless both deck and discard get depleted
            assert( (gs->deckCount[player] + gs->discardCount[player]) - 
                    (gs0->deckCount[player] + gs0->discardCount[player]) <= 0);
            assert( (gs->deckCount[player] + gs->discardCount[player]) - 
                    (gs0->deckCount[player] + gs0->discardCount[player]) >= -3);
            assert(gs->handCount[player] - gs0->handCount[player] >= -1);
            assert(gs->handCount[player] - gs0->handCount[player] <= 2);
        }
        if (gs->playedCardCount - gs0->playedCardCount != 1) {
            printf("%i*, ", i);
        }
    }
    
    printf("\n*Failed due to playedCardCount\n");
    printf("%i test runs of randomtestcard.c executed\n\n", i);
    
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
    ranges
    
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
    for (i = 0; i < weightLen; ++i) {
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
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

//tests cardSmithy()
int main() {
    int i;
    struct gameState* gs = malloc(sizeof(struct gameState));
    struct gameState* gs0;
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
        memcpy (gs0, gs, sizeof(struct gameState));
        
        res = cardSmithy(gs, handpos);
        assert(res == 0);
        
        //deck/discard should go down by 3 cards total
        assert( (gs->deckCount[player] + gs->discardCount[player]) - 
                (gs0->deckCount[player] + gs0->discardCount[player]) == -3);
        if (gs->playedCardCount[player] - gs0->playedCardCount[player] != 1) {
            printf("%i, ", i);
        }
        assert(gs->handCount[player] - gs0->handCount[player] == 3);
    }
    
    printf("\n%i test runs of randomtestcard.c executed\n\n");
    
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
    
    gs->numPlayers = rand() % MAX_PLAYERS;
    for (i = 0; i < treasure_map+1; ++i) {
        gs->supplyCount[i] = rand() % MAX_DECK;
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
        gs->handCount[i] = rand() % MAX_HAND
        for (j = 0; j < gs->handCount[i]; ++j) {
            gs->hand[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs->numPlayers; ++i) {
        gs->deckCount[i] = rand() % MAX_DECK
        for (j = 0; j < gs->deckCount[i]; ++j) {
            gs->deck[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs->numPlayers; ++i) {
        gs->discardCount[i] = rand() % MAX_DECK
        for (j = 0; j < gs->discardCount[i]; ++j) {
            gs->discard[i][j] = rand() % treasure_map+1;
        }
    }
    gs->playedCardCount = rand() % MAX_DECK
    for (i = 0; i < gs->playedCardCount; ++i) {
        gs->playedCards[i] = rand() % treasure_map+1;
    }
}
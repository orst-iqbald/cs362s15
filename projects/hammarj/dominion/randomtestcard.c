#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"

//initialize every gameState variable to some random but valid number
void genRandState(struct gameState& gs);

int main() {
    int i;
    
    return 0;
}

void genRandState(struct gameState& gs) {
    int i, j;
    
    gs.numPlayers = rand() % MAX_PLAYERS;
    for (i = 0; i < treasure_map+1; ++i) {
        gs.supplyCount[i] = rand() % MAX_DECK;
    }
    for (i = 0; i < treasure_map+1; ++i) {
        //15 embargo tokens total
        gs.embargoTokens[i] = rand() % 16;
    }
    gs.outpostPlayed = rand() % 2;
    gs.outpostTurn = rand() % 2;
    gs.whoseTurn = rand() % gs.numPlayers;
    gs.phase = rand() % 3;
    gs.numActions = rand();
    gs.coins = rand();
    gs.numBuys = rand();
    for (i = 0; i < gs.numPlayers; ++i) {
        gs.handCount[i] = rand() % MAX_HAND
        for (j = 0; j < gs.handCount[i]; ++j) {
            gs.hand[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs.numPlayers; ++i) {
        gs.deckCount[i] = rand() % MAX_DECK
        for (j = 0; j < gs.deckCount[i]; ++j) {
            gs.deck[i][j] = rand() % treasure_map+1;
        }
    }
    for (i = 0; i < gs.numPlayers; ++i) {
        gs.discardCount[i] = rand() % MAX_DECK
        for (j = 0; j < gs.discardCount[i]; ++j) {
            gs.discard[i][j] = rand() % treasure_map+1;
        }
    }
    gs.playedCardCount = rand() % MAX_DECK
    for (i = 0; i < gs.playedCardCount; ++i) {
        gs.playedCards[i] = rand() % treasure_map+1;
    }
}
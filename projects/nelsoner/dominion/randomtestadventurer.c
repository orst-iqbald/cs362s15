/*************************************************
* Author:						Eric Nelson
* Date Created:					5/6/15
* Last Modification Date:		5/6/15
* Filename:						randomtestadventurer.c
*
* Description: This is a random unit test to test the Adventurer card in dominion.c
*
*
**************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkAdventurerEffect(int currentPlayer, int card, struct gameState *state){

    struct gameState pre;
    int drawntreasure = 0;
    int temphand[MAX_HAND];
    int bonus[2] = {0, 1};
    int r, lastCardDrawn, postDeckCount;
    int z = 0;
    int preDeckCount = state->discardCount[currentPlayer] + state->deckCount[currentPlayer] + state->handCount[currentPlayer];

    memcpy(&pre, state, sizeof(struct gameState));
    SelectStream(2);
    PutSeed(3);
    r = cardEffect(card, 1, 1, 1, state, 1, bonus);

    postDeckCount = state->discardCount[currentPlayer] + state->deckCount[currentPlayer] + state->handCount[currentPlayer];

    assert(preDeckCount == postDeckCount);

    assert (r == 0);

    PutSeed(3);

     while(drawntreasure<2){

        drawCard(currentPlayer, &pre);
        lastCardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        if (lastCardDrawn == copper || lastCardDrawn == silver || lastCardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=lastCardDrawn;
            pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while(z-1>=0){
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z=z-1;
    }

    assert(memcmp(&pre, state, sizeof(struct gameState)) == 0);


    return 0;
}

int main () {

    int i, j, n;
    int currentPlayer;

    struct gameState G;

    printf ("Testing Adventurer Card Effect.\n");

    printf ("RANDOM TESTS.\n");

    SelectStream(2);
    PutSeed(3);

    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        G.whoseTurn = floor(Random() *(MAX_PLAYERS));
        currentPlayer = G.whoseTurn;
        G.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
        G.handCount[currentPlayer] = floor(Random() * MAX_HAND);
                G.discardCount[currentPlayer] = MAX_DECK - (G.deckCount[currentPlayer]+G.handCount[currentPlayer]);

                G.playedCardCount = floor(Random() * MAX_DECK);

                for (j=0; j<G.deckCount[currentPlayer]; j++){
            G.deck[currentPlayer][j] =  floor(Random() *(treasure_map+1));
                }
        for (j=0; j<G.discardCount[currentPlayer]; j++){
            G.discard[currentPlayer][j] =  floor(Random() *(treasure_map+1));
                }
                for (j=0; j<G.handCount[currentPlayer]; j++){
            G.hand[currentPlayer][j] = floor(Random() *(treasure_map+1));
                }

        checkAdventurerEffect(currentPlayer, adventurer, &G);

    }

    printf ("ALL TESTS OK\n");

    return 0;
}

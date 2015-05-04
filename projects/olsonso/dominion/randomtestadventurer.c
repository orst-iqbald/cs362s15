/* -----------------------------------------------------------------------
 * Random Unit Test for zzzadventurercardplay function
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "math.h"

void zzzadventurercardplay(int drawntreasure, int currentPlayer, int cardDrawn, int temphand[MAX_HAND], int z, struct gameState* state);

void testzzzadventurercardplay(int drawntreasure, int currentPlayer, int cardDrawn, int temphand[MAX_HAND], int z, struct gameState* post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    
    zzzadventurercardplay(drawntreasure, currentPlayer, cardDrawn, temphand, z, post);
    
    while (drawntreasure < 2) {
        if (pre.deckCount[currentPlayer] < 1) {
            //if the deck is empty we need to shuffle discard and add to deck
            shuffle(currentPlayer, &pre);
        }
        drawCard(currentPlayer, &pre);
        cardDrawn = pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else {
            temphand[z] = cardDrawn;
            pre.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while (z - 1 >= 0) {
        pre.discard[currentPlayer][pre.discardCount[currentPlayer]++] =
        temphand[z - 1]; // discard all cards in play that have been drawn
        z = z - 1;
    }
    
    //assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
	if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
		printf("Random test for adventurer card failed.\n");
	}
}

int main (int argc, char** argv) {
    int i, n, z, drawntreasure, player, cardDrawn;
    int temphand[MAX_HAND];
    struct gameState G;
    
    printf ("Random testing zzzadventurercardplay.\n");
    
    SelectStream(2);
    PutSeed(3);
    
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        player = floor(Random() * 2);
        G.whoseTurn = player;
        drawntreasure = 0;
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = floor(Random() * MAX_DECK);
    
        //fill player's hand valid cards
        for (i = 0; i <= G.handCount[player]; i++)
        {
            G.hand[player][i] = floor(Random() * 28);
        }
        //fill player's deck with valid cards
        for (i = 0; i <= G.deckCount[player]; i++)
        {
            G.deck[player][i] = floor(Random() * 28);
        }
        //fill players discard with valid cards
        for (i = 0; i <= G.discardCount[player]; i++)
        {
            G.discard[player][i] = floor(Random() * 28);
        }
    
        testzzzadventurercardplay(drawntreasure, player, cardDrawn, temphand, z, &G);
    }
    
    printf("Finished testing.\n");
    
    return 0;
}

/*
 * This file contains a random tester function for the adventurer card implementation
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "math.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>



// This is the main random test function for the Adventurer card. It is to be called in main()
int testAdventurerCard(int curPlayer, struct gameState *post, int randSeed) {
        int z = 0; // temp hand counter
        int drawntreasure = 0;
        int cardDrawn;
        int temphand[MAX_HAND];
        int handPos = 0;
        int counter = 0;
        int result;
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        SelectStream(2);
        PutSeed(randSeed);

        result = cardEffect(adventurer, 0, 0, 0, post, 0, 0);
        PutSeed(randSeed);

        while(drawntreasure < 2) {
                if (pre.deckCount[curPlayer] < 1){      //if the deck is empty we need to shuffle discard and add to deck
                        shuffle(curPlayer, &pre);
                }

                if (drawCard(curPlayer, &pre) == 0) {
                        counter++;
                }

                cardDrawn = pre.hand[curPlayer][pre.handCount[curPlayer] - 1];  //top card of hand is most recently drawn card.

                if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                        drawntreasure++;
                else {
                        temphand[z]=cardDrawn;
                        pre.handCount[curPlayer]--; //this should just remove the top card (the most recently drawn one).
                        counter--;
                        z++;
                }
        }

        while(z-1 >= 0) {
                pre.discard[curPlayer][pre.discardCount[curPlayer]++]=temphand[z-1];// discard all cards in play that have been drawn
                z=z-1;
        }

        discardCard(handPos, curPlayer, &pre, 0);

        assert(result == 0);
        assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

        return 0;
}




int main() {

        struct gameState game;
        srand(time(NULL));
        int randSeed = rand();
        int i,j,p;

        printf ("Random Testing Adventurer Card.....\n");

        SelectStream(3);
        PutSeed(randSeed);

        for (i = 0; i < 1000; i++) {
                SelectStream(3);
                for (j = 0; j < sizeof(struct gameState); j++) {
                        ((char*)&game)[j] = floor(Random() * 255);
                }

                p = floor(Random() * MAX_PLAYERS);

                game.whoseTurn = p;
                game.deckCount[p] = floor(Random() * MAX_DECK);
                game.discardCount[p] = floor(Random() * MAX_DECK);
                game.handCount[p] = floor(Random() * MAX_HAND);
                game.playedCardCount = floor(Random() * MAX_DECK);

                for (j = 0; j < game.handCount[p]; j++) {
                        game.hand[p][j] = floor(Random() * (treasure_map + 1));
                }

                for (j = 0; j < game.discardCount[p]; j++) {
                        game.discard[p][j] = floor(Random() * (treasure_map + 1));
                }

                for (j = 0; j < game.deckCount[p]; j++) {
                        game.deck[p][j] = floor(Random() * (treasure_map + 1));
                }

                testAdventurerCard(p, &game, randSeed);
        }

        printf("ALL TESTS OK\n\n");
        return 0;
}
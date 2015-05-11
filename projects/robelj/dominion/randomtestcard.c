/* 
 * This file implements a random test function for the Embargo action card
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



// This is the main random test function for the Embargo card. It is to be called in main()
int testEmbargoCard(int curPlayer, int choice1, int choice2, int choice3, struct gameState *post, int randSeed) {
        
        int result;
        int handPos = floor(Random() * post->handCount[curPlayer]);
        int getEmbargoTokens = post->embargoTokens[choice1];
        int getCoins = post->coins;
        int getHandCount = post->handCount[curPlayer];
        struct gameState pre;

        memcpy(&pre, post, sizeof(struct gameState));

        SelectStream(2);
        PutSeed(randSeed);

        result = cardEffect(embargo, choice1, 0, 0, post, handPos, 0);
        PutSeed(randSeed);

        // +2 coins
        pre.coins = pre.coins + 2;

        // see if selected pile is in play
        if (pre.supplyCount[choice1] != -1) {
                
                // add embargo token to selected supply pile
                pre.embargoTokens[choice1]++;

                // trash card
                discardCard(handPos, curPlayer, &pre, 1);
        }

        if (result == 0) {
                assert(result == 0);
                assert(post->handCount[curPlayer] == getHandCount - 1);
                assert(post->coins == getCoins + 2);
                assert(post->embargoTokens[choice1] == getEmbargoTokens + 1);
                assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
        } else {
                assert(result == -1);
                assert(post->coins == getCoins + 2);
        }

        return 0;
}




int main() {
        
        struct gameState game;
        srand(time(NULL));
        int randSeed = rand();
        int i,j,p,choice1;

        printf ("Random Testing Embargo Card.....\n");

        SelectStream(3);
        PutSeed(randSeed);

        for (i = 0; i < 1000; i++) {
                SelectStream(3);
                for (j = 0; j < sizeof(struct gameState); j++) {
                        ((char*)&game)[j] = floor(Random() * 256);
                }

                p = floor(Random() * MAX_PLAYERS);
                game.whoseTurn = p;
                game.deckCount[p] = floor(Random() * MAX_DECK);
                game.discardCount[p] = floor(Random() * MAX_DECK);
                game.handCount[p] = floor(Random() * MAX_HAND);
                game.playedCardCount = floor(Random() * MAX_DECK);
                choice1 = floor(Random() * (treasure_map + 1));
                game.coins = 0;
                game.embargoTokens[choice1] = 0;
                game.supplyCount[choice1] = floor(Random() * 60) - 1;

                testEmbargoCard(p, choice1, 0, 0, &game, randSeed);
        }

        printf("ALL TESTS OK\n\n");
        return 0;
}